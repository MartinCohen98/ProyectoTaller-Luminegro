/*
 * Barril.cpp
 *
 *  Created on: 18 sep. 2019
 *      Author: julio
 */

#include "Barril.h"

Barril::Barril(Renderizador *renderizador, int posXinicial, int posYinicial) {
	// TODO Auto-generated constructor stub
	posicionX = posXinicial;
	posicionY = posYinicial;
	ancho=90;
	alto=96;
	escaladoDeSprite = 3;
	sprite.cargar ("assets/images/objects/barrel.bmp");
	encuadre.modificar(0,0,30,32);
	insercion.modificar(posXinicial, posYinicial, ancho, alto);
	textura.texturizar(renderizador, sprite);
	textura.copiarseEn(renderizador, encuadre, insercion);
}

void Barril::actualizar(Renderizador *renderizador) {
	textura.copiarseEn(renderizador, encuadre, insercion);
}

Barril::~Barril() {
	// TODO Auto-generated destructor stub
}

