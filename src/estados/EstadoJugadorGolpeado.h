#ifndef SRC_ESTADOS_ESTADOJUGADORGOLPEADO_H_
#define SRC_ESTADOS_ESTADOJUGADORGOLPEADO_H_

#include "EstadoEnemigoParado.h"
#include "EstadoEnemigoMuriendo.h"

class EstadoJugadorGolpeado: public EstadoJugador {
private:
	int framesTranscurridas;
	int numeroDeFrame;
	bool palizaTerminada;

public:
	EstadoJugadorGolpeado(tipoDeArma arma);
	EstadoJugador* avanzar();
	EstadoJugador* parar();
	EstadoJugador* serGolpeado();
	EstadoJugador* morir();
	EstadoJugador* agacharse();
	EstadoJugador* pegar();
    EstadoJugador* acuchillar();
    EstadoJugador* apalear();
	EstadoJugador* saltar();
    EstadoJugador* congelarse();
	bool estaAtacando();
	bool puedeMoverse();
	bool terminado();
	virtual ~EstadoJugadorGolpeado();
private:
	void cambiarFrame();
};

#endif /* SRC_ESTADOS_ESTADOJUGADORGOLPEADO_H_ */
