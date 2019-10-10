#include "Elemento.h"

Elemento::Elemento() {}

void Elemento::movidaDePantalla() {
	posicionX = posicionX - 12;
	insercion.modificar(posicionX,posicionY,ancho,alto);
}

void Elemento::actualizar(Renderizador *renderizador) {
	textura.copiarseEn(renderizador, encuadre, insercion);
}

Elemento::~Elemento() {}

