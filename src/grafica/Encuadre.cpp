#include "Encuadre.h"

Encuadre::Encuadre() {}

Encuadre::Encuadre(int desplazamientoX, int desplazamientoY,
				   int resolucionX, int resolucionY){
	encuadre = {desplazamientoX, desplazamientoY, resolucionX, resolucionY};
}

SDL_Rect Encuadre::get() {
	return encuadre;
}

int Encuadre::getX(){
	return encuadre.x;
}

int Encuadre::getY() const{
	return encuadre.y;
}

int Encuadre::getAncho(){
	return encuadre.w;
}

int Encuadre::getAlto() const{
	return encuadre.h;
}

int Encuadre::modificar(int desplazamientoX, int desplazamientoY,
						int resolucionX, int resolucionY){
	encuadre = {desplazamientoX, desplazamientoY, resolucionX, resolucionY};
	return 0;
}

Encuadre::~Encuadre() {}

void Encuadre::setX(int x) {
    encuadre.x = x;
}

void Encuadre::setY(int y) {
    encuadre.y = y;
}

void Encuadre::setAncho(int w) {
    encuadre.w = w;
}

void Encuadre::setAlto(int h) {
    encuadre.h = h;
}
