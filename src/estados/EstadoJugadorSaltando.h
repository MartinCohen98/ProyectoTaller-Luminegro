#ifndef SRC_ESTADOJUGADORSALTANDO_H_
#define SRC_ESTADOJUGADORSALTANDO_H_

#include "EstadoJugadorParado.h"
#include "EstadoJugadorMuriendo.h"

class EstadoJugadorSaltando: public EstadoJugador {

private:
	int framesTranscurridas;
	int numeroDeFrame;
	int elevacion;

public:
	EstadoJugadorSaltando();
	EstadoJugador* avanzar();
	EstadoJugador* parar();
	EstadoJugador* agacharse();
	EstadoJugador* pegar();
	EstadoJugador* saltar();
    EstadoJugador* morir();
    EstadoJugador* acuchillar();
    EstadoJugador* apalear();
    EstadoJugador* congelarse();
	int obtenerElevacion();
	bool estaSaltando();
	virtual ~EstadoJugadorSaltando();

private:
	void cambiarFrame();
};

#endif /* SRC_ESTADOJUGADORSALTANDO_H_ */
