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
	EstadoJugadorSaltando(tipoDeArma arma);
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
	int obtenerElevacion();
	bool estaSaltando();
	virtual ~EstadoJugadorSaltando();

private:
	void cambiarFrame();
};

#endif /* SRC_ESTADOJUGADORSALTANDO_H_ */
