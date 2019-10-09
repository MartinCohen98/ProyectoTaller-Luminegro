/*
 * Jugador.h
 *
 *  Created on: 8 oct. 2019
 *      Author: julio
 */

#ifndef SRC_JUGADOR_H_
#define SRC_JUGADOR_H_

#include "Protagonista.h"

class Jugador {
private:
	Protagonista protagonista;
public:
	Jugador(Renderizador *renderizador, pugi::xml_document *archiConfig);
	virtual ~Jugador();
};

#endif /* SRC_JUGADOR_H_ */
