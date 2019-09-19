/*
 * Caja.h
 *
 *  Created on: 18 sep. 2019
 *      Author: julio
 */

#ifndef SRC_CAJA_H_
#define SRC_CAJA_H_

#include "Textura.h"
#include "Imagen.h"
#include "Textura.h"
#include "Renderizador.h"
#include "Encuadre.h"

class Caja {
private:
	int posicionX;
	int posicionY;
	int ancho;
	int alto;
	int escaladoDeSprite;
	Imagen sprite;
	Encuadre encuadre;
	Encuadre insercion;
	Textura textura;
public:
	Caja(Renderizador *renderizador, int posXinicial, int posYinicial);
	void actualizar(Renderizador *renderizador);
	virtual ~Caja();
};

#endif /* SRC_CAJA_H_ */
