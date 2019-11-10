#include "Servidor.h"
#include <iostream>

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
}

void Servidor::correr() {
	Logger::Log *logueador  =  Logger::Log::ObtenerInstancia();

	bool nivelTerminado;

	for (int i = 0; i < jugadoresCantidadEsperada; i++) {
		gestorThreads->agregarJugador(&socketsDeClientes[i], i);
	}

	gestorThreads->comenzarAAceptar(&socketAceptador, credenciales, &nivelActual);

	for (nivelActual = 1; nivelActual <= 2; nivelActual++) {

        string nivelNodeName = "nivel";
        nivelNodeName.append( to_string(nivelActual) );

		nivelTerminado = false;

		logueador->Info("Iniciando nivel: "+ nivelNodeName);
		logueador->Debug("Leyendo del XML la ubicación de los BMPs de los fondos y el ancho del terreno");
		
		FondoModelo fondo(archivoConfiguracion, nivelActual);
		ControlJugadoresModelo protagonistas(archivoConfiguracion, jugadoresCantidadEsperada);

		logueador->Debug("Creando enemigos y asignándoles su comportamiento básico");
		ControlEnemigosModelo controlEnemigos(nivelActual);

		logueador->Debug("Creando controlador de objetos y asignándoles su posición inicial");
		ControlObjetosModelo controlObjetos(archivoConfiguracion, fondo.obtenerAncho(), nivelActual);

		desconectarJugadoresDesconectados(&protagonistas);

		enviarCantidadDeReceives(&controlEnemigos, &controlObjetos);

		generarMensajesParaEnviar();

		controlEnemigos.movimientosIniciales();

		int atacante = controlEnemigos.buscarObjetivo(&protagonistas);

		while (!nivelTerminado) {
			gestorThreads->checkearConecciones(cantidadDeMensajes, &protagonistas);
			recibirInputs(&protagonistas);

			protagonistas.realizarMovimientos(&fondo);
			controlEnemigos.realizarMovimientos(atacante, &protagonistas);

			if (fondo.seMovio()) {
				protagonistas.movidaDePantalla(&fondo);
				controlEnemigos.movidaDePantalla();
				controlObjetos.movidaDePantalla();
			}

			enviarMensajes(&protagonistas, &fondo, &controlEnemigos,
								&controlObjetos);

			nivelTerminado = protagonistas.llegaronAlFin(&fondo);

			enviarMensajeDeNivelTerminado(nivelTerminado);

			SDL_Delay(25);
		}
	}
}

void Servidor::recibirInputs(ControlJugadoresModelo* protagonistas) {
	for (int i = 0; i < jugadoresCantidadEsperada; i++) {
		gestorThreads->recibirMensajeDeCliente(&mensajeCliente, i);
		protagonistas->procesarInput(&mensajeCliente, i);
	}
}

void Servidor::enviarCantidadDeReceives(ControlEnemigosModelo* enemigos,
							ControlObjetosModelo* objetos) {

	cantidadDeMensajes = jugadoresCantidadEsperada + objetos->obtenerCantidad()
					+ enemigos->obtenerCantidad();
	Encuadre insercion;
	Encuadre frame(cantidadDeMensajes, 0, 0, 0);
	MensajeServidor mensaje;
	mensaje.generarMensaje(&frame, &insercion, Jugador1);
	gestorThreads->enviarMensaje(&mensaje);
}

void Servidor::enviarMensajes(ControlJugadoresModelo* protagonistas,
		FondoModelo* fondo, ControlEnemigosModelo* enemigos,
		ControlObjetosModelo* objetos) {
    
	int mensajeActual = 0;

	fondo->generarMensajes(mensajesServidor, &mensajeActual);
	protagonistas->generarMensajes(mensajesServidor, &mensajeActual);
	enemigos->generarMensajes(mensajesServidor, &mensajeActual);
	objetos->generarMensajes(mensajesServidor, &mensajeActual);
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
                mensajeCredenciales.setNivelInicial(nivelActual);
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


void Servidor::desconectarJugadoresDesconectados(ControlJugadoresModelo* jugadores) {
	for (int i = 0; i < jugadoresCantidadEsperada; i++) {
		if (!gestorThreads->estaConectado(i)) {
			jugadores->desaparecer(i);
			jugadores->desconectar(i);
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
