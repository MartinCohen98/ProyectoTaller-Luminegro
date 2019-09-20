#ifndef SRC_ESTADOJUGADORAGACHADO_H_
#define SRC_ESTADOJUGADORAGACHADO_H_

#include "EstadoJugadorParado.h"

class EstadoJugadorAgachado: public EstadoJugador {

public:
	EstadoJugadorAgachado();
	EstadoJugador* parar();
	EstadoJugador* avanzar();
	EstadoJugador* agacharse();
	EstadoJugador* pegar();
	EstadoJugador* saltar();
	virtual ~EstadoJugadorAgachado();
};

#endif /* SRC_ESTADOJUGADORAGACHADO_H_ */
