#include "RecibidorMensajesCliente.h"

RecibidorMensajesCliente::RecibidorMensajesCliente(Socket* unSocket,
		ColaMensajesCliente* unaCola) {
	socket = unSocket;
	cola = unaCola;
}


void RecibidorMensajesCliente::operator()() {
	while(socket->getEstado() == Socket::ESTADO_CONECTADO) {
		socket->recibir(&mensaje);
		if (mensaje.get() != Nothing)
			cola->encolar(&mensaje);
	}
	mensaje.Codificar(Disconnect);
	cola->encolar(&mensaje);
}


RecibidorMensajesCliente::~RecibidorMensajesCliente() {}

