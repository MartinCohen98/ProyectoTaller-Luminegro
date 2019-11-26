#ifndef SRC_ESTADOJUGADORPATEANDO_H_
#define SRC_ESTADOJUGADORPATEANDO_H_

#include "EstadoJugadorParado.h"
#include "EstadoJugadorMuriendo.h"

class EstadoJugadorPateando: public EstadoJugador {

private:
	int framesTranscurridas;
	int numeroDeFrame;
	int elevacion;
	bool frameCambiada;

public:
	EstadoJugadorPateando(int numeroDeFrame, int framesTranscurridas,
						int elevacion, tipoDeArma tipoArma);
	EstadoJugador* parar();
	EstadoJugador* avanzar();
	EstadoJugador* agacharse();
	EstadoJugador* saltar();
	EstadoJugador* pegar();
    EstadoJugador* acuchillar();
    EstadoJugador* apalear();
    EstadoJugador* serGolpeado();
    EstadoJugador* morir();
    EstadoJugador* congelarse();
	int obtenerElevacion();
	int obtenerDanio();
	int obtenerPuntosDeGolpe();
	bool estaSaltando();
	bool estaAtacando();
	bool estaPateando();
	virtual ~EstadoJugadorPateando();

private:
	void cambiarFrame();
};

#endif /* SRC_ESTADOJUGADORPATEANDO_H_ */
