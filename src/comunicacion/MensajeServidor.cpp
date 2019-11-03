#include "MensajeServidor.h"

using namespace std;

MensajeServidor::MensajeServidor() {
	sprite = Jugador1;
	dadoVuelta = false;
	posicionY = 0;
}

void MensajeServidor::generarMensaje(Encuadre* unFrame,
		Encuadre* unaInsercion, tipoDeSprite tipo) {
	if (unFrame != NULL)
		frame = *unFrame;
	if (unaInsercion != NULL) {
		insercion = *unaInsercion;
		posicionY = insercion.getY();
	}
	sprite = tipo;
	dadoVuelta = false;
}


void MensajeServidor::darVuelta() {
	dadoVuelta = true;
}


void MensajeServidor::agregarPosicionY(int posicion) {
	posicionY = posicion;
}


Encuadre* MensajeServidor::obtenerFrame() {
	return &frame;
}


Encuadre* MensajeServidor::obtenerInsercion() {
	return &insercion;
}


tipoDeSprite MensajeServidor::obtenerTipoDeSprite() {
	return sprite;
}


bool MensajeServidor::estaDadoVuelta() {
	return dadoVuelta;
}

bool MensajeServidor::operator <(const MensajeServidor & mensaje) const {
	return ((posicionY + insercion.getAlto()) <
			(mensaje.posicionY + mensaje.insercion.getAlto()));
}


MensajeServidor::~MensajeServidor() {}

