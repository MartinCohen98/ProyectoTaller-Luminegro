/*
 * Cuchillo.h
 *
 *  Created on: 18 sep. 2019
 *      Author: julio
 */

#ifndef SRC_CUCHILLO_H_
#define SRC_CUCHILLO_H_

#include "Textura.h"
#include "Imagen.h"
#include "Textura.h"
#include "Renderizador.h"
#include "Encuadre.h"
#include "../lib/pugixml/pugixml.hpp"

class Cuchillo {

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
	Cuchillo();
	Cuchillo(Renderizador *renderizador, int posXinicial, int posYinicial, pugi::xml_document *archiConfig);
	void actualizar(Renderizador *renderizador);
	void refrescar(Renderizador *renderizador);
	virtual ~Cuchillo();
};

#endif /* SRC_CUCHILLO_H_ */
