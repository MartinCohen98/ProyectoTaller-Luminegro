#include "EnemigoJefeModelo.h"

EnemigoJefeModelo::EnemigoJefeModelo() {}

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


EnemigoJefeModelo::~EnemigoJefeModelo() {}

