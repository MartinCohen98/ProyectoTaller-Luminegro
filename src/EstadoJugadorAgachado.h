#ifndef SRC_ESTADOJUGADORAGACHADO_H_
#define SRC_ESTADOJUGADORAGACHADO_H_

#include "EstadoJugador.h"
#include "EstadoJugadorFrenado.h"
#include "EstadoJugadorAvanzando.h"

class EstadoJugadorAgachado: public EstadoJugador {

public:
	EstadoJugadorAgachado();
	EstadoJugador* parar();
	EstadoJugador* avanzar();
	EstadoJugador* agacharse();
	virtual ~EstadoJugadorAgachado();
};

#endif /* SRC_ESTADOJUGADORAGACHADO_H_ */
