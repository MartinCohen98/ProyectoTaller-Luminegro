#include "EnemigoJefeModelo.h"

EnemigoJefeModelo::EnemigoJefeModelo(int posXinicial, int posYinicial,FondoModelo* fondoNuevo){
	posicionX = posXinicial;
	posicionY = posYinicial;
	ancho = 180;
	alto = 360;
	escaladoDeSprite = 3;
	energia = 500;
	fondo = fondoNuevo;
	bordeSuperior = 60;
	bordeInferior = 200;
	limiteInicial = 0;
	limiteFinal = fondo->obtenerAncho();
	tipo = EnemigoJefe;
	estado = new EstadoEnemigoParado(tipo);
	dadoVuelta = false;
	subiendo = false;
	tiempoDeGolpe = 0;
	tiempoDeEsquivada = 0;
	vivo = true;
	esAtacante = true;
	activado = false;
	estadoOriginal = new EstadoEnemigoParado(tipo);
	actualizarInsercion();
	delayDeGolpe = 0;
}


EnemigoJefeModelo::~EnemigoJefeModelo() {}

