/*
 * EstadoObjeto.h
 *
 *  Created on: 20 nov. 2019
 *      Author: julio
 */

#ifndef SRC_ESTADOS_ESTADOOBJETO_H_
#define SRC_ESTADOS_ESTADOOBJETO_H_

#include "../comunicacion/MensajeServidor.h"

class EstadoObjeto {
public:
	EstadoObjeto();
	virtual EstadoObjeto* romperse();
	virtual ~EstadoObjeto();
};

#endif /* SRC_ESTADOS_ESTADOOBJETO_H_ */
