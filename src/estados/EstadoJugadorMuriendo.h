#ifndef PROYECTOTALLER_LUMINEGRO_ESTADOJUGADORMURIENDO_H
#define PROYECTOTALLER_LUMINEGRO_ESTADOJUGADORMURIENDO_H

#include "EstadoJugadorParado.h"

class EstadoJugadorMuriendo: public EstadoJugador {
private:
    int framesTranscurridas;
    int numeroDeFrame;
    bool caidaTerminada;
public:
    EstadoJugadorMuriendo(tipoDeArma arma);
    EstadoJugador* morir();
    EstadoJugador* avanzar();
    EstadoJugador* parar();
    EstadoJugador* pegar();
	EstadoJugador* agacharse();
    EstadoJugador* acuchillar();
    EstadoJugador* apalear();
	EstadoJugador* saltar();
    EstadoJugador* congelarse();
    bool estaAtacando();
    bool terminado();
    virtual ~EstadoJugadorMuriendo();
private:
    void cambiarFrame();
};


#endif //PROYECTOTALLER_LUMINEGRO_ESTADOJUGADORMURIENDO_H
