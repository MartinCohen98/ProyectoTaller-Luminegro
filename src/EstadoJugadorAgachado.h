#ifndef SRC_ESTADOJUGADORAGACHADO_H_
#define SRC_ESTADOJUGADORAGACHADO_H_

#include "EstadoJugador.h"
#include "EstadoJugadorAvanzando.h"
#include "EstadoJugadorParado.h"
#include "EstadoJugadorPegando.h"

class EstadoJugadorAgachado: public EstadoJugador {

public:
	EstadoJugadorAgachado();
	EstadoJugador* parar();
	EstadoJugador* avanzar();
	EstadoJugador* agacharse();
	EstadoJugador* pegar();
	virtual ~EstadoJugadorAgachado();
};

#endif /* SRC_ESTADOJUGADORAGACHADO_H_ */
