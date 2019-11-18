//
// Created by julio on 1/11/19.
//

#ifndef PROYECTOTALLER_LUMINEGRO_ESTADOENEMIGOPEGANDO_H
#define PROYECTOTALLER_LUMINEGRO_ESTADOENEMIGOPEGANDO_H

#include "EstadoEnemigoParado.h"
#include "EstadoEnemigoMuriendo.h"

class EstadoEnemigoPegando: public EstadoJugador {

private:
    int framesTranscurridas;
    int numeroDeFrame;
    bool golpeTerminado;

public:

    EstadoEnemigoPegando();
    EstadoEnemigoPegando(tipoDeSprite tipo);
    EstadoJugador* avanzar();
    EstadoJugador* parar();
    EstadoJugador* pegar(tipoDeSprite tipo);
    EstadoJugador* morir();
    EstadoJugador* serGolpeado();
    bool puedeMoverse();
    bool terminado();
    virtual ~EstadoEnemigoPegando();

private:
    void cambiarFrame();
};


#endif //PROYECTOTALLER_LUMINEGRO_ESTADOENEMIGOPEGANDO_H
