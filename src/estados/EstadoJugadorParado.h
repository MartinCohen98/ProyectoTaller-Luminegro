#ifndef SRC_ESTADOJUGADORPARADO_H_
#define SRC_ESTADOJUGADORPARADO_H_

#include "EstadoJugador.h"
#include "EstadoJugadorAvanzando.h"
#include "EstadoJugadorAgachado.h"
#include "EstadoJugadorPegando.h"
#include "EstadoJugadorSaltando.h"
#include "EstadoJugadorPateando.h"
#include "EstadoJugadorMuriendo.h"
#include "EstadoJugadorGolpeado.h"

class EstadoJugadorParado: public EstadoJugador {

public:
	EstadoJugadorParado(tipoDeArma arma);
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
	virtual ~EstadoJugadorParado();
};

#endif /* SRC_ESTADOJUGADORPARADO_H_ */
