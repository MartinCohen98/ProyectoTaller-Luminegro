#include "Servidor.h"
#include <iostream>
#include "../comunicacion/MensajeInicioPartida.h"

using namespace std;
using namespace Logger;


Servidor::Servidor(int cantidadDeJugadores, char* puerto, pugi::xml_document* archivoConfiguracion) {
	jugadoresCantidadEsperada = cantidadDeJugadores;
	socketsDeClientes = new Socket[cantidadDeJugadores];
	this->puerto = puerto;
	mensajesServidor = NULL;
	cantidadDeMensajes = 0;
    this->archivoConfiguracion = archivoConfiguracion;
	gestorThreads = new GestorThreadsServidor(jugadoresCantidadEsperada);
    leerTodosLosUsuariosYClavesDelConfig(&cantidadDeJugadores);
    nivelActual = 1;
    modelo = new Modelo(archivoConfiguracion, cantidadDeJugadores);
}

void Servidor::correr() {
	for (int i = 0; i < jugadoresCantidadEsperada; i++) {
		gestorThreads->agregarJugador(&socketsDeClientes[i], i);
	}
	//Generar mensaje de inicio y enviarlo a los clientes para arrancar la partida
	MensajeInicioPartida mensajeInicio = generarMensajeInicioPartida();
	enviarMensajeInicioPartida(&mensajeInicio);

    //Queda un hilo escuchando intentos de conexiones.
    // Si en algún momento se desconecta un cliente, habilita reloguearse (por eso la referencia al nivel)
	gestorThreads->comenzarAAceptar(&socketAceptador, credenciales, &nivelActual, &mensajeInicio);

	for (nivelActual = 1; nivelActual <= 2; nivelActual++) {
		jugarNivel();
	}
}


void Servidor::jugarNivel() {
	Logger::Log *logueador  =  Logger::Log::ObtenerInstancia();

    string nivelNodeName = "nivel";
    nivelNodeName.append( to_string(nivelActual) );
    logueador->Info("Iniciando nivel: "+ nivelNodeName);

	bool nivelTerminado = false;

	desconectarJugadoresDesconectados();
	enviarCantidadDeReceives();

	while (!nivelTerminado) {
		gestorThreads->checkearConecciones(cantidadDeMensajes, modelo);
		recibirInputs();

		modelo->realzarMovimientos();
		enviarMensajes();

		nivelTerminado = modelo->nivelTerminado();
		enviarMensajeDeNivelTerminado(nivelTerminado);

		SDL_Delay(25);
	}
	if (nivelActual < 2)
		modelo->pasarNivel();
}


void Servidor::recibirInputs() {
	for (int i = 0; i < jugadoresCantidadEsperada; i++) {
        gestorThreads->recibirMensajeDeCliente(&mensajeCliente, i);
        modelo->procesarInputDeJugador(&mensajeCliente, i);
    }
}

void Servidor::enviarCantidadDeReceives() {
	cantidadDeMensajes = modelo->obtenerCantidadDeEntidades();
	Encuadre insercion;
	Encuadre frame(cantidadDeMensajes, 0, 0, 0);
	MensajeServidor mensaje;
	mensaje.generarMensaje(&frame, &insercion, Jugador1);
	gestorThreads->enviarMensaje(&mensaje);
	generarMensajesParaEnviar();
}

void Servidor::enviarMensajes() {
    modelo->generarMensajesServidor(mensajesServidor);
	for (int i = 0; i < (cantidadDeMensajes + 3); i++) {
		gestorThreads->enviarMensaje(&mensajesServidor[i]);
	}
}


void Servidor::enviarMensajeDeNivelTerminado(bool nivelTerminado) {
	MensajeServidor mensaje;
	if (nivelTerminado) {
		mensaje.darVuelta();
	}
	gestorThreads->enviarMensaje(&mensaje);
}


void Servidor::generarMensajesParaEnviar() {
	//Los el valor de 3 son los mensajes de las capas del fondo
	if (mensajesServidor != NULL)
		delete[] mensajesServidor;
	mensajesServidor = new MensajeServidor[cantidadDeMensajes + 3];
}


Servidor::~Servidor() {
	socketAceptador.cerrar();
	for (int i = 0; i < jugadoresCantidadEsperada; i++) {
		socketsDeClientes[i].cerrar();
	}
	delete[] socketsDeClientes;
	if (mensajesServidor != NULL)
		delete[] mensajesServidor;
}


int Servidor::abrirSesion() {
    return socketAceptador.servidorInicializar(puerto);
}

