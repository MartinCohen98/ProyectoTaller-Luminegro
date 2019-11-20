#include "JugadorModelo.h"
#include <iostream>


JugadorModelo::JugadorModelo(pugi::xml_document *archiConfig, int posXinicial, int posYinicial) {
	posicionX = posXinicial;
	posicionY = posYinicial;
	movimientoEnX = 0;
	movimientoEnY = 0;
	movimientoAlSaltarEnX = 0;
	movimientoAlSaltarEnY = 0;
	escaladoDeSprite = 3;
	inmortal = false;
	energia = 100;
	vidas = 3;
	puntaje = 0;
	arma = tubo;
	estado = new EstadoJugadorParado(arma);
	estadoOriginal = new EstadoJugadorParado(arma);
	dadoVuelta = false;
	agachado = false;
	desconectado = false;
	salio = false;


    std::string margenWidthString = archiConfig->child("configuracion").child("escenario").
            child_value("margenWidth");

	posicionXMaxima = 800 - std::stoi(margenWidthString);
	insercion.modificar(posicionX, posicionY,
			(estado->obtenerAncho() * escaladoDeSprite),
			(estado->obtenerAlto() * escaladoDeSprite));
}

void JugadorModelo::avanzar() {
	movimientoEnX = 10;
}

void JugadorModelo::dejarDeAvanzar() {
	movimientoEnX = 0;
}

void JugadorModelo::retroceder() {
	movimientoEnX = -10;
}

void JugadorModelo::dejarDeRetroceder() {
	movimientoEnX = 0;
}

void JugadorModelo::subir() {
	movimientoEnY = -5;
}

void JugadorModelo::dejarDeSubir() {
	movimientoEnY = 0;
}

void JugadorModelo::bajar() {
	movimientoEnY = 5;
}

void JugadorModelo::dejarDeBajar() {
	movimientoEnY = 0;
}

void JugadorModelo::agacharse() {
	estado = estado->agacharse();
	agachado = true;
}


void JugadorModelo::dejarDeAgacharse() {
	agachado = false;
}


void JugadorModelo::pegar() {
	estado = estado->pegar();
}


void JugadorModelo::saltar() {
	if (!estado->estaSaltando()) {
		movimientoAlSaltarEnX = movimientoEnX;
		movimientoAlSaltarEnY = movimientoEnY;
	}
	estado = estado->saltar();
}


void JugadorModelo::congelarse() {
    movimientoEnX = 0;
    movimientoEnY = 0;
    estado = estado->congelarse();
    desconectado = true;
}

void JugadorModelo::acuchillar(){
    estado = estado->acuchillar();
}

void JugadorModelo::apalear(){
    estado = estado->apalear();
}

void JugadorModelo::serGolpeado(){
	estado = estado->serGolpeado();
}

void JugadorModelo::desaparecer() {
	if (!salio)
		posicionY += 600;
	salio = true;
}


void JugadorModelo::descongelarse() {
    desconectado = false;
    delete estado;
    estado = new EstadoJugadorParado(arma);
    if (salio) {
    	posicionY = posicionY - 600;
    	salio = false;
    }
}

bool JugadorModelo::estaDesconectado() {
    return desconectado;
}


bool JugadorModelo::estaAtacando() {
	return estado->estaAtacando();
}


int JugadorModelo::obtenerDanio() {
	return estado->obtenerDanio();
}


int JugadorModelo::obtenerPuntosDeGolpe() {
	return estado->obtenerPuntosDeGolpe();
}


bool JugadorModelo::consultarModoTest(){
   return inmortal;
}

void JugadorModelo::activarModoTest(){
    inmortal=true;
}

void JugadorModelo::desactivarModoTest(){
    inmortal=false;
}

tipoDeArma JugadorModelo::consultarArma(){
	return arma;
}

bool JugadorModelo::moverEnY() {
	bool seMovio = false;
	int movimiento = movimientoEnY;
	if (estado->estaSaltando())
		movimiento = movimientoAlSaltarEnY;
	if (((posicionY > 170) && (movimiento < 0)) ||
		((posicionY < 300) && (movimiento > 0))) {
		posicionY = posicionY + movimiento;
		seMovio = true;
	}
	return seMovio;
}


