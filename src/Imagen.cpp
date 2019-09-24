#include "Imagen.h"

const int Imagen::TIPO_OBJETO = 1;
const int Imagen::TIPO_FONDO = 2;
const int Imagen::TIPO_PERSONAJE = 3;

Imagen::Imagen(){
	imagen = NULL;
}

Imagen::Imagen(const char* path) {
}

SDL_Surface* Imagen::get() {
	return imagen;
}

int Imagen::cargar(const char* path, const int tipo) {
	imagen = SDL_LoadBMP(path);

	// Se encontró la imagen?
	if (imagen == NULL) {
	    // No che
	    switch (tipo) {
            case TIPO_OBJETO:
                // Reemplazamos por algo
                imagen = SDL_LoadBMP("assets/images/missingPictures/box.bmp");
                break;
            case TIPO_FONDO:
                // Hacemos una basada sólo en un color
                imagen = SDL_CreateRGBSurface(0, 200, 200, 32, 0, 0, 0, 0);
                SDL_FillRect(imagen, NULL, SDL_MapRGB(imagen->format, 12, 183, 242));
                break;
            case TIPO_PERSONAJE:
                // Reemplazamos por algo
                imagen = SDL_LoadBMP("assets/images/missingPictures/person.bmp");
                break;
        }
    }

	return 0;
}

Imagen::~Imagen() {}

