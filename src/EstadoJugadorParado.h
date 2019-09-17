#ifndef SRC_ESTADOJUGADORPARADO_H_
#define SRC_ESTADOJUGADORPARADO_H_

#include "EstadoJugador.h"
#include "EstadoJugadorAvanzando.h"
#include "EstadoJugadorAgachado.h"
#include "EstadoJugadorPegando.h"

class EstadoJugadorParado: public EstadoJugador {

public:
	EstadoJugadorParado();
	EstadoJugador* parar();
	EstadoJugador* avanzar();
	EstadoJugador* agacharse();
	EstadoJugador* pegar();
	virtual ~EstadoJugadorParado();
};

#endif /* SRC_ESTADOJUGADORPARADO_H_ */
