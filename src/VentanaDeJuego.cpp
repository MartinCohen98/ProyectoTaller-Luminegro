#include "VentanaDeJuego.h"

VentanaDeJuego::VentanaDeJuego() {
	ventana = SDL_CreateWindow("SDL2 Window",
	                                          SDL_WINDOWPOS_CENTERED,
	                                          SDL_WINDOWPOS_CENTERED,
	                                          640, 480,
	                                          0);
}

int VentanaDeJuego::abrir() {
	if(!ventana) {
        std::cout << "No se pudo crear una ventana\n";
        return -1;
	}

    bool salir = false;
    SDL_Event evento;
    Renderizador renderizador(ventana);
    Imagen imagen("assets/missing.bmp");
    Textura textura(&renderizador, &imagen);
    while (!salir) {
        SDL_WaitEvent(&evento);
        switch (evento.type) {
        	case SDL_KEYDOWN:	salir = true;
            					break;
        }
        textura.copiarseEn(&renderizador);
        renderizador.renderizar();
    }

    return 0;
}

VentanaDeJuego::~VentanaDeJuego() {
	if (ventana)
		SDL_DestroyWindow(ventana);
	SDL_Quit();
}

