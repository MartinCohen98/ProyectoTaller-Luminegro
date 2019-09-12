#include "Textura.h"

Textura::Textura(){
	textura = NULL;
}

Textura::Textura(Renderizador* renderizador, Imagen imagen) {
				textura = SDL_CreateTextureFromSurface(renderizador->get(), imagen.get());
}

void Textura::copiarseEn(Renderizador* renderizador,Encuadre encuadre,Encuadre encuadreFijo) {
	SDL_Rect e,ef;
	e = encuadre.get();
	ef = encuadreFijo.get();
	SDL_RenderCopy(renderizador->get(),textura,&e,&ef);
}

int Textura::texturizar(Renderizador* renderizador,Imagen imagen) {
	textura = SDL_CreateTextureFromSurface(renderizador->get(), imagen.get());
	return 0;

}


Textura::~Textura() {
	SDL_DestroyTexture(textura);
}

