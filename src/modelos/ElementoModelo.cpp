#include "ElementoModelo.h"

ElementoModelo::ElementoModelo() {
	posicionX = 0;
	posicionY = 0;
	ancho = 0;
	alto = 0;
	sprite = Caja;
	golpes = 0;
}


void ElementoModelo::movidaDePantalla() {
	posicionX = posicionX - 12;
	insercion.modificar(posicionX, posicionY, ancho, alto);
}



void ElementoModelo::generarMensaje(MensajeServidor* mensajes, int* mensajeActual) {
	mensajes[*mensajeActual].generarMensaje(&encuadre, &insercion, sprite);
	(*mensajeActual)++;
}


void ElementoModelo::desaparecer() {
	posicionY += 600;
	insercion.modificar(posicionX, posicionY, ancho, alto);
}

void ElementoModelo::actualizarInsercion() {
	insercion.modificar(posicionX, posicionY, ancho, alto);
}

void ElementoModelo::actualizarPosicion(){
    if(estado->terminado())
    	desaparecer();
}

ElementoModelo::~ElementoModelo() {}

