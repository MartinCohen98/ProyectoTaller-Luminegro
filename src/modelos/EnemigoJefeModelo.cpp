#include "EnemigoJefeModelo.h"

EnemigoJefeModelo::EnemigoJefeModelo() {}

EnemigoJefeModelo::EnemigoJefeModelo(int posXinicial, int posYinicial){
	posicionX = posXinicial;
	posicionY = posYinicial;
	ancho = 200;
	alto = 400;
	energia = 500;
	bordeSuperior = 80;
	bordeInferior = 220;
	tipoEnemigo = EnemigoJefe;
	estado = new EstadoEnemigoParado(tipoEnemigo);
	dadoVuelta = false;
	subiendo = false;
	actualizarInsercion();
}


EnemigoJefeModelo::~EnemigoJefeModelo() {}

