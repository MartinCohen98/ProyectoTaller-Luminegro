/*
 * Encuadre.cpp
 *
 *  Created on: 10 sep. 2019
 *      Author: julio
 */

#include "Encuadre.h"

Encuadre::Encuadre() {}

Encuadre::Encuadre(int desplazamientoX, int desplazamientoY,
				   int resolucionX, int resolucionY){
	encuadre = {desplazamientoX, desplazamientoY, resolucionX, resolucionY};
}

SDL_Rect Encuadre::get() {
	return encuadre;
}

int Encuadre::Modificar(int desplazamientoX, int desplazamientoY,
						int resolucionX, int resolucionY){
	encuadre = {desplazamientoX, desplazamientoY, resolucionX, resolucionY};
	return 0;
}

Encuadre::~Encuadre() {}
