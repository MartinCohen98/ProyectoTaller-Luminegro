#ifndef SRC_IMAGEN_H_
#define SRC_IMAGEN_H_

#include <string>
#include <SDL2/SDL.h>
#include "varios/Logger.h"

class Imagen {

private:
	SDL_Surface* imagen;

public:
    static const int TIPO_OBJETO = 1;
    static const int TIPO_FONDO = 2;
    static const int TIPO_PERSONAJE = 3;

	Imagen();
	SDL_Surface* get();
	int cargar(const char* path, const int tipo);
	virtual ~Imagen();
};

#endif /* SRC_IMAGEN_H_ */
