#ifndef SRC_ESTADOJUGADORPATEANDO_H_
#define SRC_ESTADOJUGADORPATEANDO_H_

#include "EstadoJugadorParado.h"
#include "EstadoJugadorMuriendo.h"

class EstadoJugadorPateando: public EstadoJugador {

private:
	int framesTranscurridas;
	int numeroDeFrame;
	int elevacion;
	bool frameCambiada;

public:
	EstadoJugadorPateando(int numeroDeFrame, int framesTranscurridas,
						int elevacion, tipoDeArma tipoArma);
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
	virtual ~EstadoJugadorPateando();

private:
	void cambiarFrame();
};

#endif /* SRC_ESTADOJUGADORPATEANDO_H_ */
