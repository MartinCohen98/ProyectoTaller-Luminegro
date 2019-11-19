#ifndef PROYECTOTALLER_LUMINEGRO_ESTADOJUGADORACUCHILLANDO_H
#define PROYECTOTALLER_LUMINEGRO_ESTADOJUGADORACUCHILLANDO_H

#include "EstadoJugadorParado.h"
#include "EstadoJugadorMuriendo.h"

class EstadoJugadorAcuchillando : public EstadoJugador {

private:
    int framesTranscurridas;
    int numeroDeFrame;
    bool golpeTerminado;

public:

    EstadoJugadorAcuchillando(tipoDeArma arma);
    EstadoJugador* avanzar();
    EstadoJugador* parar();
    EstadoJugador* agacharse();
    EstadoJugador* pegar();
    EstadoJugador* saltar();
    EstadoJugador* morir();
    EstadoJugador* acuchillar();
    EstadoJugador* apalear();
    EstadoJugador* congelarse();
    bool puedeMoverse();
    bool estaAtacando();
    bool terminado();
    int obtenerDanio();
    virtual ~EstadoJugadorAcuchillando();

private:
    void cambiarFrame();

};


#endif //PROYECTOTALLER_LUMINEGRO_ESTADOJUGADORACUCHILLANDO_H
