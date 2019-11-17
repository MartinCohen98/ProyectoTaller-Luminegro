#ifndef PROYECTOTALLER_LUMINEGRO_SONIDOS_H
#define PROYECTOTALLER_LUMINEGRO_SONIDOS_H

#include "../varios/Logger.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "../../lib/pugixml/pugixml.hpp"
#include <thread>

class Sonidos {

private:
    Logger::Log *logueador;
    pugi::xml_document* archiConfig;
    std::string mensajeLog;
    Mix_Chunk *sonidoFondo = NULL;
    Mix_Chunk *sonidoGolpe = NULL;
    Mix_Chunk *sonidoSalto = NULL;
    Mix_Chunk *sonidoCaida = NULL;
    Mix_Chunk *sonidoDestruccion = NULL;
    bool *musicaFondoActiva;
    bool *ejecutarSonidoGolpe;
    bool *ejecutarSonidoSalto;
    bool *ejecutarSonidoCaida;
    bool *ejecutarSonidoDestruccion;

public:
    Sonidos(pugi::xml_document* archiConfig, bool *musicaFondoActiva, bool *ejecutarSonidoGolpe,
            bool *ejecutarSonidoSalto, bool *ejecutarSonidoCaida, bool *ejecutarSonidoDestruccion);
    void operator()();
    virtual ~Sonidos();
};


#endif //PROYECTOTALLER_LUMINEGRO_SONIDOS_H
