#include "RecibidorMensajesServidor.h"

RecibidorMensajesServidor::RecibidorMensajesServidor(Socket* unSocket,
		ColaMensajesServidor* unaCola) {
	socket = unSocket;
	cola = unaCola;
}


void RecibidorMensajesServidor::operator()() {
	while(socket->getEstado() == Socket::ESTADO_CONECTADO) {
		socket->recibir(&mensaje);
		cola->encolar(&mensaje);
	}
}



RecibidorMensajesServidor::~RecibidorMensajesServidor() {}

