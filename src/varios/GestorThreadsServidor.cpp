#include "GestorThreadsServidor.h"

GestorThreadsServidor::GestorThreadsServidor(int cantidadDeJugadores) {
	jugadores = cantidadDeJugadores;
	colasRecibidoras = new ColaMensajesCliente[jugadores];
	colasEnviadoras = new ColaMensajesServidor[jugadores];
	sockets = new Socket*[jugadores];
	threadsRecibidoras = new std::thread*[jugadores];
	threadsEnviadoras = new std::thread*[jugadores];
	conectado = new bool[jugadores];
}


void GestorThreadsServidor::agregarJugador(Socket* socket, int numero) {
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
	conectado[numero] = true;
}


void GestorThreadsServidor::recibirMensajeDeCliente(MensajeCliente* mensaje, int cliente) {
	(*mensaje) = colasRecibidoras[cliente].desencolar();
}


void GestorThreadsServidor::enviarMensaje(MensajeServidor* mensaje) {
	for (int i = 0; i < jugadores; i++) {
		colasEnviadoras[i].encolar(mensaje);
	}
}


void GestorThreadsServidor::checkearDesconecciones() {
	for (int i = 0; i < jugadores; i++) {
		if (sockets[i]->getEstado() == Socket::ESTADO_DESCONECTADO) {
			threadsEnviadoras[i]->join();
			delete threadsEnviadoras[i];
			threadsEnviadoras[i] = NULL;
			threadsRecibidoras[i]->join();
			delete threadsRecibidoras[i];
			threadsRecibidoras[i] = NULL;
			sockets[i]->cerrar();
			conectado[i] = false;
		}
	}
}


bool GestorThreadsServidor::estaConectado(int jugador) {
	return conectado[jugador];
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

