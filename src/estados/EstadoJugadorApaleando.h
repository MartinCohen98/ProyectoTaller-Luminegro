#ifndef PROYECTOTALLER_LUMINEGRO_ESTADOJUGADORAPALEANDO_H
#define PROYECTOTALLER_LUMINEGRO_ESTADOJUGADORAPALEANDO_H

#include "EstadoJugadorParado.h"
#include "EstadoJugadorMuriendo.h"

class EstadoJugadorApaleando : public EstadoJugador {

private:
    int framesTranscurridas;
    int numeroDeFrame;
    bool golpeTerminado;
    bool frameDeDanio;

public:

    EstadoJugadorApaleando(tipoDeArma arma);
    EstadoJugador* parar();
    EstadoJugador* avanzar();
    EstadoJugador* agacharse();
    EstadoJugador* saltar();
    EstadoJugador* pegar();
    EstadoJugador* acuchillar();
    EstadoJugador* apalear();
    EstadoJugador* serGolpeado();
    EstadoJugador* morir();
    EstadoJugador* congelarse();
    bool puedeMoverse();
    bool estaAtacando();
    int obtenerDanio();
    int obtenerPuntosDeGolpe();
    bool terminado();
    virtual ~EstadoJugadorApaleando();

private:
    void cambiarFrame();


};


#endif //PROYECTOTALLER_LUMINEGRO_ESTADOJUGADORAPALEANDO_H
