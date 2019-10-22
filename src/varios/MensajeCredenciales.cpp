#include "MensajeCredenciales.h"

void MensajeCredenciales::setUsuario(std::string valor) {
    this->usuario = valor;
}


void MensajeCredenciales::setClave(std::string valor) {
    this->usuario = valor;
}


void MensajeCredenciales::setEstado(int valor) {
    this->estado = valor;
}


std::string MensajeCredenciales::getUsuario() {
    return this->usuario;
}


std::string MensajeCredenciales::getClave() {
    return this->clave;
}

int MensajeCredenciales::getEstado() {
    return this->estado;
}