/*
 * ControlEnemigos.cpp
 *
 *  Created on: 18 sep. 2019
 *      Author: julio
 */

#include "ControlEnemigos.h"


ControlEnemigos::ControlEnemigos(){

}

ControlEnemigos::ControlEnemigos(Renderizador *renderizador, pugi::xml_document *archiConfig) {
	// TODO Auto-generated constructor stub
	enemigosCantidad=5;
	 const char* enemigoBredBMPPath = archiConfig->child("configuracion").child("escenario").
			 child("enemigos").child("bred").child("imagen").attribute("url").value();

	 const char* enemigoDugBMPPath = archiConfig->child("configuracion").child("escenario").
			 child("enemigos").child("dug").child("imagen").attribute("url").value();

	 const char* enemigoJakeBMPPath = archiConfig->child("configuracion").child("escenario").
			 child("enemigos").child("jake").child("imagen").attribute("url").value();

	enemigos = new Enemigo[enemigosCantidad];
	enemigos[0]=Enemigo(renderizador, 650, 220, enemigoBredBMPPath);
	enemigos[1]=Enemigo(renderizador, 0, 280, enemigoDugBMPPath);
    enemigos[2]=Enemigo(renderizador, 1500, 220, enemigoJakeBMPPath);
	enemigos[3]=Enemigo(renderizador, 1800, 220, enemigoJakeBMPPath);
};

int ControlEnemigos::InsertarEnEscenario(Renderizador *renderizador){

	};

int ControlEnemigos::ActualizarEnPantalla(Renderizador *renderizador){
	enemigos[0].retroceder();
	enemigos[1].avanzar();
	enemigos[2].retroceder();
	enemigos[3].avanzar();
	enemigos[0].actualizar(renderizador);
	enemigos[1].actualizar(renderizador);
	enemigos[2].actualizar(renderizador);
	enemigos[3].actualizar(renderizador);
	return 0;
}

ControlEnemigos::~ControlEnemigos() {
	// TODO Auto-generated destructor stub
}

