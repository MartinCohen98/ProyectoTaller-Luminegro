#include "PersonaModelo.h"

PersonaModelo::PersonaModelo() {
	posicionX = 0;
    posicionY = 0;
    dadoVuelta = false;
    estado = NULL;
}

int PersonaModelo::darPosicionX(){
    return posicionX;
}

int PersonaModelo::darPosicionY(){
    return posicionY;
}

PersonaModelo::~PersonaModelo() {}

