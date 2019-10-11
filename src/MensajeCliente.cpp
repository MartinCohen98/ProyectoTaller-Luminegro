/*
 * MensajeCliente.cpp
 *
 *  Created on: 9 oct. 2019
 *      Author: julio
 */

#include "MensajeCliente.h"

MensajeCliente::MensajeCliente() {
	// TODO Auto-generated constructor stub

}

void MensajeCliente::Codificar(enum teclas input){
	datos = input;
}

int MensajeCliente::DarDatos(void){
	return datos;
}

MensajeCliente::~MensajeCliente() {
	// TODO Auto-generated destructor stub
}

