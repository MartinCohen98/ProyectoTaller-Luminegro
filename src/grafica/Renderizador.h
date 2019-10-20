#ifndef SRC_RENDERIZADOR_H_
#define SRC_RENDERIZADOR_H_

#include <SDL2/SDL.h>

class Renderizador {

private:
	SDL_Renderer* renderizador;

public:
	Renderizador(SDL_Window *ventana);
	SDL_Renderer* get();
	void renderizar();
	virtual ~Renderizador();
};

#endif /* SRC_RENDERIZADOR_H_ */
