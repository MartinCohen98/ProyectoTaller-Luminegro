#ifndef SRC_ESTADOJUGADORAGACHADO_H_
#define SRC_ESTADOJUGADORAGACHADO_H_

#include "EstadoJugadorParado.h"
#include "EstadoJugadorMuriendo.h"
#include "EstadoJugadorAcuchillando.h"
#include "EstadoJugadorApaleando.h"


class EstadoJugadorAgachado: public EstadoJugador {

public:
	EstadoJugadorAgachado(tipoDeArma arma);
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
    bool estaAtacando();
	bool puedeMoverse();
	virtual ~EstadoJugadorAgachado();
};

#endif /* SRC_ESTADOJUGADORAGACHADO_H_ */
