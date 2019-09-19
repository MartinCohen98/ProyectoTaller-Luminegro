/*
 * ControlEnemigos.h
 *
 *  Created on: 18 sep. 2019
 *      Author: julio
 */

#ifndef SRC_CONTROLENEMIGOS_H_
#define SRC_CONTROLENEMIGOS_H_

#include "Enemigo.h"
#include "Renderizador.h"
#include "Parallax.h"


class ControlEnemigos {
/*private: Enemigo enemigos[4];*/
public:
    ControlEnemigos();
	/*ControlEnemigos(Renderizador *renderizador)*/
	int InsertarEnEscenario(Renderizador *renderizador);
	int ActualizarEnPantalla(Parallax *parallax, Renderizador *renderizador);
	virtual ~ControlEnemigos();
};

#endif /* SRC_CONTROLENEMIGOS_H_ */
