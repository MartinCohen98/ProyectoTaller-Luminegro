#include "Imagen.h"

Imagen::Imagen(){
	imagen = NULL;
}

Imagen::Imagen(const char* path) {
	imagen = SDL_LoadBMP(path);
}

SDL_Surface* Imagen::get() {
	return imagen;
}

int Imagen::cargar(const char* path) {
	imagen = SDL_LoadBMP(path);
	return 0;
}

Imagen::~Imagen() {}

