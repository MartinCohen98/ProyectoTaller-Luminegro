#include "Protagonista.h"


Protagonista::Protagonista(Renderizador *renderizador, pugi::xml_document *archiConfig){
	posicionX = 0;
	posicionY = 250;
	escalado = 3;
	estado = new EstadoJugadorParado();
	estadoOriginal = new EstadoJugadorParado();
	dadoVuelta = false;

	// Leo del XML la ubicación del BMP del protagonista
    std::string protagonistaBMPPath = archiConfig->child("configuracion").child("escenario")
            .child("protagonista").child_value("imagen");

    Imagen sprite;
	sprite.cargar( protagonistaBMPPath.data() );

	insercion.modificar(posicionX, posicionY,
			(estado->obtenerAncho() * escalado),
			(estado->obtenerAlto() * escalado));
	textura.texturizar(renderizador, sprite);
	textura.copiarseEn(renderizador, estado->obtenerSprite(), insercion);
	this->archiConfig = archiConfig;
}

int Protagonista::avanzar(Parallax *parallax) {
	dadoVuelta = false;
	int error = 0;
	estado = estado->avanzar();
	if (posicionX < 500) {
		moverEnX(10);
	} else {
		if (!parallax->consultarFin()) {
			parallax->mover();
		} else {
			if (posicionX < (800 - escalar(estado->obtenerAncho())))
				moverEnX(10);
		}
	}
	return error;
}

void Protagonista::parar() {
	estado = estado->parar();
}

void Protagonista::retroceder() {
	dadoVuelta = true;
	if (posicionX > 0) {
		estado = estado->avanzar();
		moverEnX(-10);
	} else {
		estado = estado->parar();
	}
}

void Protagonista::subir() {
	if (posicionY > 170) {
		estado = estado->avanzar();
		moverEnY(-5);
	} else {
		estado = estado->parar();
	}
}

void Protagonista::bajar() {
	if (posicionY < 300) {
		estado = estado->avanzar();
		moverEnY(5);
	} else {
		estado = estado->parar();
	}
}

void Protagonista::agacharse() {
	estado = estado->agacharse();
}

void Protagonista::pegar() {
	estado = estado->pegar();
}

int Protagonista::moverEnY(int nuevoY) {
	int error = 0;
	posicionY = posicionY + nuevoY;
	return error;
}

void Protagonista::actualizar(Renderizador *renderizador) {
	if (!dadoVuelta) {
		insercion.modificar(posicionX, posicionY,
				escalar(estado->obtenerAncho()), escalar(estado->obtenerAlto()));
		textura.copiarseEn(renderizador, estado->obtenerSprite(), insercion);
	} else {
		insercion.modificar(posicionX - escalar(estado->obtenerAncho()) +
				escalar(estadoOriginal->obtenerAncho()), posicionY,
				escalar(estado->obtenerAncho()), escalar(estado->obtenerAlto()));
		textura.copiarseInvertidoEn(renderizador,
					estado->obtenerSprite(), insercion);
	}
}

void Protagonista::moverEnX(int movimiento) {
	posicionX = posicionX + movimiento;
}

int Protagonista::escalar(int tamanio) {
	return (tamanio * escalado);
}

bool Protagonista::llegoAlFin(Parallax *parallax) {
	return (parallax->consultarFin() &&
			(posicionX == (800 - escalar(estado->obtenerAncho()))));
}

Protagonista::~Protagonista(){
	delete estado;
}
