#include "Imagen.h"


Imagen::Imagen(){
	imagen = NULL;
}

SDL_Surface* Imagen::get() {
	return imagen;
}

int Imagen::cargar(const char* path, const int tipo) {
	imagen = SDL_LoadBMP(path);

	// Se encontró la imagen?
	if (imagen == NULL) {
		std::string mensajeError = "No se encontró la imagen: ";
		mensajeError.append(path);
		Logger::Log *logueador  =  Logger::Log::ObtenerInstancia();
		logueador->Error(mensajeError);
	    // No che
	    switch (tipo) {
            case TIPO_OBJETO:
                // Reemplazamos por una caja
                imagen = SDL_LoadBMP("assets/images/missingPictures/box.bmp");
                break;
            case TIPO_FONDO:
                // Hacemos una basada sólo en un color
                imagen = SDL_CreateRGBSurface(0, 200, 200, 32, 0, 0, 0, 0);
                SDL_FillRect(imagen, NULL, SDL_MapRGB(imagen->format, 12, 183, 242));
                break;
            case TIPO_PERSONAJE:
                // Reemplazamos por un muñeco
                imagen = SDL_LoadBMP("assets/images/missingPictures/person.bmp");
                break;
            case TIPO_DESCONECTADO:
                // Reemplazamos por un muñeco
                imagen = SDL_LoadBMP("assets/images/general/cerrandoJuego.bmp");
                break;

        }
    } /*else {
    	std::string mensajeCarga = "Se cargo la imagen: ";
    	mensajeCarga.append(path);
    	Logger::Log *logueador  =  Logger::Log::ObtenerInstancia();
    	logueador->Debug(mensajeCarga);
    }*/

	return 0;
}

Imagen::~Imagen() {}

