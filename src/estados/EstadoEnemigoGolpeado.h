#ifndef SRC_ESTADOS_ESTADOENEMIGOGOLPEADO_H_
#define SRC_ESTADOS_ESTADOENEMIGOGOLPEADO_H_

#include "EstadoEnemigoParado.h"
#include "EstadoEnemigoMuriendo.h"

class EstadoEnemigoGolpeado: public EstadoJugador  {
private:
	int framesTranscurridas;
	int numeroDeFrame;
	bool palizaTerminada;
public:
	EstadoEnemigoGolpeado(tipoDeSprite tipo);
	EstadoJugador* avanzar();
	EstadoJugador* parar();
	EstadoJugador* serGolpeado();
	EstadoJugador* morir();
	EstadoJugador* pegar();
	bool puedeMoverse();
	virtual ~EstadoEnemigoGolpeado();
};

#endif /* SRC_ESTADOS_ESTADOENEMIGOGOLPEADO_H_ */
