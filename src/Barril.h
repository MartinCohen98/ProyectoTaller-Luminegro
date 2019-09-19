/*
 * Barril.h
 *
 *  Created on: 18 sep. 2019
 *      Author: julio
 */

#ifndef BARRIL_H_
#define BARRIL_H_

#include "Textura.h"
#include "Imagen.h"
#include "Textura.h"
#include "Renderizador.h"
#include "Encuadre.h"

class Barril {
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
	Barril(Renderizador *renderizador, int posXinicial, int posYinicial);
	void actualizar(Renderizador *renderizador);
	virtual ~Barril();
};

#endif /* BARRIL_H_ */
