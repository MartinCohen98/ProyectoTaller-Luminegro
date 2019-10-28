#include "MensajeServidor.h"

using namespace std;

MensajeServidor::MensajeServidor() {
	sprite = Jugador1;
	dadoVuelta = false;
}

void MensajeServidor::generarMensaje(Encuadre* unFrame,
		Encuadre* unaInsercion, tipoDeSprite tipo) {
	if (unFrame != NULL)
		frame = *unFrame;
	if (unaInsercion != NULL)
		insercion = *unaInsercion;
	sprite = tipo;
	dadoVuelta = false;
}


void MensajeServidor::darVuelta() {
	dadoVuelta = true;
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
	return ((insercion.getY() + insercion.getAlto()) <
			(mensaje.insercion.getY() +
			mensaje.insercion.getAlto()));
}


MensajeServidor::~MensajeServidor() {}

