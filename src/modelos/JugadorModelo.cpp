#include "JugadorModelo.h"
#include <iostream>


JugadorModelo::JugadorModelo(pugi::xml_document *archiConfig, int posXinicial,
								int posYinicial, tipoDeSprite tipoNuevo) {
	posicionX = posXinicial;
	posicionY = posYinicial;
	tipo = tipoNuevo;
	movimientoEnX = 0;
	movimientoEnY = 0;
	movimientoAlSaltarEnX = 0;
	movimientoAlSaltarEnY = 0;
	escaladoDeSprite = 3;
	inmortal = false;
	energia = 100;
	vidas = 3;
	puntaje = 0;
	arma = desarmado;
	estado = new EstadoJugadorParado(arma);
	estadoOriginal = new EstadoJugadorParado(arma);
	dadoVuelta = false;
	agachado = false;
	desconectado = false;
	salio = false;
	golpesDeArma = 0;
	derrotado = false;


    std::string margenWidthString = archiConfig->child("configuracion")
    		.child("escenario").child_value("margenWidth");

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
    ejecutarSonidoGolpeTiro = true;
	estado = estado->pegar();
}


void JugadorModelo::saltar() {
	if (!estado->estaSaltando()) {
		movimientoAlSaltarEnX = movimientoEnX;
		movimientoAlSaltarEnY = movimientoEnY;
        ejecutarSonidoSalto = true;
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
    ejecutarSonidoGolpeTiro = true;
    estado = estado->acuchillar();
}

void JugadorModelo::apalear(){
    ejecutarSonidoGolpeTiro = true;
    estado = estado->apalear();
}

void JugadorModelo::serGolpeado(){
	estado = estado->serGolpeado();
}

void JugadorModelo::desaparecer() {
	if (!salio || posicionY < 600)
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

void JugadorModelo::morir(){
    ejecutarSonidoCaida = true;
    estado = estado->morir();
    actualizarInsercion(false);
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

void JugadorModelo::sumarPuntos(int puntos){
	puntaje+= puntos;
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

int JugadorModelo::recibirDanioDe(Colisionable* colisionable) {
	if ((colisionable->obtenerTipo() != Jugador1) &&
				(colisionable->obtenerTipo() != Jugador2) &&
				(colisionable->obtenerTipo() != Jugador3) &&
				(colisionable->obtenerTipo() != Jugador4)) {
		if(!inmortal)
			energia -= colisionable->obtenerDanio();
		serGolpeado();
		if (energia <= 0){
			morir();
			vidas--;
			if (vidas>0) {
				energia = 100;
			} else {
				derrotado = true;
				congelarse();
				desaparecer();
			}
		}
	}
	return 0;
}

bool JugadorModelo::consultarDerrotado(){
	return derrotado;
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
    		Colisionable* punteroArma = colisionador->levantarSiHay(this);
    		if (punteroArma != NULL) {
    			golpesDeArma = 3;
    			arma = punteroArma->obtenerTipoDeArma();
    			estado->asignarArma(arma);
    		}
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
	tipoDeSprite tipoColision;
	if (colisionador->colisiona(this, &tipoColision)) {
		if (ejecutarSonidoGolpeTiro) {
			ejecutarSonidoGolpeImpacto = true;
			if (!estado->estaPateando()) {
				golpesDeArma--;
				if (golpesDeArma == 0) {
					arma = desarmado;
					estado->asignarArma(arma);
				}
			}
		}
		posicionX = posicionXAnterior;
		posicionY = posicionYAnterior;
		actualizarInsercion(false);
	}
}


void JugadorModelo::actualizarInsercion(bool conElevacion) {
	int elevacion = 0;
	int diferenciaEnX = 0;
	if (estado->estaSaltando() && !estado->estaPateando())
		elevacion = 30;
	if (estado->estaSaltando() && estado->estaPateando() && !conElevacion)
		diferenciaEnX = 40;
	if (conElevacion)
		elevacion = estado->obtenerElevacion();
	if (!dadoVuelta) {
		insercion.modificar(posicionX, posicionY - elevacion,
				escalar(estado->obtenerAncho()) - diferenciaEnX,
				escalar(estado->obtenerAlto()));
	} else {
		insercion.modificar(posicionX - escalar(estado->obtenerAncho()) +
				escalar(estadoOriginal->obtenerAncho()) - diferenciaEnX,
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


bool JugadorModelo::puedeAtacarA(tipoDeSprite tipoSprite) {
	if ((tipo == Jugador1) || (tipo == Jugador2) || (tipo == Jugador3)
			|| (tipo == Jugador4)) {
		return false;
	}
	return true;
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
    mensajes[*mensajeActual].setSonidoEjecutarGolpeTiro(ejecutarSonidoGolpeTiro);
    mensajes[*mensajeActual].setSonidoEjecutarGolpeImpacto(ejecutarSonidoGolpeImpacto);
    mensajes[*mensajeActual].setSonidoEjecutarSalto(ejecutarSonidoSalto);
    mensajes[*mensajeActual].setSonidoEjecutarCaida(ejecutarSonidoCaida);

	mensajes[*mensajeActual].setInfoJugador(
			InfoJugador(energia, vidas, puntaje, (!salio && !desconectado)));
	//Si no está ni desconectado ni salió, está conectado

    ejecutarSonidoGolpeTiro = false;
    ejecutarSonidoGolpeImpacto = false;
    ejecutarSonidoSalto = false;
    ejecutarSonidoCaida = false;


	mensajes[*mensajeActual].agregarPosicionY(posicionY +
									escalar(estadoOriginal->obtenerAlto()));
	if (dadoVuelta)
		mensajes[*mensajeActual].darVuelta();
	actualizarInsercion(false);
	(*mensajeActual)++;
}


JugadorModelo::~JugadorModelo() {}

void JugadorModelo::reasignarPosicion(int x, int y) {
    posicionX = x;
    posicionY = y;
}

