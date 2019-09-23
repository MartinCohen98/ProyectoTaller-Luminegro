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
#include "../lib/pugixml/pugixml.hpp"


class ControlEnemigos {
private: Enemigo *enemigos;
         int enemigosCantidad;
public:
    ControlEnemigos();
	ControlEnemigos(Renderizador *renderizador, pugi::xml_document *archiConfig);
	int InsertarEnEscenario(Renderizador *renderizador);
	int ActualizarEnPantalla(Renderizador *renderizador);
	virtual ~ControlEnemigos();
};

#endif /* SRC_CONTROLENEMIGOS_H_ */
