#ifndef SRC_ESTADOENEMIGOAVANZANDO_H_
#define SRC_ESTADOENEMIGOAVANZANDO_H_

#include "EstadoJugador.h"
#include "EstadoEnemigoParado.h"
#include "EstadoEnemigoPegando.h"
#include "EstadoEnemigoMuriendo.h"
#include "../comunicacion/MensajeServidor.h"

class EstadoEnemigoAvanzando: public EstadoJugador {

private:
	int framesTranscurridas;
	int numeroDeFrame;

public:
	EstadoEnemigoAvanzando();
	EstadoEnemigoAvanzando(tipoDeSprite tipo);
	EstadoJugador* parar();
	EstadoJugador* avanzar();
    EstadoJugador* pegar();
    EstadoJugador* morir();
    EstadoJugador* serGolpeado();
	virtual ~EstadoEnemigoAvanzando();

private:
	void cambiarFrame();
};

#endif /* SRC_ESTADOENEMIGOAVANZANDO_H_ */
