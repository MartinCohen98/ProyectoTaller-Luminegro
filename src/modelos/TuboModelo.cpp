#include "TuboModelo.h"

TuboModelo::TuboModelo(int posXinicial, int posYinicial) {
	posicionX = posXinicial;
	posicionY = posYinicial;
	ancho = 144;
	alto = 24;
	sprite = Tubo;

	encuadre.modificar(0,0,144,24);
	insercion.modificar(posXinicial, posYinicial, ancho, alto);
}


tipoDeArma TuboModelo::obtenerTipoDeArma() {
	return tubo;
}


TuboModelo::~TuboModelo() {}

