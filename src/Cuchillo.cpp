/*
 * Cuchillo.cpp
 *
 *  Created on: 18 sep. 2019
 *      Author: julio
 */

#include "Cuchillo.h"

Cuchillo::Cuchillo(){

}

Cuchillo::Cuchillo(Renderizador *renderizador, int posXinicial, int posYinicial, pugi::xml_document *archiConfig) {
	// TODO Auto-generated constructor stub
	posicionX = posXinicial;
	posicionY = posYinicial;
	ancho=66;
	alto=21;
	escaladoDeSprite = 3;

    std::string cuchilloBMPPath = archiConfig->child("configuracion").child("escenario")
            .child("objetos").child("cuchillo").child_value("imagen");

    sprite.cargar ( cuchilloBMPPath.data() );

	encuadre.modificar(0,0,66,21);
	insercion.modificar(posXinicial, posYinicial, ancho, alto);
	textura.texturizar(renderizador, sprite);
	textura.copiarseEn(renderizador, encuadre, insercion);
}

void Cuchillo::actualizar(Renderizador *renderizador) {
	posicionX=posicionX-12;
	insercion.modificar(posicionX,posicionY,ancho,alto);
	textura.copiarseEn(renderizador, encuadre, insercion);
}

void Cuchillo::refrescar(Renderizador *renderizador) {
	textura.copiarseEn(renderizador, encuadre, insercion);
}

Cuchillo::~Cuchillo() {
	// TODO Auto-generated destructor stub
}

