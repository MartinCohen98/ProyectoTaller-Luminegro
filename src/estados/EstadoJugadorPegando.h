#ifndef SRC_ESTADOJUGADORPEGANDO_H_
#define SRC_ESTADOJUGADORPEGANDO_H_

#include "EstadoJugadorParado.h"
#include "EstadoJugadorMuriendo.h"

class EstadoJugadorPegando: public EstadoJugador {

private:
	int framesTranscurridas;
	int numeroDeFrame;
	bool golpeTerminado;
	bool frameDeDanio;

public:

	EstadoJugadorPegando(tipoDeArma arma);
	EstadoJugador* avanzar();
	EstadoJugador* parar();
	EstadoJugador* agacharse();
	EstadoJugador* pegar();
	EstadoJugador* saltar();
    EstadoJugador* morir();
    EstadoJugador* acuchillar();
    EstadoJugador* apalear();
    EstadoJugador* congelarse();
	bool puedeMoverse();
	bool estaAtacando();
	int obtenerDanio();
	int obtenerPuntosDeGolpe();
	bool terminado();
	virtual ~EstadoJugadorPegando();

private:
	void cambiarFrame();
};

#endif /* SRC_ESTADOJUGADORPEGANDO_H_ */
