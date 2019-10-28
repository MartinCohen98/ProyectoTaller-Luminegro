#include "EnviadorMensajesServidor.h"

EnviadorMensajesServidor::EnviadorMensajesServidor(Socket* unSocket,
									ColaMensajesServidor* unaCola) {
	socket = unSocket;
	cola = unaCola;
}


void EnviadorMensajesServidor::operator()() {
	while(socket->getEstado() == Socket::ESTADO_CONECTADO) {
		mensaje = cola->desencolar();
		if (mensaje.obtenerTipoDeSprite() != MensajeInvalido) {
			socket->enviar(&mensaje);
		} else {
			std::this_thread::yield();
		}
	}
}


EnviadorMensajesServidor::~EnviadorMensajesServidor() {}

