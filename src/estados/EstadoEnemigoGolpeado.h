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
	EstadoJugador* parar();
	EstadoJugador* avanzar();
	EstadoJugador* pegar();
	EstadoJugador* serGolpeado();
	EstadoJugador* morir();
	bool puedeMoverse();
	virtual ~EstadoEnemigoGolpeado();
};

#endif /* SRC_ESTADOS_ESTADOENEMIGOGOLPEADO_H_ */
