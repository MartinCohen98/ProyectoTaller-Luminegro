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

class ControlObjetos {
private:
	int desplazamiento;
public:
	ControlObjetos();
	bool Actualizar(Renderizador *renderizador,int avance);
	virtual ~ControlObjetos();
};

#endif /* SRC_CONTROLOBJETOS_H_ */
