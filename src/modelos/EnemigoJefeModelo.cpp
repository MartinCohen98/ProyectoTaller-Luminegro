#include "EnemigoJefeModelo.h"

EnemigoJefeModelo::EnemigoJefeModelo() {}

EnemigoJefeModelo::EnemigoJefeModelo(int posXinicial, int posYinicial,FondoModelo* fondo){
	posicionX = posXinicial;
	posicionY = posYinicial;
	ancho = 180;
	alto = 360;
	escaladoDeSprite=3.6;
	energia = 500;
	bordeSuperior = 120;
	bordeInferior = 260;
	tipoEnemigo = EnemigoJefe;
	estado = new EstadoEnemigoParado(tipoEnemigo);
	dadoVuelta = false;
	subiendo = false;
	actualizarInsercion();
}


EnemigoJefeModelo::~EnemigoJefeModelo() {}

