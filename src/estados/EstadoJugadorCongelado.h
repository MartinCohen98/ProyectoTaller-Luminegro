//
// Created by julio on 27/10/19.
//

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
    EstadoJugador* pegar();
    EstadoJugador* saltar();
    bool puedeMoverse();
    virtual ~EstadoJugadorCongelado();
};


#endif //PROYECTOTALLER_LUMINEGRO_ESTADOJUGADORCONGELADO_H
