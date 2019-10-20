#include "Cuchillo.h"

Cuchillo::Cuchillo(Renderizador *renderizador, int posXinicial, int posYinicial, pugi::xml_document *archiConfig) {
	posicionX = posXinicial;
	posicionY = posYinicial;
	ancho = 66;
	alto = 21;

    std::string cuchilloBMPPath = archiConfig->child("configuracion").child("escenario")
            .child("objetos").child("cuchillo").child_value("imagen");

    sprite.cargar( cuchilloBMPPath.data(), Imagen::TIPO_OBJETO);

	encuadre.modificar(0,0,66,21);
	insercion.modificar(posXinicial, posYinicial, ancho, alto);
	textura.texturizar(renderizador, sprite);
	textura.copiarseEn(renderizador, encuadre, insercion);
}

Cuchillo::~Cuchillo() {}

