#ifndef PROYECTOTALLER_LUMINEGRO_ESTADOENEMIGOMURIENDO_H
#define PROYECTOTALLER_LUMINEGRO_ESTADOENEMIGOMURIENDO_H

#include "EstadoJugadorParado.h"

class EstadoEnemigoMuriendo: public EstadoJugador {

private:
    int framesTranscurridas;
    int numeroDeFrame;
    bool caidaTerminada;

public:
    EstadoEnemigoMuriendo(tipoDeSprite tipo);
    EstadoJugador* parar();
    EstadoJugador* avanzar();
    EstadoJugador* pegar();
    EstadoJugador* serGolpeado();
    EstadoJugador* morir();
    bool puedeMoverse();
    bool terminado();
    bool estaMuerto();
    virtual ~EstadoEnemigoMuriendo();
private:
    void cambiarFrame();
};


#endif //PROYECTOTALLER_LUMINEGRO_ESTADOENEMIGOMURIENDO_H
