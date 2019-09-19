/*
 * Caja.cpp
 *
 *  Created on: 18 sep. 2019
 *      Author: julio
 */

#include "Caja.h"

Caja::Caja(Renderizador *renderizador, int posXinicial, int posYinicial) {
	// TODO Auto-generated constructor stub
	posicionX = posXinicial;
	posicionY = posYinicial;
	ancho=96;
	alto=160;
	escaladoDeSprite = 3;
	sprite.cargar ("assets/images/objects/box.bmp");
	encuadre.modificar(0,0,96,160);
	insercion.modificar(posXinicial, posYinicial, ancho, alto);
	textura.texturizar(renderizador, sprite);
	textura.copiarseEn(renderizador, encuadre, insercion);
}

void Caja::actualizar(Renderizador *renderizador) {
	textura.copiarseEn(renderizador, encuadre, insercion);
}

Caja::~Caja() {
	// TODO Auto-generated destructor stub
}

