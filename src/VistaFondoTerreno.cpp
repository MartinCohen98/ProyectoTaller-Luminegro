#include "VistaFondoTerreno.h"

VistaFondoTerreno::VistaFondoTerreno(Renderizador* elRenderizador,
		pugi::xml_document *archiConfig, std::string nivel) {
	renderizador = elRenderizador;

		// Leo del XML la ubicación del BMP del cielo
	    std::string path = archiConfig->child("configuracion").child("escenario")
	            .child("niveles").child( nivel.data() ).child_value("terreno");

	    Imagen sprite;
		sprite.cargar( path.data(), Imagen::TIPO_FONDO );
		textura.texturizar(renderizador, sprite);
}

VistaFondoTerreno::~VistaFondoTerreno() {}

