#include "EnemigoModelo.h"

EnemigoModelo::EnemigoModelo(int posXinicial, int posYinicial) {
	posicionX = posXinicial;
	posicionY = posYinicial;
	ancho = 140;
	alto = 280;
	estado = new EstadoEnemigoParado(0,0,47,78);
	dadoVuelta = false;
	actualizarInsercion();
}

void EnemigoModelo::avanzar() {
	dadoVuelta = false;
	estado = estado->avanzar();
	moverEnX(5);
	actualizarInsercion();
}

void EnemigoModelo::parar() {
	estado = estado->parar();
}

void EnemigoModelo::retroceder() {
	dadoVuelta = true;
	estado = estado->avanzar();
	moverEnX(-5);
	actualizarInsercion();
}

void EnemigoModelo::subir() {
	if (posicionY > 180) {
		estado = estado->avanzar();
		moverEnY(-5);
	} else {
		estado = estado->parar();
	}
	actualizarInsercion();
}

void EnemigoModelo::bajar() {
	if (posicionY < 320) {
		moverEnY(1);
        estado = estado->avanzar();
	} else {
		estado = estado->parar();
	}
	actualizarInsercion();
}

void EnemigoModelo::agacharse() {
	estado = estado->agacharse();
}

void EnemigoModelo::avanzarDiagArriba(){
}

void EnemigoModelo::avanzarDiagAbajo(){
}

void EnemigoModelo::retrocederDiagArriba(){
}

void EnemigoModelo::retrocederDiagAbajo(){
    dadoVuelta = true;
    moverEnX(-5);
    if (posicionY < 320) {
        moverEnY(1);
        estado = estado->avanzar();
    } else {
        estado = estado->parar();
    }
    actualizarInsercion();
}

void EnemigoModelo::retrocesoDePantalla() {
	posicionX = posicionX - 12;
}


void EnemigoModelo::generarMensaje(MensajeServidor* mensajes, int* mensajeActual) {
	Encuadre sprite = estado->obtenerSprite();
	mensajes[*mensajeActual].generarMensaje(&sprite, &insercion, Enemigo1);
	if (dadoVuelta)
		mensajes[*mensajeActual].darVuelta();
	(*mensajeActual)++;
}


void EnemigoModelo::actualizarInsercion() {
	insercion.modificar(posicionX, posicionY, ancho, alto);
}


void EnemigoModelo::moverEnX(int movimiento) {
	posicionX = posicionX + movimiento;
}


void EnemigoModelo::moverEnY(int movimiento) {
	posicionY = posicionY + movimiento;
}

EnemigoModelo::~EnemigoModelo() {}

