/*
 * EstadoObjetoEntero.h
 *
 *  Created on: 20 nov. 2019
 *      Author: julio
 */

#ifndef SRC_ESTADOS_ESTADOOBJETOENTERO_H_
#define SRC_ESTADOS_ESTADOOBJETOENTERO_H_

#include "../estados/EstadoObjeto.h"
#include "../estados/EstadoObjetoRoto.h"

class EstadoObjetoEntero: public EstadoObjeto {
private:
	Encuadre frameActual;
	int alto;
	int ancho;
	tipoDeSprite tipo;
public:
	EstadoObjetoEntero(tipoDeSprite tipo);
	EstadoObjeto* romperse();
	virtual ~EstadoObjetoEntero();
};

#endif /* SRC_ESTADOS_ESTADOOBJETOENTERO_H_ */
