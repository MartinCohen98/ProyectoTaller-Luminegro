#ifndef SRC_IMAGEN_H_
#define SRC_IMAGEN_H_

#include <string>
#include <SDL2/SDL.h>

class Imagen {

private:
	SDL_Surface* imagen;

public:
    static const int TIPO_OBJETO;
    static const int TIPO_FONDO;
    static const int TIPO_PERSONAJE;

	Imagen();
	Imagen(const char* path);
	SDL_Surface* get();
	int cargar(const char* path, const int tipo);
	virtual ~Imagen();
};

#endif /* SRC_IMAGEN_H_ */
