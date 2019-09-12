#include "Protagonista.h"


Protagonista::Protagonista(Renderizador *renderizador){
	posicionX = 0;
	posicionY = 120;
	sprite.cargar("assets/images/sprites/jake.bmp");
	frameActual.Modificar(0, 0, 50, 78);
	insercion.Modificar(posicionX, posicionY, 50, 74);
	textura.texturizar(renderizador, sprite);
	textura.copiarseEn(renderizador, frameActual, insercion);
}

int Protagonista::CambiarPosicion(Renderizador *renderizador, int nuevoX, int nuevoY){
	int error = 0;
	posicionX = posicionX + nuevoX;
	posicionY = posicionY + nuevoY;
	insercion.Modificar(posicionX, posicionY, 140, 250);
	textura.texturizar(renderizador, sprite);
	textura.copiarseEn(renderizador, frameActual, insercion);
	return error;
}


Protagonista::~Protagonista(){

}
