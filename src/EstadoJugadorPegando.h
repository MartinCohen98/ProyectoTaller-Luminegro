#ifndef SRC_ESTADOJUGADORPEGANDO_H_
#define SRC_ESTADOJUGADORPEGANDO_H_

#include "EstadoJugador.h"
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
	bool puedeMoverse();
	bool terminado();
	virtual ~EstadoJugadorPegando();

private:
	void cambiarFrame();
};

#endif /* SRC_ESTADOJUGADORPEGANDO_H_ */
