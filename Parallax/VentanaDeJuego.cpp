#include "VentanaDeJuego.h"

VentanaDeJuego::VentanaDeJuego() {
	ventana = SDL_CreateWindow("Parallax",
	                                          SDL_WINDOWPOS_CENTERED,
	                                          SDL_WINDOWPOS_CENTERED,
	                                          640, 480,
	                                          0);
}

SDL_Window* VentanaDeJuego::Get() {
	return ventana;
}

int VentanaDeJuego::Abrir(Renderizador *renderizador) {

	if(!ventana) {
        std::cout << "No se pudo crear una ventana\n";
        return -1;
	}

    bool salir = false;
    SDL_Event evento;
    renderizador->renderizar();

    return 0;
}

VentanaDeJuego::~VentanaDeJuego() {
	if (ventana)
		SDL_DestroyWindow(ventana);
	SDL_Quit();
}

