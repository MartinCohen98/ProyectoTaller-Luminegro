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
    EstadoJugador* avanzar();
    EstadoJugador* parar();
	EstadoJugador* agacharse();
	EstadoJugador* saltar();
    EstadoJugador* pegar();
    EstadoJugador* acuchillar();
    EstadoJugador* apalear();
    EstadoJugador* serGolpeado();
    EstadoJugador* morir();
    EstadoJugador* congelarse();
    bool estaAtacando();
    bool terminado();
    virtual ~EstadoJugadorMuriendo();
private:
    void cambiarFrame();
};


#endif //PROYECTOTALLER_LUMINEGRO_ESTADOJUGADORMURIENDO_H
