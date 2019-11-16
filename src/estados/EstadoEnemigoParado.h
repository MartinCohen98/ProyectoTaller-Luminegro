/*
 * EstadoEnemigoFrenado.h
 *
 *  Created on: 16 sep. 2019
 *      Author: julio
 */

#ifndef SRC_ESTADOENEMIGOPARADO_H_
#define SRC_ESTADOENEMIGOPARADO_H_


#include "EstadoJugador.h"
#include "EstadoEnemigoAvanzando.h"
#include "EstadoJugadorAgachado.h"
#include "EstadoEnemigoMuriendo.h"
#include "../comunicacion/MensajeServidor.h"

class EstadoEnemigoParado: public EstadoJugador {
public:
    EstadoEnemigoParado();
    EstadoEnemigoParado(tipoDeSprite tipo);
	EstadoJugador* parar();
	EstadoJugador* avanzar();
    EstadoJugador* pegar();
    EstadoJugador* morir();
	virtual ~EstadoEnemigoParado();
};

#endif /* SRC_ESTADOENEMIGOPARADO_H_ */
