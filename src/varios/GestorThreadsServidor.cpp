#include "GestorThreadsServidor.h"

GestorThreadsServidor::GestorThreadsServidor(int cantidadDeJugadores) {
	jugadores = cantidadDeJugadores;
	colasRecibidoras = new ColaMensajesCliente[jugadores];
	colasEnviadoras = new ColaMensajesServidor[jugadores];
	sockets = new Socket*[jugadores];
	threadsRecibidoras = new std::thread*[jugadores];
	threadsEnviadoras = new std::thread*[jugadores];
	contador = new ContadorDeJugadores(jugadores);
	threadAceptador = NULL;
}


void GestorThreadsServidor::agregarJugador(Socket* socket, int numero) {
	if (socket != NULL)
		sockets[numero] = socket;
	MensajeServidor mensajeServidor;
	MensajeCliente mensajeCliente;
	while (mensajeServidor.obtenerTipoDeSprite() != MensajeInvalido)
		mensajeServidor = colasEnviadoras[numero].desencolar();
	while (mensajeCliente.get() != Nothing)
		mensajeCliente = colasRecibidoras[numero].desencolar();
	threadsRecibidoras[numero] =
			new std::thread(RecibidorMensajesCliente(sockets[numero],
												&colasRecibidoras[numero]));
	threadsEnviadoras[numero] =
			new std::thread(EnviadorMensajesServidor(sockets[numero],
												&colasEnviadoras[numero]));
	contador->seConectoElJugador(numero);
}


void GestorThreadsServidor::recibirMensajeDeCliente(MensajeCliente* mensaje, int cliente) {
	(*mensaje) = colasRecibidoras[cliente].desencolar();
}


void GestorThreadsServidor::enviarMensaje(MensajeServidor* mensaje) {
	for (int i = 0; i < jugadores; i++) {
		colasEnviadoras[i].encolar(mensaje);
	}
}


void GestorThreadsServidor::checkearConecciones(int cantidadDeMensajes,
										ControlJugadoresModelo* protagonistas) {
	for (int i = 0; i < jugadores; i++) {
		if (sockets[i]->getEstado() == Socket::ESTADO_DESCONECTADO) {
			threadsEnviadoras[i]->join();
			delete threadsEnviadoras[i];
			threadsEnviadoras[i] = NULL;
			threadsRecibidoras[i]->join();
			delete threadsRecibidoras[i];
			threadsRecibidoras[i] = NULL;
			sockets[i]->cerrar();
			contador->seDesconectoElJugador(i);
		}
	}
	InformacionJugador info = contador->obtenerInfo();
	if (info.obtenerSocket() != 0) {
		sockets[info.obtenerNumeroDeJugador()]->asignarNumero(info.obtenerSocket());
		Encuadre insercion;
		Encuadre frame(cantidadDeMensajes, 0, 0, 0);
		MensajeServidor mensaje;
		mensaje.generarMensaje(&frame, &insercion, Jugador1);
		sockets[info.obtenerNumeroDeJugador()]->enviar(&mensaje);
		protagonistas->conectar(info.obtenerNumeroDeJugador());
		agregarJugador(NULL, info.obtenerNumeroDeJugador());
	}
}


bool GestorThreadsServidor::estaConectado(int jugador) {
	return contador->estaConectado(jugador);
}


void GestorThreadsServidor::comenzarAAceptar(Socket* socketAceptador,
									MensajeCredenciales* credenciales) {
	contador->definirCredenciales(credenciales);
	threadAceptador = new std::thread(AceptadorConexiones(socketAceptador,
															contador));
}


GestorThreadsServidor::~GestorThreadsServidor() {
	for (int i = 0; i < jugadores; i++) {
		if (threadsEnviadoras[i] != NULL) {
			threadsEnviadoras[i]->join();
			delete threadsEnviadoras[i];
		}
		if (threadsRecibidoras[i] != NULL) {
			threadsRecibidoras[i]->join();
			delete threadsRecibidoras[i];
		}
	}
	delete[] threadsEnviadoras;
	delete[] threadsRecibidoras;
	delete[] sockets;
	delete[] colasRecibidoras;
	delete[] colasEnviadoras;
}

