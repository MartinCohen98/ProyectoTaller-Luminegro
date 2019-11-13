//
// Created by julio on 10/11/19.
//

#ifndef PROYECTOTALLER_LUMINEGRO_ESTADOJUGADORMURIENDO_H
#define PROYECTOTALLER_LUMINEGRO_ESTADOJUGADORMURIENDO_H

#include "EstadoJugadorParado.h"

class EstadoJugadorMuriendo: public EstadoJugador {
private:
    int framesTranscurridas;
    int numeroDeFrame;
public:
    EstadoJugadorMuriendo();
    EstadoJugador* morir();
    EstadoJugador* avanzar();
    EstadoJugador* parar();
    EstadoJugador* pegar();
    virtual ~EstadoJugadorMuriendo();
private:
    void cambiarFrame();
};


#endif //PROYECTOTALLER_LUMINEGRO_ESTADOJUGADORMURIENDO_H