/*
 * EnemigoJefeModelo.cpp
 *
 *  Created on: 15 nov. 2019
 *      Author: julio
 */

#include "EnemigoJefeModelo.h"

EnemigoJefeModelo::EnemigoJefeModelo() {
	// TODO Auto-generated constructor stub

}

EnemigoJefeModelo::EnemigoJefeModelo(int posXinicial, int posYinicial, tipoDeSprite tipo){
	posicionX = posXinicial;
	posicionY = posYinicial;
	ancho = 200;
	alto = 400;
	energia=500;
	tipoEnemigo=tipo;
	estado = new EstadoEnemigoParado(tipoEnemigo);
	dadoVuelta = false;
	subiendo=false;
	actualizarInsercion();
}


EnemigoJefeModelo::~EnemigoJefeModelo() {
	// TODO Auto-generated destructor stub
}

