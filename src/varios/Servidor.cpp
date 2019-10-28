#include "Servidor.h"

using namespace std;

Servidor::Servidor(int cantidadDeJugadores, char* puerto) {
	jugadores = cantidadDeJugadores;
	socketsDeClientes = new Socket[cantidadDeJugadores];
	int resultadoAccion = socketAceptador.servidorInicializar(puerto);
	if (resultadoAccion == 1) {
		// Ya fue logueado en la clase
		return;
	}

	// ESTO SE LLAMA CON UNA INSTANCIA NUEVA DE "Socket" POR CADA JUGADOR QUE SE NOS CONECTA
	for (int i = 0; i < jugadores; i++) {
		resultadoAccion = socketAceptador.esperarYAceptarCliente(&socketsDeClientes[i]);
		if (resultadoAccion == EXIT_FAILURE) {
			// Ya fue logueado en la clase
			socketAceptador.cerrar();
			return;
		}
	}
	mensajesServidor = NULL;
	cantidadDeMensajes = 0;
}

void Servidor::correr(pugi::xml_document* archiConfig) {
	Logger::Log *logueador  =  Logger::Log::ObtenerInstancia();

	bool nivelTerminado;

	GestorThreadsServidor gestorThreads(jugadores);

	for (int i = 0; i < jugadores; i++) {
		gestorThreads.agregarJugador(&socketsDeClientes[i], i);
	}

	for (int nivel = 1; nivel <= 2; nivel++) {

        string nivelNodeName = "nivel";
        nivelNodeName.append( to_string(nivel) );

		nivelTerminado = false;

		logueador->Info("Iniciando nivel: "+ nivelNodeName);
		logueador->Debug("Leyendo del XML la ubicación de los BMPs de los fondos y el ancho del terreno");
		
		FondoModelo fondo(archiConfig, nivel);
		ControlJugadoresModelo protagonistas(archiConfig, jugadores);

		logueador->Debug("Creando enemigos y asignándoles su comportamiento básico");
		ControlEnemigosModelo controlEnemigos(nivel);

		logueador->Debug("Creando controlador de objetos y asignándoles su posición inicial");
		ControlObjetosModelo controlObjetos(archiConfig, fondo.obtenerAncho(), nivel);

		enviarCantidadDeReceives(&controlEnemigos, &controlObjetos);

		generarMensajesParaEnviar();

		while (!nivelTerminado) {
			recibirInputs(&protagonistas, &gestorThreads);

			protagonistas.realizarMovimientos(&fondo);
			controlEnemigos.realizarMovimientos();

			if (fondo.seMovio()) {
				protagonistas.movidaDePantalla(&fondo);
				controlEnemigos.movidaDePantalla();
				controlObjetos.movidaDePantalla();
			}

			enviarEncuadres(&protagonistas, &fondo, &controlEnemigos,
								&controlObjetos);

			nivelTerminado = protagonistas.llegaronAlFin(&fondo);

			enviarMensajeDeNivelTerminado(nivelTerminado);

			SDL_Delay(25);
		}
	}
}

void Servidor::recibirInputs(ControlJugadoresModelo* protagonistas,
							GestorThreadsServidor* gestorThreads) {
	for (int i = 0; i < jugadores; i++) {
	    bool conectado=true;
	   /* if (i=1)
	       conectado=true;*/
		gestorThreads->recibirMensajeDeCliente(&mensajeCliente, i);
		protagonistas->procesarInput(&mensajeCliente, i, conectado);
	}
}

void Servidor::enviarCantidadDeReceives(ControlEnemigosModelo* enemigos,
							ControlObjetosModelo* objetos) {

	cantidadDeMensajes = jugadores + objetos->obtenerCantidad()
					+ enemigos->obtenerCantidad();

	for (int i = 0; i < jugadores; i++) {
        if (socketsDeClientes[i].getEstado() == Socket::ESTADO_CONECTADO) {
            socketsDeClientes[i].enviar(cantidadDeMensajes);
        }
    }
}

void Servidor::enviarEncuadres(ControlJugadoresModelo* protagonistas,
		FondoModelo* fondo, ControlEnemigosModelo* enemigos,
		ControlObjetosModelo* objetos) {
    
	int mensajeActual = 0;

	fondo->generarMensajes(mensajesServidor, &mensajeActual);
	protagonistas->generarMensajes(mensajesServidor, &mensajeActual);
	enemigos->generarMensajes(mensajesServidor, &mensajeActual);
	objetos->generarMensajes(mensajesServidor, &mensajeActual);
	for (int i = 0; i < jugadores; i++) {
		if (socketsDeClientes[i].getEstado() == Socket::ESTADO_CONECTADO) {
			socketsDeClientes[i].enviar(mensajesServidor, cantidadDeMensajes + 3);
		}
	}
}


void Servidor::enviarMensajeDeNivelTerminado(bool nivelTerminado) {
	MensajeServidor mensaje;
	if (nivelTerminado) {
		mensaje.darVuelta();
	}
    for (int i = 0; i < jugadores; i++) {
        if (socketsDeClientes[i].getEstado() == Socket::ESTADO_CONECTADO) {
            socketsDeClientes[i].enviar(&mensaje, 1);
        }
    }
}


void Servidor::generarMensajesParaEnviar() {
	//Los el valor de 3 son los mensajes de las capas del fondo
	if (mensajesServidor != NULL)
		delete[] mensajesServidor;
	mensajesServidor = new MensajeServidor[cantidadDeMensajes + 3];
}


Servidor::~Servidor() {
	socketAceptador.cerrar();
	for (int i = 0; i < jugadores; i++) {
		socketsDeClientes[i].cerrar();
	}
	delete[] socketsDeClientes;
	if (mensajesServidor != NULL)
		delete[] mensajesServidor;
}

