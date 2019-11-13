#ifndef SRC_ESTADOJUGADORAVANZANDO_H_
#define SRC_ESTADOJUGADORAVANZANDO_H_

#include "EstadoJugadorParado.h"
#include "EstadoJugadorCongelado.h"
#include "EstadoJugadorMuriendo.h"

class EstadoJugadorAvanzando: public EstadoJugador {

private:
	int framesTranscurridas;
	int numeroDeFrame;

public:
	EstadoJugadorAvanzando();
	EstadoJugador* parar();
	EstadoJugador* avanzar();
	EstadoJugador* agacharse();
	EstadoJugador* pegar();
	EstadoJugador* saltar();
    EstadoJugador* morir();
    EstadoJugador* acuchillar();
    EstadoJugador* apalear();
    EstadoJugador* congelarse();
	virtual ~EstadoJugadorAvanzando();

private:
	void cambiarFrame();
};

#endif /* SRC_ESTADOJUGADORAVANZANDO_H_ */
