#include "ColaMensajesServidor.h"

ColaMensajesServidor::ColaMensajesServidor() {}


void ColaMensajesServidor::encolar(MensajeServidor* mensaje) {
	m.lock();
	cola.push(*mensaje);
	m.unlock();
}


MensajeServidor ColaMensajesServidor::desencolar() {
	MensajeServidor mensaje;
	m.lock();
	if (cola.empty()) {
		mensaje.generarMensaje(NULL, NULL, MensajeInvalido);
	} else {
		mensaje = cola.front();
		cola.pop();
	}
	m.unlock();
	return mensaje;
}


ColaMensajesServidor::~ColaMensajesServidor() {
	while(!cola.empty())
		cola.pop();
}

