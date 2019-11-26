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
    EstadoJugador* parar();
    EstadoJugador* avanzar();
    EstadoJugador* pegar();
    EstadoJugador* serGolpeado();
    EstadoJugador* morir();
    bool puedeMoverse();
    bool terminado();
    bool estaAtacando();
    int obtenerDanio();
    int obtenerAlto();
    virtual ~EstadoEnemigoPegando();

private:
    void cambiarFrame();
};


#endif //PROYECTOTALLER_LUMINEGRO_ESTADOENEMIGOPEGANDO_H
