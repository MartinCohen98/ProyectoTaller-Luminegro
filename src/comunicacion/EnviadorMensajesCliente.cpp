#include "EnviadorMensajesCliente.h"

EnviadorMensajesCliente::EnviadorMensajesCliente(Socket* unSocket,
								ColaMensajesCliente* unaCola) {
	socket = unSocket;
	cola = unaCola;
}


void EnviadorMensajesCliente::operator()() {
	while(socket->getEstado() == Socket::ESTADO_CONECTADO) {
		mensaje = cola->desencolar();
		if (mensaje.get() != Nothing) {
			socket->enviar(&mensaje);
		} else {
			std::this_thread::yield();
		}
	}
}


EnviadorMensajesCliente::~EnviadorMensajesCliente() {}

