#ifndef SRC_ESTADOJUGADORSALTANDO_H_
#define SRC_ESTADOJUGADORSALTANDO_H_

#include "EstadoJugador.h"
#include "EstadoJugadorParado.h"

class EstadoJugadorSaltando: public EstadoJugador {

private:
	int framesTranscurridas;
	int numeroDeFrame;
	int elevacion;

public:
	EstadoJugadorSaltando();
	EstadoJugador* avanzar();
	EstadoJugador* parar();
	EstadoJugador* agacharse();
	EstadoJugador* pegar();
	EstadoJugador* saltar();
	int obtenerElevacion();
	virtual ~EstadoJugadorSaltando();

private:
	void cambiarFrame();
};

#endif /* SRC_ESTADOJUGADORSALTANDO_H_ */
