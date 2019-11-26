#ifndef PROYECTOTALLER_LUMINEGRO_ESTADOJUGADORCONGELADO_H
#define PROYECTOTALLER_LUMINEGRO_ESTADOJUGADORCONGELADO_H

#include "EstadoJugador.h"
#include "EstadoEnemigoParado.h"

class EstadoJugadorCongelado: public EstadoJugador {
public:
    EstadoJugadorCongelado(tipoDeArma arma);
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
    virtual ~EstadoJugadorCongelado();
};


#endif //PROYECTOTALLER_LUMINEGRO_ESTADOJUGADORCONGELADO_H
