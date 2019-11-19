#include "EnemigoModelo.h"

EnemigoModelo::EnemigoModelo(){

}

EnemigoModelo::EnemigoModelo(int posXinicial, int posYinicial, tipoDeSprite tipo) {
	posicionX = posXinicial;
	posicionY = posYinicial;
	ancho = 140;
	alto = 280;
	energia=100;
	tipoEnemigo=tipo;
	estado = new EstadoEnemigoParado();
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

void EnemigoModelo::pegar(){
    estado = estado->pegar();
}

void EnemigoModelo::morir(){
    estado = estado->morir();
}

void EnemigoModelo::acuchillar(){
    estado = estado->acuchillar();
}

void EnemigoModelo::apalear(){
    estado = estado->apalear();
}

void EnemigoModelo::serGolpeado(){
	estado = estado->serGolpeado();
}

void EnemigoModelo::avanzarDiagArriba(int tope){
    dadoVuelta = false;
    moverEnX(5);
    if (posicionY > tope) {
        moverEnY(-1);
        estado = estado->avanzar();
    } else {
        parar();
        estado = estado->parar();
    }
    actualizarInsercion();
}

void EnemigoModelo::avanzarDiagAbajo(int tope){
    dadoVuelta = false;
    moverEnX(5);
    if (posicionY < tope) {
        moverEnY(1);
        estado = estado->avanzar();
    } else {
        parar();
        estado = estado->parar();
    }
    actualizarInsercion();
}

void EnemigoModelo::retrocederDiagArriba(int tope){
    dadoVuelta = true;
    moverEnX(-5);
    if (posicionY > tope) {
        moverEnY(-1);
        estado = estado->avanzar();
    } else {
        parar();
        estado = estado->parar();
    }
    actualizarInsercion();
}

void EnemigoModelo::retrocederDiagAbajo(int tope){
    dadoVuelta = true;
    if (posicionY < tope) {
        moverEnX(-5);
        moverEnY(1);
        estado = estado->avanzar();
    } else {
        parar();
        estado = estado->parar();
    }
    actualizarInsercion();
}

void EnemigoModelo::trasladarse(int destinoX,int destinoY) {
    bool atras = false;
    bool abajo = false;
    if (destinoX < posicionX)
        atras = true;
    if (destinoY > posicionY)
        abajo = true;
    if (atras & abajo) {
        retrocederDiagAbajo(destinoY);
        if (posicionY==destinoY)
            retroceder();
    }
    if (atras & !abajo) {
        retrocederDiagArriba(destinoY);
        if (posicionY==destinoY)
            retroceder();
    }
    if (!atras & abajo) {
        avanzarDiagAbajo(destinoY);
        if (posicionY==destinoY)
            avanzar();
    }
    if (!atras & !abajo) {
        avanzarDiagArriba(destinoY);
        if (posicionY==destinoY)
            avanzar();
    }
    if (abajo)
    	bajar();
    if (!abajo)
    	subir();
}

void EnemigoModelo::patrullar(){
    if (darPosicionY()==bordeSuperior)
        estaBajando();
    if (darPosicionY()==bordeInferior)
        estaSubiendo();
    if (!consultarSubiendo()){
        if (consultarDadoVuelta())
            retrocederDiagAbajo(bordeInferior);
        else
            avanzarDiagAbajo(bordeInferior);
      }
    else {
        if (consultarDadoVuelta())
            retrocederDiagArriba(bordeSuperior);
        else
            avanzarDiagArriba(bordeSuperior);
      }
}

void EnemigoModelo::modificarJugadorObjetivo(int objetivo){
	jugadorObjetivo=objetivo;
}

int EnemigoModelo::consultarJugadorObjetivo(){
	return jugadorObjetivo;
}

void EnemigoModelo::atacar(int x,int y){
	//if (posicionY==250 || posicionY==200 || posicionY==300)
	if (posicionY==y)
	  pegar();
	trasladarse(x-110,y+20);
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


void EnemigoModelo::guardarPosicionesActuales() {
	posicionXAnterior = posicionX;
	posicionYAnterior = posicionY;
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

void EnemigoModelo::realizarMovimientos(Colisionador* colisionador) {
	if (estado->puedeMoverse()) {
//		actualizarPosicion(fondo, rezagado);
    } else {
    		estado = estado->parar();
	}
	checkearColisiones(colisionador);
}


void EnemigoModelo::checkearColisiones(Colisionador* colisionador) {
	actualizarInsercion();
	if (colisionador->colisiona(&insercion)) {
		posicionX = posicionXAnterior;
		posicionY = posicionYAnterior;
		actualizarInsercion();
	}
}


EnemigoModelo::~EnemigoModelo() {}

