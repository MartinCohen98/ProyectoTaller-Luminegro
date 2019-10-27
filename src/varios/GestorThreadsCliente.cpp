#include "GestorThreadsCliente.h"

GestorThreadsCliente::GestorThreadsCliente(Socket* unSocket) {
	threadEnviadora = NULL;
	socket = unSocket;
}


void GestorThreadsCliente::comenzarAEnviar() {
	threadEnviadora = new std::thread(EnviadorMensajesCliente(socket,
			&colaCliente));
}


void GestorThreadsCliente::enviarMensaje(MensajeCliente* mensaje) {
	colaCliente.encolar(mensaje);
}


GestorThreadsCliente::~GestorThreadsCliente() {}
