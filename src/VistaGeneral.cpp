#include "VistaGeneral.h"

VistaGeneral::VistaGeneral() {
	renderizador = NULL;
}

void VistaGeneral::renderizarConElMensaje(MensajeServidor* mensaje) {
	Encuadre* frame = mensaje->obtenerFrame();
	Encuadre* insercion = mensaje->obtenerInsercion();
	bool dadoVuelta = mensaje->estaDadoVuelta();
	if (!dadoVuelta) {
		textura.copiarseEn(renderizador, *frame, *insercion);
	} else {
		textura.copiarseInvertidoEn(renderizador, *frame, *insercion);
	}
}

VistaGeneral::~VistaGeneral() {}

