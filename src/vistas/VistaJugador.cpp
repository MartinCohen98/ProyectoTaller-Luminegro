#include "VistaJugador.h"

VistaJugador::VistaJugador(Renderizador* elRenderizador, pugi::xml_document *archiConfig, tipoDeSprite jugador,
        bool *ejecutarSonidoGolpeTiro, bool *ejecutarSonidoGolpeImpacto, bool *ejecutarSonidoSalto,
        bool *ejecutarSonidoCaida) {

	renderizador = elRenderizador;
    this->ejecutarSonidoGolpeTiro = ejecutarSonidoGolpeTiro;
    this->ejecutarSonidoGolpeImpacto = ejecutarSonidoGolpeImpacto;
    this->ejecutarSonidoSalto = ejecutarSonidoSalto;
    this->ejecutarSonidoCaida = ejecutarSonidoCaida;

	std::string path;

	// Leo del XML la ubicación del BMP del protagonista
    switch(jugador) {
    	case Jugador1:
    		path = archiConfig->child("configuracion").child("escenario")
				.child("protagonistas").child("protagonista1").child_value("imagen");
    		break;
    	case Jugador2:
    		path = archiConfig->child("configuracion").child("escenario")
				.child("protagonistas").child("protagonista2").child_value("imagen");
    		break;
    	case Jugador3:
    		path = archiConfig->child("configuracion").child("escenario")
				.child("protagonistas").child("protagonista3").child_value("imagen");
    		break;
    	case Jugador4:
    		path = archiConfig->child("configuracion").child("escenario")
				.child("protagonistas").child("protagonista4").child_value("imagen");
    		break;
    	default:
    		std::string path = archiConfig->child("configuracion").child("escenario")
				.child("protagonistas").child("protagonista1").child_value("imagen");
    }

    Imagen sprite;
	sprite.cargar( path.data(), Imagen::TIPO_PERSONAJE );
	textura.texturizar(renderizador, sprite);
}

VistaJugador::~VistaJugador() {}

