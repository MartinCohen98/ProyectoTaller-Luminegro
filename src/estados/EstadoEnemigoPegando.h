#ifndef PROYECTOTALLER_LUMINEGRO_ESTADOENEMIGOPEGANDO_H
#define PROYECTOTALLER_LUMINEGRO_ESTADOENEMIGOPEGANDO_H

#include "EstadoEnemigoParado.h"
#include "EstadoEnemigoMuriendo.h"

class EstadoEnemigoPegando: public EstadoJugador {

private:
    int framesTranscurridas;
    int numeroDeFrame;
    bool golpeTerminado;
    bool frameDeDanio;

public:
    EstadoEnemigoPegando(tipoDeSprite tipo);
    EstadoJugador* avanzar();
    EstadoJugador* parar();
    EstadoJugador* pegar();
    EstadoJugador* morir();
    EstadoJugador* serGolpeado();
    bool puedeMoverse();
    bool terminado();
    bool estaAtacando();
    int obtenerDanio();
    virtual ~EstadoEnemigoPegando();

private:
    void cambiarFrame();
};


#endif //PROYECTOTALLER_LUMINEGRO_ESTADOENEMIGOPEGANDO_H
