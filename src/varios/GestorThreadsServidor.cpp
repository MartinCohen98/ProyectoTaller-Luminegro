#include "GestorThreadsServidor.h"

GestorThreadsServidor::GestorThreadsServidor(int cantidadDeJugadores) {
	jugadores = cantidadDeJugadores;
	colas = new ColaMensajesCliente[jugadores];
	sockets = new Socket*[jugadores];
	threadsRecibidoras = new std::thread*[jugadores];
}


void GestorThreadsServidor::agregarJugador(Socket* socket, int numero) {
	sockets[numero] = socket;
	threadsRecibidoras[numero] =
			new std::thread(RecibidorMensajesCliente(sockets[numero],
													&colas[numero]));
}


void GestorThreadsServidor::recibirMensajeDeCliente(MensajeCliente* mensaje, int cliente) {
	(*mensaje) = colas[cliente].desencolar();
}


GestorThreadsServidor::~GestorThreadsServidor() {
	delete[] sockets;
	delete[] colas;
}

