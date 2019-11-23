#include "EnemigoJefeModelo.h"

EnemigoJefeModelo::EnemigoJefeModelo() {}

EnemigoJefeModelo::EnemigoJefeModelo(int posXinicial, int posYinicial,FondoModelo* fondo){
	posicionX = posXinicial;
	posicionY = posYinicial;
	ancho = 180;
	alto = 360;
	escaladoDeSprite=2.7;
	energia = 500;
	bordeSuperior = 100;
	bordeInferior = 240;
	limiteInicial = 0;
	limiteFinal = fondo->obtenerAncho();
	tipoEnemigo = EnemigoJefe;
	estado = new EstadoEnemigoParado(tipoEnemigo);
	dadoVuelta = false;
	subiendo = false;
	tiempoDeGolpe=0;
	tiempoDeEsquivada=0;
	vivo=true;
	actualizarInsercion();
}


EnemigoJefeModelo::~EnemigoJefeModelo() {}

