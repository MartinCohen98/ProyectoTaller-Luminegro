#ifndef SRC_ESTADOJUGADORAVANZANDO_H_
#define SRC_ESTADOJUGADORAVANZANDO_H_

#include "EstadoJugador.h"
#include "EstadoJugadorFrenado.h"
#include "EstadoJugadorAgachado.h"

class EstadoJugadorAvanzando: public EstadoJugador {

private:
	int framesTranscurridas;
	int numeroDeFrame;

public:
	EstadoJugadorAvanzando();
	EstadoJugador* parar();
	EstadoJugador* avanzar();
	EstadoJugador* agacharse();
	virtual ~EstadoJugadorAvanzando();

private:
	void cambiarFrame();
};

#endif /* SRC_ESTADOJUGADORAVANZANDO_H_ */
