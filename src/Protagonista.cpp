#include "Protagonista.h"


Protagonista::Protagonista(Renderizador *renderizador){
	posicionX = 0;
	posicionY = 200;
	ancho = 175;
	alto = 273;
	sprite.cargar("assets/images/sprites/jake.bmp");
	frameActual.modificar(0, 0, 50, 78);
	insercion.modificar(posicionX, posicionY, ancho, alto);
	textura.texturizar(renderizador, sprite);
	textura.copiarseEn(renderizador, frameActual, insercion);
}

int Protagonista::avanzar(Parallax *parallax) {
	int error = 0;
	if (posicionX < 500) {
		moverEnX(10);
	} else {
		parallax->mover();
	}
	return error;
}

void Protagonista::retroceder() {
	if (posicionX > 0) {
		moverEnX(-10);
	}
}

int Protagonista::moverEnY(int nuevoY) {
	int error = 0;
	posicionY = posicionY + nuevoY;
	return error;
}

void Protagonista::actualizar(Renderizador *renderizador) {
	insercion.modificar(posicionX, posicionY, ancho, alto);
	textura.texturizar(renderizador, sprite);
	textura.copiarseEn(renderizador, frameActual, insercion);
}

void Protagonista::moverEnX(int movimiento) {
	posicionX = posicionX + movimiento;
}

Protagonista::~Protagonista(){

}
