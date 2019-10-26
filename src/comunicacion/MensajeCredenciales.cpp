#include "MensajeCredenciales.h"

void MensajeCredenciales::setUsuario(std::string valor) {
    // Se almacena el usuario, pero siempre con un largo fijo
    this->usuario = valor;
    completarCredencialCaracteres(&this->usuario);
}


void MensajeCredenciales::setClave(std::string valor) {
    // Se almacena la clave, pero siempre con un largo fijo
    this->clave = valor;
    completarCredencialCaracteres(&this->clave);
}


void MensajeCredenciales::completarCredencialCaracteres(std::string *valor) {
    // Le agrega espacios al final si es necesario
    if (UNA_CREDENCIAL_LONGITUD_MAXIMA > valor->size()) {
       valor->insert(valor->size(), " ", UNA_CREDENCIAL_LONGITUD_MAXIMA - valor->size());
    }
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