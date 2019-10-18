#include "VistaJugador.h"

VistaJugador::VistaJugador(Renderizador* elRenderizador,
							pugi::xml_document *archiConfig) {
	renderizador = elRenderizador;

	// Leo del XML la ubicación del BMP del protagonista
    std::string protagonistaBMPPath = archiConfig->child("configuracion").child("escenario")
            .child("protagonistas").child("protagonista1").child_value("imagen");

    Imagen sprite;
	sprite.cargar( protagonistaBMPPath.data(), Imagen::TIPO_PERSONAJE );
	textura.texturizar(renderizador, sprite);
}

VistaJugador::~VistaJugador() {}

