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

class EstadoEnemigoParado: public EstadoJugador {
public:
    EstadoEnemigoParado();
	EstadoEnemigoParado(int x, int y, int ancho, int alto);
	EstadoJugador* parar();
	EstadoJugador* avanzar();
    EstadoJugador* pegar();
	virtual ~EstadoEnemigoParado();
};

#endif /* SRC_ESTADOENEMIGOPARADO_H_ */
