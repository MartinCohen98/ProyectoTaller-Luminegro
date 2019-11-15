#ifndef PROYECTOTALLER_LUMINEGRO_MUSICAFONDO_H
#define PROYECTOTALLER_LUMINEGRO_MUSICAFONDO_H

#include "../varios/Logger.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "../../lib/pugixml/pugixml.hpp"

class MusicaFondo {

private:
    Logger::Log *logueador;
    std::string mensajeError;
    Mix_Chunk *sonido = NULL;

public:
    int inicializar(pugi::xml_document* archiConfig);
    int reproducir();
    virtual ~MusicaFondo();
};


#endif //PROYECTOTALLER_LUMINEGRO_MUSICAFONDO_H
