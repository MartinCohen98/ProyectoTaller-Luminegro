#include "MensajeCliente.h"

MensajeCliente::MensajeCliente() {
	datos = Rise;
}

void MensajeCliente::Codificar(enum teclas input){
	datos = input;
}

int MensajeCliente::get(void){
	return datos;
}

MensajeCliente::~MensajeCliente() {}

