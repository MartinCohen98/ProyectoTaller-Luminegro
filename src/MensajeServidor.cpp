#include "MensajeServidor.h"

MensajeServidor::MensajeServidor() {
	frame = NULL;
	insercion = NULL;
	tipoDeSprite = Jugador1;
	dadoVuelta = false;
}

void MensajeServidor::generarMensaje(Encuadre* unFrame,
		Encuadre* unaInsercion, sprite tipo) {
	frame = unFrame;
	insercion = unaInsercion;
	tipoDeSprite = tipo;
	dadoVuelta = false;
}

void MensajeServidor::darVuelta() {
	dadoVuelta = true;
}

MensajeServidor::~MensajeServidor() {}

