#include "CuchilloModelo.h"

CuchilloModelo::CuchilloModelo(int posXinicial, int posYinicial) {
	posicionX = posXinicial;
	posicionY = posYinicial;
	ancho = 66;
	alto = 21;
	sprite = Cuchillo;

	encuadre.modificar(0,0,66,21);
	insercion.modificar(posXinicial, posYinicial, ancho, alto);
}

CuchilloModelo::~CuchilloModelo() {}

