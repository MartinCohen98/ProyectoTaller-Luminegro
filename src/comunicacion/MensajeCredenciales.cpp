#include "MensajeCredenciales.h"


void MensajeCredenciales::setUsuario(const std::string& valor) {
    // Se almacena el usuario, pero siempre con un largo fijo
    strcpy(this->usuario, valor.c_str());
}

void MensajeCredenciales::setClave(std::string valor) {
    // Se almacena la clave, pero siempre con un largo fijo
    strcpy(this->clave, valor.c_str());
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

