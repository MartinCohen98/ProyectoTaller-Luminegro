#ifndef PROYECTOTALLER_LUMINEGRO_MUSICAFONDO_H
#define PROYECTOTALLER_LUMINEGRO_MUSICAFONDO_H

#include "../varios/Logger.h"
#include <SDL2/SDL.h>
#include <SDL_mixer.h>

class MusicaFondo {

private:
    Logger::Log *logueador;
    std::string mensajeError;
    Mix_Chunk *sonido = NULL;

public:
    int inicializar();
    int dalePlay();
    virtual ~MusicaFondo();
};


#endif //PROYECTOTALLER_LUMINEGRO_MUSICAFONDO_H
