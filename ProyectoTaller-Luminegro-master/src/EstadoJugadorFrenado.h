#ifndef SRC_ESTADOJUGADORFRENADO_H_
#define SRC_ESTADOJUGADORFRENADO_H_

#include "EstadoJugador.h"
#include "EstadoJugadorAvanzando.h"
#include "EstadoJugadorAgachado.h"

class EstadoJugadorFrenado: public EstadoJugador {

public:
	EstadoJugadorFrenado();
	EstadoJugadorFrenado(int x, int y, int ancho, int alto);
	EstadoJugador* parar();
	EstadoJugador* avanzar();
	EstadoJugador* agacharse();
	virtual ~EstadoJugadorFrenado();
};

#endif /* SRC_ESTADOJUGADORFRENADO_H_ */
