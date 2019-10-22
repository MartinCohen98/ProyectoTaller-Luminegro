#include "GestorThreads.h"

GestorThreads::GestorThreads(int cantidadDeJugadores) {
	jugadores = cantidadDeJugadores;
	colas = new ColaMensajesCliente[jugadores];
	sockets = new Socket*[jugadores];
	threadsRecibidoras = new std::thread*[jugadores];
}


void GestorThreads::agregarJugador(Socket* socket, int numero) {
	sockets[numero] = socket;
	threadsRecibidoras[numero] =
			new std::thread(RecibidorMensajesCliente(sockets[numero],
													&colas[numero]));
}


void GestorThreads::recibirMensajeDeCliente(MensajeCliente* mensaje, int cliente) {
	(*mensaje) = colas[cliente].desencolar();
}


GestorThreads::~GestorThreads() {
	delete[] sockets;
	delete[] colas;
}

