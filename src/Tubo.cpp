#include "Tubo.h"

Tubo::Tubo(Renderizador *renderizador, int posXinicial, int posYinicial, pugi::xml_document *archiConfig) {
	posicionX = posXinicial;
	posicionY = posYinicial;
	ancho = 144;
	alto = 24;

    std::string tuboBMPPath = archiConfig->child("configuracion").child("escenario")
            .child("objetos").child("tuboMetalico").child_value("imagen");

    sprite.cargar( tuboBMPPath.data(), Imagen::TIPO_OBJETO);

	encuadre.modificar(0,0,24,144);
	insercion.modificar(posXinicial, posYinicial, ancho, alto);
	textura.texturizar(renderizador, sprite);
	textura.copiarseEn(renderizador, encuadre, insercion);
}

Tubo::~Tubo() {}

