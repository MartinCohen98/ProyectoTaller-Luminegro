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
    EstadoJugador* avanzar();
    EstadoJugador* parar();
    EstadoJugador* pegar();
    EstadoJugador* morir();
    EstadoJugador* serGolpeado();
    bool puedeMoverse();
    bool terminado();
    bool estaMuerto();
    virtual ~EstadoEnemigoMuriendo();
private:
    void cambiarFrame();
};


#endif //PROYECTOTALLER_LUMINEGRO_ESTADOENEMIGOMURIENDO_H
