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

	// Acá se pone true pero nunca false
	if ( mensaje->getSonidoEjecutarGolpeTiro() )     *this->ejecutarSonidoGolpeTiro = true;
	if ( mensaje->getSonidoEjecutarGolpeImpacto() )  *this->ejecutarSonidoGolpeImpacto = true;
	if ( mensaje->getSonidoEjecutarSalto() )         *this->ejecutarSonidoSalto = true;
	if ( mensaje->getSonidoEjecutarCaida() )         *this->ejecutarSonidoCaida = true;
	if ( mensaje->getSonidoEjecutarDestruccion() )   *this->ejecutarSonidoDestruccion = true;
}

VistaGeneral::~VistaGeneral() {}

