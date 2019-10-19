#include "Elemento.h"

Elemento::Elemento() {
	posicionX = 0;
	posicionY = 0;
	alto = 0;
	ancho = 0;
}


void Elemento::movidaDePantalla() {
	posicionX = posicionX - 12;
	insercion.modificar(posicionX,posicionY,ancho,alto);
}


void Elemento::actualizar(Renderizador *renderizador) {
	textura.copiarseEn(renderizador, encuadre, insercion);
}


Elemento::~Elemento() {}

