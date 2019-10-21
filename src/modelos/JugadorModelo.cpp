#include "JugadorModelo.h"

JugadorModelo::JugadorModelo(pugi::xml_document *archiConfig) {
	posicionX = 0;
	posicionY = 250;
	movimientoEnX = 0;
	movimientoEnY = 0;
	movimientoAlSaltarEnX = 0;
	movimientoAlSaltarEnY = 0;
	escaladoDeSprite = 3;
	estado = new EstadoJugadorParado();
	estadoOriginal = new EstadoJugadorParado();
	dadoVuelta = false;
	agachado = false;

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


void JugadorModelo::realizarMovimientos(FondoModelo* fondo) {
	if (estado->puedeMoverse()) {
		actualizarPosicion(fondo);
	} else {
		if (agachado) {
			estado = estado->agacharse();
		} else {
			estado = estado->parar();
		}
	}
}


void JugadorModelo::actualizarPosicion(FondoModelo* fondo) {
	bool seMovioEnX = moverEnX(fondo);
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
	actualizarInsercion();
}


void JugadorModelo::actualizarInsercion() {
	if (!dadoVuelta) {
		insercion.modificar(posicionX, posicionY - estado->obtenerElevacion(),
				escalar(estado->obtenerAncho()), escalar(estado->obtenerAlto()));
	} else {
		insercion.modificar(posicionX - escalar(estado->obtenerAncho()) +
				escalar(estadoOriginal->obtenerAncho()),
				posicionY - estado->obtenerElevacion(),
				escalar(estado->obtenerAncho()), escalar(estado->obtenerAlto()));
	}
}

bool JugadorModelo::moverEnX(FondoModelo* fondo) {
	bool seMovio = false;
	int movimiento = movimientoEnX;
	if (estado->estaSaltando())
		movimiento = movimientoAlSaltarEnX;
	if (movimiento > 0) {
		dadoVuelta = false;
		if ((posicionX < posicionXMaxima) || fondo->consultarFin()) {
			posicionX = posicionX + movimiento;
		} else {
			fondo->mover();
		}
		seMovio = true;
	}
	if	((posicionX > 0) && (movimiento < 0)) {
		dadoVuelta = true;
		posicionX = posicionX + movimiento;
		seMovio = true;
	}
	return seMovio;
}


int JugadorModelo::escalar(int tamanio) {
	return (tamanio * escaladoDeSprite);
}


bool JugadorModelo::llegoAlFin(FondoModelo *fondo) {
	return (fondo->consultarFin() &&
			(posicionX == (800 - escalar(estado->obtenerAncho()))));
}


void JugadorModelo::enviarEncuadres(Socket *sockets, int cantidadDeSockets) {
	MensajeServidor mensaje;
	Encuadre sprite = estado->obtenerSprite();
	mensaje.generarMensaje(&sprite, &insercion, Jugador1);
	if (dadoVuelta)
		mensaje.darVuelta();
	for (int i = 0; i < cantidadDeSockets; i++) {
        if (sockets[i].getEstado() == Socket::ESTADO_CONECTADO) {
            sockets[i].enviar(&mensaje);
        }
	}
}


JugadorModelo::~JugadorModelo() {}

