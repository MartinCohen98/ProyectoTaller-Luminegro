#include "Protagonista.h"


Protagonista::Protagonista(Renderizador *renderizador){
	posicionX = 0;
	posicionY = 200;
	ancho = 175;
	alto = 273;
	estado = new EstadoJugadorFrenado();
	sprite.cargar("assets/images/sprites/cody.bmp");
	insercion.modificar(posicionX, posicionY, ancho, alto);
	textura.texturizar(renderizador, sprite);
	textura.copiarseEn(renderizador, estado->obtenerSprite(), insercion);
}

int Protagonista::avanzar(Parallax *parallax) {
	int error = 0;
	estado = estado->avanzar();
	if (posicionX < 500) {
		moverEnX(10);
	} else {
		parallax->mover();
	}
	return error;
}

void Protagonista::parar() {
	estado = estado->parar();
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
	textura.copiarseEn(renderizador, estado->obtenerSprite(), insercion);
}

void Protagonista::moverEnX(int movimiento) {
	posicionX = posicionX + movimiento;
}

Protagonista::~Protagonista(){
	delete estado;
}
