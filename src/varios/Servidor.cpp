#include "Servidor.h"
#include <iostream>

using namespace std;
using namespace Logger;


void Servidor::validarCredenciales(MensajeCredenciales *mensajeCredenciales) {
    string claveCorrecta;
    int jugadorNombre;

    string usuario = mensajeCredenciales->getUsuario();

    if (usuario.compare("mariano") == 0) {
        jugadorNombre = mariano;
        claveCorrecta = "cognitiva";

    } else if (usuario.compare("julio") == 0) {
        jugadorNombre = julio;
        claveCorrecta = "conductual";

    } else if (usuario.compare("martin") == 0) {
        jugadorNombre = martin;
        claveCorrecta = "gestalt";

    } else if (usuario.compare("nicolas") == 0) {
        jugadorNombre = nicolas;
        claveCorrecta = "freud";
    }

    if (mensajeCredenciales->getClave() == claveCorrecta) {
        if (jugadoresConectados[jugadorNombre]) {
            mensajeCredenciales->setEstado(MensajeCredenciales::ESTADO_USUARIO_YA_CONECTADO);
        } else {
            mensajeCredenciales->setEstado(MensajeCredenciales::ESTADO_AUTENTICADO);
            jugadoresConectados[jugadorNombre] = true;
        }
    } else {
        mensajeCredenciales->setEstado(MensajeCredenciales::ESTADO_USUARIO_O_CLAVE_ERRONEOS);
    }
}


Servidor::Servidor(int cantidadDeJugadores, char* puerto) {
	jugadoresCantidadEsperada = cantidadDeJugadores;
	socketsDeClientes = new Socket[cantidadDeJugadores];
	this->puerto = puerto;
	mensajesServidor = NULL;
	cantidadDeMensajes = 0;
}

void Servidor::Correr(pugi::xml_document* archiConfig) {
	Logger::Log *logueador  =  Logger::Log::ObtenerInstancia();

	bool nivelTerminado;

	GestorThreadsServidor gestorThreads(jugadoresCantidadEsperada);

	for (int i = 0; i < jugadoresCantidadEsperada; i++) {
		gestorThreads.agregarJugador(&socketsDeClientes[i], i);
	}

	for (int nivel = 1; nivel <= 2; nivel++) {

        string nivelNodeName = "nivel";
        nivelNodeName.append( to_string(nivel) );

		nivelTerminado = false;

		logueador->Info("Iniciando nivel: "+ nivelNodeName);
		logueador->Debug("Leyendo del XML la ubicación de los BMPs de los fondos y el ancho del terreno");
		
		FondoModelo fondo(archiConfig, nivel);
		ControlJugadoresModelo protagonistas(archiConfig, jugadoresCantidadEsperada);

		logueador->Debug("Creando enemigos y asignándoles su comportamiento básico");
		ControlEnemigosModelo controlEnemigos(nivel);

		logueador->Debug("Creando controlador de objetos y asignándoles su posición inicial");
		ControlObjetosModelo controlObjetos(archiConfig, fondo.obtenerAncho(), nivel);

		enviarCantidadDeReceives(&controlEnemigos, &controlObjetos, &gestorThreads);

		generarMensajesParaEnviar();

		while (!nivelTerminado) {
			gestorThreads.checkearDesconecciones();
			recibirInputs(&protagonistas, &gestorThreads);

			protagonistas.realizarMovimientos(&fondo);
			controlEnemigos.realizarMovimientos();

			if (fondo.seMovio()) {
				protagonistas.movidaDePantalla(&fondo);
				controlEnemigos.movidaDePantalla();
				controlObjetos.movidaDePantalla();
			}

			generarMensajes(&protagonistas, &fondo, &controlEnemigos,
								&controlObjetos);
			enviarMensajes(&gestorThreads);

			nivelTerminado = protagonistas.llegaronAlFin(&fondo);

			enviarMensajeDeNivelTerminado(nivelTerminado, &gestorThreads);

			SDL_Delay(25);
		}
	}
}

void Servidor::recibirInputs(ControlJugadoresModelo* protagonistas,
							GestorThreadsServidor* gestorThreads) {
	for (int i = 0; i < jugadoresCantidadEsperada; i++) {
		gestorThreads->recibirMensajeDeCliente(&mensajeCliente, i);
		protagonistas->procesarInput(&mensajeCliente, i);
	}
}

void Servidor::enviarCantidadDeReceives(ControlEnemigosModelo* enemigos,
							ControlObjetosModelo* objetos,
							GestorThreadsServidor* gestorThreads) {

	cantidadDeMensajes = jugadoresCantidadEsperada + objetos->obtenerCantidad()
					+ enemigos->obtenerCantidad();
	Encuadre insercion;
	Encuadre frame(cantidadDeMensajes, 0, 0, 0);
	MensajeServidor mensaje;
	mensaje.generarMensaje(&frame, &insercion, Jugador1);
	gestorThreads->enviarMensaje(&mensaje);
}

void Servidor::generarMensajes(ControlJugadoresModelo* protagonistas,
		FondoModelo* fondo, ControlEnemigosModelo* enemigos,
		ControlObjetosModelo* objetos) {
    
	int mensajeActual = 0;

	fondo->generarMensajes(mensajesServidor, &mensajeActual);
	protagonistas->generarMensajes(mensajesServidor, &mensajeActual);
	enemigos->generarMensajes(mensajesServidor, &mensajeActual);
	objetos->generarMensajes(mensajesServidor, &mensajeActual);
}


void Servidor::enviarMensajes(GestorThreadsServidor* gestorThreads) {
	for (int i = 0; i < (cantidadDeMensajes + 3); i++) {
		gestorThreads->enviarMensaje(&mensajesServidor[i]);
	}
}


void Servidor::enviarMensajeDeNivelTerminado(bool nivelTerminado,
							GestorThreadsServidor* gestorThreads) {
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

int Servidor::AbrirSesion() {
    return socketAceptador.servidorInicializar(puerto);
}

int Servidor::EsperarConexiones() {
    int resultadoAccion;
    MensajeCredenciales mensajeCredenciales;

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

            validarCredenciales(&mensajeCredenciales);

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

    // Se deja un thread esperando conexiones porque ya superarían el máximo permitido de jugadores y hay que avisarles
    //threadRechazadorConexiones = new std::thread(RechazadorConexiones(&socketAceptador));

    return resultadoAccion;
}

