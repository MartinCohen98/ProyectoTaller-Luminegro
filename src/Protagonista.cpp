/*
 * Protagonista.cpp
 *
 *  Created on: 11 sep. 2019
 *      Author: julio
 */

#include "Protagonista.h"


Protagonista::Protagonista(Renderizador *renderizador){
	posicionX=0;
	posicionY=120;
	int resultado = sprite.cargar("assets/images/sprites/jake.bmp");
	frameActual.Modificar(0,-100,140,300);
	insercion.Modificar(posicionX,posicionY,50,74);
	textura.texturizar(renderizador,sprite);
	textura.copiarseEn(renderizador,frameActual,insercion);
}

int Protagonista::CambiarPosicion(Renderizador *renderizador, int nuevoX, int nuevoY){
	int error = 0;
	posicionX=posicionX+nuevoX;
	posicionY=posicionY+nuevoY;
	insercion.Modificar(posicionX,posicionY,140,250);
	textura.texturizar(renderizador,sprite);
	textura.copiarseEn(renderizador,frameActual,insercion);
	return error;
}


Protagonista::~Protagonista(){

}
