#include "Textura.h"

Textura::Textura(Renderizador* renderizador, Imagen* imagen) {
				textura = SDL_CreateTextureFromSurface(renderizador->get(), imagen->get());
}

void Textura::copiarseEn(Renderizador* renderizador) {
	SDL_RenderCopy(renderizador->get(), textura, NULL, NULL);
}

Textura::~Textura() {
	SDL_DestroyTexture(textura);
}

