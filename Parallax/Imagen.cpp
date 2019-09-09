#include "Imagen.h"

Imagen::Imagen(const char* path) {
	imagen = SDL_LoadBMP(path);
}

SDL_Surface* Imagen::get() {
	return imagen;
}

Imagen::~Imagen() {}

