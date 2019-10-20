#include "Barril.h"


Barril::Barril(Renderizador *renderizador, int posXinicial, int posYinicial, pugi::xml_document *archiConfig) {
	posicionX = posXinicial;
	posicionY = posYinicial;
	ancho = 90;
	alto = 96;

    std::string barrilBMPPath = archiConfig->child("configuracion").child("escenario")
            .child("objetos").child("barril").child_value("imagen");

	sprite.cargar( barrilBMPPath.data(), Imagen::TIPO_OBJETO);

	encuadre.modificar(0, 0, 30, 32);
	insercion.modificar(posXinicial, posYinicial, ancho, alto);
	textura.texturizar(renderizador, sprite);
	textura.copiarseEn(renderizador, encuadre, insercion);
}

Barril::~Barril() {}

