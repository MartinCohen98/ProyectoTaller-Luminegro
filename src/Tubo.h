/*
 * Tubo.h
 *
 *  Created on: 18 sep. 2019
 *      Author: julio
 */

#ifndef SRC_TUBO_H_
#define SRC_TUBO_H_

#include "Textura.h"
#include "Imagen.h"
#include "Textura.h"
#include "Renderizador.h"
#include "Encuadre.h"

class Tubo {
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
	Tubo(Renderizador *renderizador, int posXinicial, int posYinicial);
	void actualizar(Renderizador *renderizador);
	virtual ~Tubo();
};

#endif /* SRC_TUBO_H_ */
