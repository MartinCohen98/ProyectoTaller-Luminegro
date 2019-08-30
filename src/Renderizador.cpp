#include "Renderizador.h"

Renderizador::Renderizador(SDL_Window* ventana) {
	renderizador = SDL_CreateRenderer(ventana, -1, 0);
}

Renderizador::~Renderizador() {}

