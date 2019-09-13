#ifndef SRC_ESTADOJUGADOR_H_
#define SRC_ESTADOJUGADOR_H_

#include "Encuadre.h"

class EstadoJugador {

public:
	EstadoJugador();
	Encuadre obtenerSprite();
	virtual EstadoJugador* avanzar();
	virtual EstadoJugador* parar();
	virtual ~EstadoJugador();

protected:
	Encuadre frameActual;
};

#endif /* SRC_ESTADOJUGADOR_H_ */
