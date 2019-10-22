#ifndef SRC_ESTADOENEMIGOAVANZANDO_H_
#define SRC_ESTADOENEMIGOAVANZANDO_H_

#include "EstadoJugador.h"
#include "EstadoJugadorParado.h"
#include "EstadoJugadorAgachado.h"

class EstadoEnemigoAvanzando: public EstadoJugador {

private:
	int framesTranscurridas;
	int numeroDeFrame;

public:
	EstadoEnemigoAvanzando();
	EstadoEnemigoAvanzando(int x, int y, int ancho, int alto);
	EstadoJugador* parar();
	EstadoJugador* avanzar();
	EstadoJugador* agacharse();
	virtual ~EstadoEnemigoAvanzando();

private:
	void cambiarFrame();
};

#endif /* SRC_ESTADOENEMIGOAVANZANDO_H_ */