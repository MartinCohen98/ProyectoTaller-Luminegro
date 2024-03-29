#ifndef SRC_ESTADOJUGADORAVANZANDO_H_
#define SRC_ESTADOJUGADORAVANZANDO_H_

#include "EstadoJugadorParado.h"
#include "EstadoJugadorCongelado.h"
#include "EstadoJugadorMuriendo.h"

class EstadoJugadorAvanzando: public EstadoJugador {

private:
	int framesTranscurridas;
	int numeroDeFrame;
	int posYframe;

public:
	EstadoJugadorAvanzando(tipoDeArma arma);
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
	virtual ~EstadoJugadorAvanzando();

private:
	void cambiarFrame();
};

#endif /* SRC_ESTADOJUGADORAVANZANDO_H_ */
