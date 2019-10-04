/*
 * Elemento.cpp
 *
 *  Created on: 2 oct. 2019
 *      Author: julio
 */

#include "Elemento.h"

Elemento::Elemento() {
	// TODO Auto-generated constructor stub

}

void Elemento::movidaDePantalla() {
	posicionX = posicionX - 12;
	insercion.modificar(posicionX,posicionY,ancho,alto);
}

void Elemento::actualizar(Renderizador *renderizador) {
	textura.copiarseEn(renderizador, encuadre, insercion);
}

Elemento::~Elemento() {
	// TODO Auto-generated destructor stub
}

