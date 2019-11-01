//
// Created by mariano on 1/11/19.
//

#include "UsuarioYClave.h"

UsuarioYClave::UsuarioYClave() {
}

void UsuarioYClave::setValores(const std::string nombre, std::string clave) {
    this->nombre = nombre;
    this->clave = clave;
}

bool UsuarioYClave::validar(std::string nombre, std::string clave) {
    bool resultado;

    if (this->fueAutenticado) {
        resultado = false;
    } else {
        resultado = (this->nombre == nombre && this->clave == clave);
        if (resultado) {
            this->fueAutenticado = true;
        }
    }

    return resultado;
}