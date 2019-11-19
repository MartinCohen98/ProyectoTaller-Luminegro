//
// Created by julio on 12/11/19.
//

#ifndef PROYECTOTALLER_LUMINEGRO_ESTADOJUGADORAPALEANDO_H
#define PROYECTOTALLER_LUMINEGRO_ESTADOJUGADORAPALEANDO_H

#include "EstadoJugadorParado.h"
#include "EstadoJugadorMuriendo.h"

class EstadoJugadorApaleando : public EstadoJugador {

private:
    int framesTranscurridas;
    int numeroDeFrame;
    bool golpeTerminado;

public:

    EstadoJugadorApaleando(tipoDeArma arma);
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
    int obtenerDanio();
    bool terminado();
    virtual ~EstadoJugadorApaleando();

private:
    void cambiarFrame();


};


#endif //PROYECTOTALLER_LUMINEGRO_ESTADOJUGADORAPALEANDO_H
