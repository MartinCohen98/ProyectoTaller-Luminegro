#include "EnemigoModelo.h"

EnemigoModelo::EnemigoModelo(int posXinicial, int posYinicial, tipoDeSprite tipo) {
	posicionX = posXinicial;
	posicionY = posYinicial;
	ancho = 140;
	alto = 280;
	energia=100;
	tipoEnemigo=tipo;
	estado = new EstadoEnemigoParado(0,0,47,78);
	dadoVuelta = false;
	subiendo=false;
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
    actualizarInsercion();
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
		moverEnY(-1);
	} else {
	    parar();
		estado = estado->parar();
	}
	actualizarInsercion();
}

void EnemigoModelo::bajar() {
	if (posicionY < 320) {
		moverEnY(1);
        estado = estado->avanzar();
	} else {
	    parar();
		estado = estado->parar();
	}
	actualizarInsercion();
}

void EnemigoModelo::agacharse() {
	estado = estado->agacharse();
}

void EnemigoModelo::avanzarDiagArriba(){
    dadoVuelta = false;
    moverEnX(5);
    if (posicionY > 180) {
        moverEnY(-1);
        estado = estado->avanzar();
    } else {
        parar();
        estado = estado->parar();
    }
    actualizarInsercion();
}

void EnemigoModelo::avanzarDiagAbajo(){
    dadoVuelta = false;
    moverEnX(5);
    if (posicionY < 320) {
        moverEnY(1);
        estado = estado->avanzar();
    } else {
        parar();
        estado = estado->parar();
    }
    actualizarInsercion();
}

void EnemigoModelo::retrocederDiagArriba(){
    dadoVuelta = true;
    moverEnX(-5);
    if (posicionY > 180) {
        moverEnY(-1);
        estado = estado->avanzar();
    } else {
        parar();
        estado = estado->parar();
    }
    actualizarInsercion();
}

void EnemigoModelo::retrocederDiagAbajo(){
    dadoVuelta = true;
    if (posicionY < 320) {
        moverEnX(-5);
        moverEnY(1);
        estado = estado->avanzar();
    } else {
        parar();
        estado = estado->parar();
    }
    actualizarInsercion();
}

void EnemigoModelo::trasladarse(int destinoX,int destinoY){

}

void EnemigoModelo::patrullar(){
    switch(darPosicionY()) {
        case 180:
            estaBajando();
            break;
        case 320:
            estaSubiendo();
    }
    if (!consultarSubiendo()){
        if (consultarDadoVuelta())
            retrocederDiagAbajo();
        else
            avanzarDiagAbajo();
      }
    else {
        if (consultarDadoVuelta())
            retrocederDiagArriba();
        else
            avanzarDiagArriba();
      }
}


void EnemigoModelo::estaSubiendo(){
    subiendo=true;
}

void EnemigoModelo::estaBajando(){
    subiendo=false;
}

bool EnemigoModelo::consultarSubiendo(){
    return subiendo;
}

void EnemigoModelo::retrocesoDePantalla() {
	posicionX = posicionX - 12;
}


void EnemigoModelo::generarMensaje(MensajeServidor* mensajes, int* mensajeActual) {
	Encuadre sprite = estado->obtenerSprite();
	mensajes[*mensajeActual].generarMensaje(&sprite, &insercion, tipoEnemigo);
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

