#include "ControlEnemigos.h"


ControlEnemigos::ControlEnemigos(Renderizador *renderizador, pugi::xml_document *archiConfig, int nivel) {
	enemigosCantidad=6;
	const char* enemigoBredBMPPath = archiConfig->child("configuracion").child("escenario").
			child("enemigos").child("bred").child("imagen").attribute("url").value();

	const char* enemigoDugBMPPath = archiConfig->child("configuracion").child("escenario").
			child("enemigos").child("dug").child("imagen").attribute("url").value();

	const char* enemigoJakeBMPPath = archiConfig->child("configuracion").child("escenario").
			child("enemigos").child("jake").child("imagen").attribute("url").value();
	enemigos = new Enemigo*[enemigosCantidad];

	if (nivel==1){
	    enemigos[0] = new Enemigo(renderizador, 1000, 220, enemigoBredBMPPath);
	    enemigos[1] = new Enemigo(renderizador, 500, 350, enemigoDugBMPPath);
        enemigos[2] = new Enemigo(renderizador, 3000, 220, enemigoJakeBMPPath);
	    enemigos[3] = new Enemigo(renderizador, -500, 350, enemigoJakeBMPPath);
	    enemigos[4] = new Enemigo(renderizador, 5000, 220, enemigoDugBMPPath);
	    enemigos[5] = new Enemigo(renderizador, 7000, 220, enemigoBredBMPPath);
	  }

	if (nivel==2){
		enemigos[0] = new Enemigo(renderizador, 750, 220, enemigoJakeBMPPath);
		enemigos[1] = new Enemigo(renderizador, 700, 350, enemigoBredBMPPath);
		enemigos[2] = new Enemigo(renderizador, 2500, 220, enemigoJakeBMPPath);
	    enemigos[3] = new Enemigo(renderizador, -300, 350, enemigoDugBMPPath);
		enemigos[4] = new Enemigo(renderizador, 4000, 220, enemigoBredBMPPath);
		enemigos[5] = new Enemigo(renderizador, 5500, 220, enemigoDugBMPPath);
	  }
}

void ControlEnemigos::movidaDePantalla() {
	for (int i = 0; i < enemigosCantidad; i++) {
		enemigos[i]->actualizarRetroceso();
	}
}

void ControlEnemigos::realizarMovimientos(){
	enemigos[0]->retroceder();
	enemigos[1]->avanzar();
	enemigos[2]->retroceder();
	enemigos[3]->avanzar();
	enemigos[4]->retroceder();
	enemigos[5]->retroceder();
}

void ControlEnemigos::actualizarFondo(Renderizador* renderizador) {
	enemigos[0]->actualizar(renderizador);
	enemigos[2]->actualizar(renderizador);
	enemigos[4]->actualizar(renderizador);
	enemigos[5]->actualizar(renderizador);
}

void ControlEnemigos::actualizarFrente(Renderizador* renderizador) {
	enemigos[1]->actualizar(renderizador);
	enemigos[3]->actualizar(renderizador);
}

ControlEnemigos::~ControlEnemigos() {
	if (enemigos != NULL) {
		for (int i = 0; i < enemigosCantidad; i++)
			delete enemigos[i];
		delete[] enemigos;
	}
}

