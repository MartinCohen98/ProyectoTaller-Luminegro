/*
 * EstadoObjetoEntero.h
 *
 *  Created on: 20 nov. 2019
 *      Author: julio
 */

#ifndef SRC_ESTADOS_ESTADOOBJETOENTERO_H_
#define SRC_ESTADOS_ESTADOOBJETOENTERO_H_

#include "../estados/EstadoObjetoRoto.h"

class EstadoObjetoEntero {
private:
	Encuadre frameActual;
	int alto;
	int ancho;
	tipoDeSprite tipo;
public:
	EstadoObjetoEntero(tipoDeSprite tipo);
	EstadoObjetoRoto* romperse();
	virtual ~EstadoObjetoEntero();
};

#endif /* SRC_ESTADOS_ESTADOOBJETOENTERO_H_ */
