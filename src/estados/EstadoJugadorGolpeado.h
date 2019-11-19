/*
 * EstadoJugadorGolpeado.h
 *
 *  Created on: 18 nov. 2019
 *      Author: julio
 */

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
	EstadoJugadorGolpeado();
	EstadoJugador* avanzar();
	EstadoJugador* parar();
	EstadoJugador* serGolpeado();
	EstadoJugador* morir();
	bool puedeMoverse();
	bool terminado();
	virtual ~EstadoJugadorGolpeado();
private:
	void cambiarFrame();
};

#endif /* SRC_ESTADOS_ESTADOJUGADORGOLPEADO_H_ */