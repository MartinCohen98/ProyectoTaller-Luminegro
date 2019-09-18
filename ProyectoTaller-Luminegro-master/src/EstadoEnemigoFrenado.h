/*
 * EstadoEnemigoFrenado.h
 *
 *  Created on: 16 sep. 2019
 *      Author: julio
 */

#ifndef SRC_ESTADOENEMIGOFRENADO_H_
#define SRC_ESTADOENEMIGOFRENADO_H_


#include "EstadoJugador.h"
#include "EstadoEnemigoAvanzando.h"
#include "EstadoJugadorAgachado.h"

class EstadoEnemigoFrenado: public EstadoJugador {
public:
	EstadoEnemigoFrenado(int x, int y, int ancho, int alto);
	EstadoJugador* parar();
	EstadoJugador* avanzar();
	EstadoJugador* agacharse();
	virtual ~EstadoEnemigoFrenado();
};

#endif /* SRC_ESTADOENEMIGOFRENADO_H_ */
