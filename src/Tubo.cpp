/*
 * Tubo.cpp
 *
 *  Created on: 18 sep. 2019
 *      Author: julio
 */

#include "Tubo.h"

Tubo::Tubo(Renderizador *renderizador, int posXinicial, int posYinicial) {
	// TODO Auto-generated constructor stub
	posicionX = posXinicial;
	posicionY = posYinicial;
	ancho=144;
	alto=24;
	escaladoDeSprite = 3;
	sprite.cargar ("assets/images/objects/metalTube.bmp");
	encuadre.modificar(0,0,24,144);
	insercion.modificar(posXinicial, posYinicial, ancho, alto);
	textura.texturizar(renderizador, sprite);
	textura.copiarseEn(renderizador, encuadre, insercion);
}

void Tubo::actualizar(Renderizador *renderizador) {
	posicionX=posicionX-12;
	insercion.modificar(posicionX,posicionY,ancho,alto);
	textura.copiarseEn(renderizador, encuadre, insercion);
}

void Tubo::refrescar(Renderizador *renderizador) {
	textura.copiarseEn(renderizador, encuadre, insercion);
}

Tubo::~Tubo() {
	// TODO Auto-generated destructor stub
}

