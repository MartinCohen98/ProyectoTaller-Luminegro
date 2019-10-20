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

int Encuadre::getY(){
	return encuadre.y;
}

int Encuadre::getAncho(){
	return encuadre.w;
}

int Encuadre::getAlto(){
	return encuadre.h;
}

int Encuadre::modificar(int desplazamientoX, int desplazamientoY,
						int resolucionX, int resolucionY){
	encuadre = {desplazamientoX, desplazamientoY, resolucionX, resolucionY};
	return 0;
}

Encuadre::~Encuadre() {}
