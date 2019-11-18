/*
 * EstadoEnemigoGolpeado.h
 *
 *  Created on: 18 nov. 2019
 *      Author: julio
 */

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
	EstadoEnemigoGolpeado();
	EstadoEnemigoGolpeado(tipoDeSprite tipo);
	EstadoJugador* avanzar();
	EstadoJugador* parar();
	EstadoJugador* serGolpeado();
	EstadoJugador* morir();
	bool puedeMoverse();
	bool terminado();
	virtual ~EstadoEnemigoGolpeado();
private:
	void cambiarFrame();
};

#endif /* SRC_ESTADOS_ESTADOENEMIGOGOLPEADO_H_ */
