#include "GestorThreadsCliente.h"

GestorThreadsCliente::GestorThreadsCliente(Socket* unSocket) {
	threadEnviadora = NULL;
	threadRecibidora = NULL;
	socket = unSocket;
}


void GestorThreadsCliente::comenzar() {
	threadEnviadora = new std::thread(EnviadorMensajesCliente(socket,
			&colaCliente));
	threadRecibidora = new std::thread(RecibidorMensajesServidor(socket,
			&colaServidor));
}


bool GestorThreadsCliente::seDesconecto() {
    return socket->getEstado() == Socket::ESTADO_DESCONECTADO;
}


void GestorThreadsCliente::enviarMensaje(MensajeCliente* mensaje) {
	colaCliente.encolar(mensaje);
}


MensajeServidor GestorThreadsCliente::recibirMensaje() {
	MensajeServidor mensaje;
	mensaje.generarMensaje(NULL, NULL, MensajeInvalido);
	while (mensaje.obtenerTipoDeSprite() == MensajeInvalido) {
        if (seDesconecto()) {
            return mensaje;
        }
		mensaje = colaServidor.desencolar();
		if (mensaje.obtenerTipoDeSprite() == MensajeInvalido)
			std::this_thread::yield();
	}
	return mensaje;
}


MensajeInicioPartida GestorThreadsCliente::recibirMensajeDeInicio() {
    MensajeInicioPartida mensajeInicio;
    socket->recibir((char *) &mensajeInicio, sizeof(MensajeInicioPartida));
    return mensajeInicio;
}


GestorThreadsCliente::~GestorThreadsCliente() {}

