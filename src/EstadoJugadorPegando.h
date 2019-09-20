#ifndef SRC_ESTADOJUGADORPEGANDO_H_
#define SRC_ESTADOJUGADORPEGANDO_H_

#include "EstadoJugadorParado.h"

class EstadoJugadorPegando: public EstadoJugador {

private:
	int framesTranscurridas;
	int numeroDeFrame;
	bool golpeTerminado;

public:

	EstadoJugadorPegando();
	EstadoJugador* avanzar();
	EstadoJugador* parar();
	EstadoJugador* agacharse();
	EstadoJugador* pegar();
	EstadoJugador* saltar();
	bool puedeMoverse();
	bool terminado();
	virtual ~EstadoJugadorPegando();

private:
	void cambiarFrame();
};

#endif /* SRC_ESTADOJUGADORPEGANDO_H_ */