void JugadorModelo::realizarMovimientos(FondoModelo* fondo, bool rezagado,
										Colisionador* colisionador) {
	posicionXAnterior = posicionX;
	posicionYAnterior = posicionY;
	if (estado->puedeMoverse()) {
		actualizarPosicion(fondo, rezagado);
    } else {
    	if (agachado) {
    		estado = estado->agacharse();
    	} else {
    		estado = estado->parar();
    	}
	}
	checkearColisiones(colisionador);
}


void JugadorModelo::actualizarPosicion(FondoModelo* fondo, bool rezagado) {
	bool seMovioEnX = moverEnX(fondo, rezagado);
	bool seMovioEnY = moverEnY();
	if (seMovioEnX || seMovioEnY) {
		estado = estado->avanzar();
	} else {
		if (agachado) {
			estado = estado->agacharse();
		} else {
			estado = estado->parar();
		}
	}
}


void JugadorModelo::checkearColisiones(Colisionador* colisionador) {
	actualizarInsercion(false);
	if (colisionador->colisiona(this)) {
		posicionX = posicionXAnterior;
		posicionY = posicionYAnterior;
		actualizarInsercion(false);
	}
}


void JugadorModelo::actualizarInsercion(bool conElevacion) {
	int elevacion = 0;
	if (estado->estaSaltando())
		elevacion = 30;
	if (conElevacion)
		elevacion = estado->obtenerElevacion();
	if (!dadoVuelta) {
		insercion.modificar(posicionX, posicionY - elevacion,
				escalar(estado->obtenerAncho()), escalar(estado->obtenerAlto()));
	} else {
		insercion.modificar(posicionX - escalar(estado->obtenerAncho()) +
				escalar(estadoOriginal->obtenerAncho()),
				posicionY - elevacion, escalar(estado->obtenerAncho()),
				escalar(estado->obtenerAlto()));
	}
}

bool JugadorModelo::moverEnX(FondoModelo* fondo, bool rezagado) {
	bool seMovio = false;
	int movimiento = movimientoEnX;
	if (estado->estaSaltando())
		movimiento = movimientoAlSaltarEnX;
	if (movimiento > 0) {
		dadoVuelta = false;
		if ((posicionX < posicionXMaxima) || fondo->consultarFin()) {
			posicionX = posicionX + movimiento;
		} else {
            if (!rezagado) {
              fondo->mover();
           }
		}
		seMovio = true;
	}
	if	((posicionX > 0) && (movimiento < 0)) {
		dadoVuelta = true;
		posicionX = posicionX + movimiento;
		if (posicionX < 0)
			posicionX = 0;
		seMovio = true;
	}
	return seMovio;
}


int JugadorModelo::escalar(int tamanio) {
	return (tamanio * escaladoDeSprite);
}


bool JugadorModelo::llegoAlFin(FondoModelo *fondo) {
	return (fondo->consultarFin() &&
			(posicionX >= 800));
}


void JugadorModelo::movidaDePantalla(FondoModelo* fondo) {
	if (!movioAlFondo(fondo)) {
		posicionX = posicionX - 10;
		if (posicionX < 0)
			posicionX = 0;
	}
}


bool JugadorModelo::movioAlFondo(FondoModelo* fondo) {
	bool retorno = false;
	int movimiento = movimientoEnX;
	if (estado->estaSaltando()) {
		movimiento = movimientoAlSaltarEnX;
	}
	if ((movimiento < 0) && (posicionX >= posicionXMaxima) &&
				fondo->consultarFin()) {
		retorno = true;
	}
	return retorno;
}


void JugadorModelo::generarMensaje(MensajeServidor* mensajes, int* mensajeActual,
		int numeroSprite) {
	actualizarInsercion(true);
	Encuadre sprite = estado->obtenerSprite();
	tipoDeSprite tipo;
	switch (numeroSprite) {
		case 1:		tipo = Jugador1;
					break;
		case 2:		tipo = Jugador2;
					break;
		case 3:		tipo = Jugador3;
					break;
		case 4:		tipo = Jugador4;
					break;
	}
	mensajes[*mensajeActual].generarMensaje(&sprite, &insercion, tipo);
	mensajes[*mensajeActual].agregarPosicionY(posicionY +
									escalar(estadoOriginal->obtenerAlto()));
	if (dadoVuelta)
		mensajes[*mensajeActual].darVuelta();
	actualizarInsercion(false);
	(*mensajeActual)++;
}


JugadorModelo::~JugadorModelo() {}

