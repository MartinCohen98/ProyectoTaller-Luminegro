#include "GestorThreadsServidor.h"

GestorThreadsServidor::GestorThreadsServidor(int cantidadDeJugadores) {
	jugadores = cantidadDeJugadores;
	colasRecibidoras = new ColaMensajesCliente[jugadores];
	colasEnviadoras = new ColaMensajesServidor[jugadores];
	sockets = new Socket*[jugadores];
	threadsRecibidoras = new std::thread*[jugadores];
	threadsEnviadoras = new std::thread*[jugadores];
}


void GestorThreadsServidor::agregarJugador(Socket* socket, int numero) {
	sockets[numero] = socket;
	threadsRecibidoras[numero] =
			new std::thread(RecibidorMensajesCliente(sockets[numero],
												&colasRecibidoras[numero]));
	threadsEnviadoras[numero] =
			new std::thread(EnviadorMensajesServidor(sockets[numero],
												&colasEnviadoras[numero]));
}


void GestorThreadsServidor::recibirMensajeDeCliente(MensajeCliente* mensaje, int cliente) {
	(*mensaje) = colasRecibidoras[cliente].desencolar();
}


void GestorThreadsServidor::enviarMensaje(MensajeServidor* mensaje) {
	for (int i = 0; i < jugadores; i++) {
		colasEnviadoras[i].encolar(mensaje);
	}
}


GestorThreadsServidor::~GestorThreadsServidor() {
	delete[] sockets;
	delete[] colasRecibidoras;
	delete[] colasEnviadoras;
}

