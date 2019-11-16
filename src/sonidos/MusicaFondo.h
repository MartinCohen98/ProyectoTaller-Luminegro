#ifndef PROYECTOTALLER_LUMINEGRO_MUSICAFONDO_H
#define PROYECTOTALLER_LUMINEGRO_MUSICAFONDO_H

#include "../varios/Logger.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "../../lib/pugixml/pugixml.hpp"
#include <thread>

class MusicaFondo {

private:
    Logger::Log *logueador;
    pugi::xml_document* archiConfig;
    std::string mensajeError;
    Mix_Chunk *sonido = NULL;
    bool *sonidoEstaActivo;

public:
    MusicaFondo(pugi::xml_document* archiConfig, bool *sonidoEstaActivo);
    void operator()();k
    virtual ~MusicaFondo();
};


#endif //PROYECTOTALLER_LUMINEGRO_MUSICAFONDO_H
