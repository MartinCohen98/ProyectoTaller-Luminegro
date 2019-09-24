/*
 * Tubo.cpp
 *
 *  Created on: 18 sep. 2019
 *      Author: julio
 */

#include "Tubo.h"

Tubo::Tubo(){

}

Tubo::Tubo(Renderizador *renderizador, int posXinicial, int posYinicial, pugi::xml_document *archiConfig) {
	// TODO Auto-generated constructor stub
	posicionX = posXinicial;
	posicionY = posYinicial;
	ancho=144;
	alto=24;
	escaladoDeSprite = 3;

    std::string tuboBMPPath = archiConfig->child("configuracion").child("escenario")
            .child("objetos").child("tuboMetalico").child_value("imagen");

    sprite.cargar( tuboBMPPath.data(), Imagen::TIPO_OBJETO);

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

