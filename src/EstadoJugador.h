#ifndef SRC_ESTADOJUGADOR_H_
#define SRC_ESTADOJUGADOR_H_

#include "Encuadre.h"

class EstadoJugador {

public:
	EstadoJugador();
	Encuadre obtenerSprite();
	virtual EstadoJugador* avanzar();
	virtual EstadoJugador* parar();
	virtual EstadoJugador* agacharse();
	virtual EstadoJugador* pegar();
	virtual int obtenerAlto();
	virtual int obtenerAncho();
	virtual ~EstadoJugador();

protected:
	Encuadre frameActual;
	int alto;
	int ancho;
};

#endif /* SRC_ESTADOJUGADOR_H_ */
