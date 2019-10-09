#include "Protagonista.h"

Protagonista::Protagonista(){

}

Protagonista::Protagonista(Renderizador *renderizador, pugi::xml_document *archiConfig){
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

	// Leo del XML la ubicación del BMP del protagonista
    std::string protagonistaBMPPath = archiConfig->child("configuracion").child("escenario")
            .child("protagonistas").child("protagonista1").child_value("imagen");

    Imagen sprite;
	sprite.cargar( protagonistaBMPPath.data(), Imagen::TIPO_PERSONAJE );

    std::string margenWidthString = archiConfig->child("configuracion").child("escenario").
            child_value("margenWidth");

    this->posicionXMaxima = 800 - std::stoi(margenWidthString);

    insercion.modificar(posicionX, posicionY,
			(estado->obtenerAncho() * escaladoDeSprite),
			(estado->obtenerAlto() * escaladoDeSprite));
	textura.texturizar(renderizador, sprite);
	textura.copiarseEn(renderizador, estado->obtenerSprite(), insercion);
	this->archiConfig = archiConfig;
}

void Protagonista::avanzar() {
	movimientoEnX = 10;
}

void Protagonista::dejarDeAvanzar() {
	movimientoEnX = 0;
}

void Protagonista::retroceder() {
	movimientoEnX = -10;
}

void Protagonista::dejarDeRetroceder() {
	movimientoEnX = 0;
}

void Protagonista::subir() {
	movimientoEnY = -5;
}

void Protagonista::dejarDeSubir() {
	movimientoEnY = 0;
}

void Protagonista::bajar() {
	movimientoEnY = 5;
}

void Protagonista::dejarDeBajar() {
	movimientoEnY = 0;
}

void Protagonista::agacharse() {
	estado = estado->agacharse();
	agachado = true;
}

void Protagonista::dejarDeAgacharse() {
	agachado = false;
}

void Protagonista::pegar() {
	estado = estado->pegar();
}

void Protagonista::saltar() {
	if (!estado->estaSaltando()) {
		movimientoAlSaltarEnX = movimientoEnX;
		movimientoAlSaltarEnY = movimientoEnY;
	}
	estado = estado->saltar();
}

bool Protagonista::moverEnY() {
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

void Protagonista::realizarMovimientos(Fondo* fondo) {
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

void Protagonista::actualizar(Renderizador *renderizador) {
	if (!dadoVuelta) {
		insercion.modificar(posicionX, posicionY - estado->obtenerElevacion(),
				escalar(estado->obtenerAncho()), escalar(estado->obtenerAlto()));
		textura.copiarseEn(renderizador, estado->obtenerSprite(), insercion);
	} else {
		insercion.modificar(posicionX - escalar(estado->obtenerAncho()) +
				escalar(estadoOriginal->obtenerAncho()),
				posicionY - estado->obtenerElevacion(),
				escalar(estado->obtenerAncho()), escalar(estado->obtenerAlto()));
		textura.copiarseInvertidoEn(renderizador,
					estado->obtenerSprite(), insercion);
	}
}

void Protagonista::actualizarPosicion(Fondo* fondo) {
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
}

bool Protagonista::moverEnX(Fondo* fondo) {
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

int Protagonista::escalar(int tamanio) {
	return (tamanio * escaladoDeSprite);
}

bool Protagonista::llegoAlFin(Fondo *fondo) {
	return (fondo->consultarFin() &&
			(posicionX == (800 - escalar(estado->obtenerAncho()))));
}

Protagonista::~Protagonista(){
	delete estado;
}
