#include "ColaMensajesCliente.h"

ColaMensajesCliente::ColaMensajesCliente() {}


void ColaMensajesCliente::encolar(MensajeCliente* mensaje) {
	m.lock();
	if (mensaje->get() != Nothing)
		cola.push(*mensaje);
	m.unlock();
}


MensajeCliente ColaMensajesCliente::desencolar() {
	MensajeCliente mensaje;
	m.lock();
	if (cola.empty()) {
		mensaje.Codificar(Nothing);
	} else {
		mensaje = cola.front();
		cola.pop();
	}
	m.unlock();
	return mensaje;
}


ColaMensajesCliente::~ColaMensajesCliente() {
	while(!cola.empty())
		cola.pop();
}

