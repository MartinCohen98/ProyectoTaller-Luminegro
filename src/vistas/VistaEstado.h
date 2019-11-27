#ifndef PROYECTOTALLER_LUMINEGRO_VISTAESTADO_H
#define PROYECTOTALLER_LUMINEGRO_VISTAESTADO_H


#include <SDL2/SDL_ttf.h>
#include "../grafica/Textura.h"
#include "../varios/InfoJugador.h"
#include "../../lib/pugixml/pugixml.hpp"

class VistaEstado {
private:
    Renderizador* renderizador;
    Textura texturaIcono;
    Textura texturaNombreJugador;
    Textura texturaNombreRelleno;
    Textura texturaPuntaje;
    Textura texturaBarraVida;
    Encuadre encuadreIcono;
    Encuadre encuadreNombre;
    Encuadre encuadreBarraVida;
    Encuadre encuadrePuntaje;
    TTF_Font *fuente;
    SDL_Surface * superficieTxt;
    SDL_Color colorRellenoLetras;
    SDL_Color colorLetrasNombre;
    SDL_Color colorPuntaje;
    SDL_Color colorDesconexion;
    int maxVida;
    std::string nombreJugador;
    std::string nombreYVidas;
    uint8_t cantidadDeVidas;
public:
    VistaEstado(Renderizador *renderizador, pugi::xml_document *archiConfig, int maxVida, std::string nombreJugador, int numeroJugador);
    void renderizar(InfoJugador estadoJugador);
    void CargarBarraDeVida(InfoJugador *estadoJugador);
    void CargarNombreYVidas(InfoJugador *estadoJugador);
    void CargarPuntaje(InfoJugador *estadoJugador);
    ~VistaEstado();
};


#endif //PROYECTOTALLER_LUMINEGRO_VISTAESTADO_H
