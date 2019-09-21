/*
 * Barril.cpp
 *
 *  Created on: 18 sep. 2019
 *      Author: julio
 */

#include "Barril.h"

Barril::Barril(){

}

Barril::Barril(Renderizador *renderizador, int posXinicial, int posYinicial, pugi::xml_document *archiConfig) {
	// TODO Auto-generated constructor stub
	posicionX = posXinicial;
	posicionY = posYinicial;
	ancho=90;
	alto=96;
	escaladoDeSprite = 3;

    std::string barrilBMPPath = archiConfig->child("configuracion").child("escenario")
            .child("objetos").child("barril").child_value("imagen");

	sprite.cargar ( barrilBMPPath.data() );

	encuadre.modificar(0,0,30,32);
	insercion.modificar(posXinicial, posYinicial, ancho, alto);
	textura.texturizar(renderizador, sprite);
	textura.copiarseEn(renderizador, encuadre, insercion);
}

void Barril::actualizar(Renderizador *renderizador) {
	posicionX=posicionX-12;
	insercion.modificar(posicionX,posicionY,ancho,alto);
	textura.copiarseEn(renderizador, encuadre, insercion);
}

void Barril::refrescar(Renderizador *renderizador) {
	textura.copiarseEn(renderizador, encuadre, insercion);
}


Barril::~Barril() {
	// TODO Auto-generated destructor stub
}

