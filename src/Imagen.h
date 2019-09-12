#ifndef SRC_IMAGEN_H_
#define SRC_IMAGEN_H_

#include <string>
#include <SDL2/SDL.h>

class Imagen {

private:
	SDL_Surface* imagen;

public:
	Imagen();
	Imagen(const char* path);
	SDL_Surface* get();
	int cargar(const char* path);
	virtual ~Imagen();
};

#endif /* SRC_IMAGEN_H_ */
