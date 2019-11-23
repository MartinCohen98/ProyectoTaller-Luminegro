#include "Textura.h"

Textura::Textura(){
	textura = NULL;
}

Textura::Textura(Renderizador* renderizador, Imagen imagen) {
	textura = SDL_CreateTextureFromSurface(renderizador->get(), imagen.get());
}

void Textura::copiarseEn(Renderizador* renderizador, Encuadre encuadre,
						Encuadre encuadreFijo) {
	SDL_Rect e,ef;
	e = encuadre.get();
	ef = encuadreFijo.get();
	SDL_RenderCopy(renderizador->get(), textura, &e, &ef);
}

void Textura::copiarseInvertidoEn(Renderizador* renderizador, Encuadre encuadre,
									Encuadre encuadreFijo) {
	SDL_Rect e,ef;
	e = encuadre.get();
	ef = encuadreFijo.get();
	SDL_RendererFlip flip = SDL_FLIP_HORIZONTAL;
	SDL_RenderCopyEx(renderizador->get(), textura, &e, &ef, 0, NULL, flip);
}

int Textura::texturizar(Renderizador* renderizador,Imagen imagen) {
	if (textura != NULL)
		SDL_DestroyTexture(textura);
	textura = SDL_CreateTextureFromSurface(renderizador->get(), imagen.get());
	return 0;

}

void Textura::copiarseEn(Renderizador *renderizador, Encuadre encuadre) {
    SDL_Rect rectDest = encuadre.get();
    SDL_RenderCopy(renderizador->get(), textura, NULL, &rectDest);
}

Textura::~Textura() {
    if (textura != NULL)
        SDL_DestroyTexture(textura);
}
