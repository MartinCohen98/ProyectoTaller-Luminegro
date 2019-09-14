#include "Protagonista.h"


Protagonista::Protagonista(Renderizador *renderizador){
	posicionX = 0;
	posicionY = 250;
	ancho = 140;
	alto = 280;
	estado = new EstadoJugadorFrenado();
	dadoVuelta = false;
	sprite.cargar("assets/images/sprites/cody.bmp");
	insercion.modificar(posicionX, posicionY, ancho, alto);
	textura.texturizar(renderizador, sprite);
	textura.copiarseEn(renderizador, estado->obtenerSprite(), insercion);
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
			if (posicionX < (800 - ancho))
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

void Protagonista::agacharse() {
	estado = estado->agacharse();
}

int Protagonista::moverEnY(int nuevoY) {
	int error = 0;
	posicionY = posicionY + nuevoY;
	return error;
}

void Protagonista::actualizar(Renderizador *renderizador) {
	insercion.modificar(posicionX, posicionY, ancho, alto);
	if (!dadoVuelta) {
		textura.copiarseEn(renderizador, estado->obtenerSprite(), insercion);
	} else {
		textura.copiarseInvertidoEn(renderizador,
					estado->obtenerSprite(), insercion);
	}
}

void Protagonista::moverEnX(int movimiento) {
	posicionX = posicionX + movimiento;
}

bool Protagonista::llegoAlFin(Parallax *parallax) {
	return (parallax->consultarFin() && (posicionX == (800 - ancho)));
}

Protagonista::~Protagonista(){
	delete estado;
}
