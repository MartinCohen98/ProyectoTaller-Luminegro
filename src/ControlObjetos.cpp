/*
 * ControlObjetos.cpp
 *
 *  Created on: 19 sep. 2019
 *      Author: julio
 */

#include "ControlObjetos.h"

ControlObjetos::ControlObjetos() {
	// TODO Auto-generated constructor stub
	desplazamiento=0;

}

bool ControlObjetos::Actualizar(Renderizador *renderizador,int avance){
 if (avance>desplazamiento){
	 desplazamiento=avance;
	 return true;
    }
 else
	 return false;
 }


ControlObjetos::~ControlObjetos() {
	// TODO Auto-generated destructor stub
}

