/*
 * ControlEnemigos.cpp
 *
 *  Created on: 18 sep. 2019
 *      Author: julio
 */

#include "ControlEnemigos.h"


ControlEnemigos::ControlEnemigos(){

}

ControlEnemigos::ControlEnemigos(Renderizador *renderizador) {
	// TODO Auto-generated constructor stub
	enemigosCantidad=5;
	enemigos = new Enemigo[enemigosCantidad];
	enemigos[0]=Enemigo(renderizador, 650, 220, "assets/images/sprites/bred.bmp");
	enemigos[1]=Enemigo(renderizador, 0, 280, "assets/images/sprites/dug.bmp");
    enemigos[2]=Enemigo(renderizador, 1500, 220, "assets/images/sprites/jake.bmp");
	enemigos[3]=Enemigo(renderizador, 1800, 220, "assets/images/sprites/jake.bmp");
};

int ControlEnemigos::InsertarEnEscenario(Renderizador *renderizador){
	;
	}

int ControlEnemigos::ActualizarEnPantalla(Parallax *parallax,Renderizador *renderizador){
/*	enemigos[0].retroceder();
	enemigos[1].avanzar(parallax);
	enemigos[2].retroceder();
	enemigos[3].avanzar(parallax);
	enemigos[0].actualizar(renderizador);
	enemigos[1].actualizar(renderizador);
	enemigos[2].actualizar(renderizador);
	enemigos[3].actualizar(renderizador);*/
}

ControlEnemigos::~ControlEnemigos() {
	// TODO Auto-generated destructor stub
}

