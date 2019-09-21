/*
 * ControlObjetos.h
 *
 *  Created on: 19 sep. 2019
 *      Author: julio
 */

#ifndef SRC_CONTROLOBJETOS_H_
#define SRC_CONTROLOBJETOS_H_

#include "Renderizador.h"
#include "Parallax.h"
#include "Barril.h"
#include "Caja.h"
#include "Cuchillo.h"
#include "Tubo.h"
#include "../lib/pugixml/pugixml.hpp"

class ControlObjetos {
private:
	int desplazamiento;
	int cantBarriles;
	int cantCajas;
	int cantCuchillos;
	int cantTubos;
	Barril barriles[10];
	Caja cajas[10];
	Cuchillo cuchillos[10];
	Tubo tubos[10];
public:
	ControlObjetos();
	ControlObjetos(Renderizador *renderizador, pugi::xml_document *archiConfig);
	bool Actualizar(Renderizador *renderizador,int avance);
	virtual ~ControlObjetos();
};

#endif /* SRC_CONTROLOBJETOS_H_ */