int Servidor::esperarConexiones() {
    int resultadoAccion;
    MensajeCredenciales mensajeCredenciales;
    bool usuarioYClaveValidados = false;

    cout << "Esperando conexión de clientes en el puerto " << puerto << endl;

    // ESTO SE LLAMA CON UNA INSTANCIA NUEVA DE "Socket" POR CADA JUGADOR QUE SE NOS CONECTA
    for (int i = 0; i < jugadoresCantidadEsperada; i++) {

        resultadoAccion = socketAceptador.esperarYAceptarCliente(&socketsDeClientes[i]);
        if (resultadoAccion == EXIT_FAILURE) {
            // Ya fue logueado en la clase
            socketAceptador.cerrar();
            return resultadoAccion;
        }

        // Se le avisa que hay cupo disponible para que se conecte el jugador
        mensajeCredenciales.setEstado(MensajeCredenciales::ESTADO_ESPERANDO_CONEXIONES);
        resultadoAccion = socketsDeClientes[i].enviar(&mensajeCredenciales);
        if (resultadoAccion == EXIT_FAILURE) {
            // Ya fue logueado en la clase
            socketAceptador.cerrar();
            return resultadoAccion;
        }

        while (mensajeCredenciales.getEstado() != MensajeCredenciales::ESTADO_AUTENTICADO) {
            resultadoAccion = socketsDeClientes[i].recibir(&mensajeCredenciales);
            if (resultadoAccion == EXIT_FAILURE) {
                // Ya fue logueado en la clase
                socketAceptador.cerrar();
                return resultadoAccion;
            }

            usuarioYClaveValidados = this->validarUsuarioYClave(&mensajeCredenciales);

            if (usuarioYClaveValidados) {
                credenciales[i] = mensajeCredenciales;
                mensajeCredenciales.setEstado(MensajeCredenciales::ESTADO_AUTENTICADO);
            } else {
                mensajeCredenciales.setEstado(MensajeCredenciales::ESTADO_USUARIO_O_CLAVE_ERRONEOS);
            }

            resultadoAccion = socketsDeClientes[i].enviar(&mensajeCredenciales);
            if (resultadoAccion == EXIT_FAILURE) {
                // Ya fue logueado en la clase
                socketAceptador.cerrar();
                return resultadoAccion;
            }
        }

        mensajeCredenciales.setEstado(MensajeCredenciales::ESTADO_ESPERANDO_CONEXIONES);
        cout << "Cliente conectado" << endl;
    }

    return resultadoAccion;
}


void Servidor::desconectarJugadoresDesconectados() {
	for (int i = 0; i < jugadoresCantidadEsperada; i++) {
		if (!gestorThreads->estaConectado(i)) {
			modelo->desaparecerJugador(i);
			modelo->desconectarJugador(i);
		}
	}
}


void Servidor::leerTodosLosUsuariosYClavesDelConfig(int *cantidadDeJugadores) {

    usuariosYClaves = new UsuarioYClave[4];
    string usuariosNombres[4] = {"mariano", "julio", "martin", "nicolas"};
    string clave;
    int n;

    for (int i = 0; i < 4; i ++) {
        n = usuariosNombres[i].length();
        char unUsuarioNombre[n + 1];
        strcpy(unUsuarioNombre, usuariosNombres[i].c_str());

        clave = archivoConfiguracion->child("configuracion").child("claves").child_value(unUsuarioNombre);
        usuariosYClaves[i].setValores(usuariosNombres[i], clave);
    }
}


bool Servidor::validarUsuarioYClave(MensajeCredenciales* mensajeCredenciales) {
    bool resultado = false;
    int i = 0;

    while (!resultado && i < 4) {
        resultado = usuariosYClaves[i].validar( mensajeCredenciales->getUsuario(), mensajeCredenciales->getClave());
        i++;
    }

    return resultado;
}

int Servidor::enviarMensajeInicioPartida(MensajeInicioPartida *mensaje) {
    return gestorThreads->enviarMensajeInicioPartida(mensaje);
}

MensajeInicioPartida Servidor::generarMensajeInicioPartida() {
    int vidaMaxima = stoi(archivoConfiguracion->child("configuracion").child("escenario").child("vitalidad").child_value("energia"));

    MensajeInicioPartida mensaje = MensajeInicioPartida();
    mensaje.setNivelInicial(nivelActual);
    mensaje.setVidaMax(vidaMaxima);
    mensaje.setCantidadJugadoresPartida(jugadoresCantidadEsperada);
    for(int i = 0; i < jugadoresCantidadEsperada; i++){
        mensaje.setNombreJugador(i, credenciales[i].getUsuario());
    }
    return mensaje;
}
