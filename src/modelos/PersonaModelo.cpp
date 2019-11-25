#include "PersonaModelo.h"

PersonaModelo::PersonaModelo() {
	posicionX = 0;
    posicionY = 0;
    dadoVuelta = false;
    estado = NULL;
    energia = 0;
    posicionXAnterior = 0;
    posicionYAnterior = 0;
}

int PersonaModelo::darPosicionX(){
    return posicionX;
}


int PersonaModelo::darPosicionY(){
    return posicionY;
}


bool PersonaModelo::consultarDadoVuelta(){
    return dadoVuelta;
}

void PersonaModelo::sumarPuntos(){

}

PersonaModelo::~PersonaModelo() {}

