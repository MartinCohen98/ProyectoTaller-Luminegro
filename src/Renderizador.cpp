#include "Renderizador.h"

Renderizador::Renderizador(SDL_Window* ventana) {
	renderizador = SDL_CreateRenderer(ventana, -1, 0);
}

SDL_Renderer* Renderizador::get() {
	return renderizador;
}

void Renderizador::renderizar() {
	SDL_RenderPresent(renderizador);
}

Renderizador::~Renderizador() {
	SDL_DestroyRenderer(renderizador);
}

