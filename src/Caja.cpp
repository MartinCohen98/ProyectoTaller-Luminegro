#include "Caja.h"
#include "Imagen.h"

Caja::Caja(Renderizador *renderizador, int posXinicial, int posYinicial, pugi::xml_document *archiConfig) {
	posicionX = posXinicial;
	posicionY = posYinicial;
	ancho = 96;
	alto = 160;
	escaladoDeSprite = 3;

    std::string cajaBMPPath = archiConfig->child("configuracion").child("escenario")
            .child("objetos").child("caja").child_value("imagen");

    sprite.cargar (cajaBMPPath.data(), Imagen::TIPO_OBJETO);

	encuadre.modificar(0, 0, 96, 160);
	insercion.modificar(posXinicial, posYinicial, ancho, alto);
	textura.texturizar(renderizador, sprite);
	textura.copiarseEn(renderizador, encuadre, insercion);
}

void Caja::movidaDePantalla() {
	posicionX = posicionX - 12;
	insercion.modificar(posicionX, posicionY, ancho, alto);
}

void Caja::actualizar(Renderizador *renderizador) {
	textura.copiarseEn(renderizador, encuadre, insercion);
}

Caja::~Caja() {}

