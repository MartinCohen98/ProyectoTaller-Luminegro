#include "VentanaDeJuego.h"

VentanaDeJuego::VentanaDeJuego() {
	anchoPantalla = 640;
	altoPantalla = 480;
}

int VentanaDeJuego::abrir() {

	SDL_Window* ventana = SDL_CreateWindow("SDL2 Window",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          anchoPantalla, altoPantalla,
                                          0);

    if(!ventana) {
        std::cout << "No se pudo crear una ventana\n";
        return -1;
	}

    bool salir = false;
    SDL_Event evento;

    while (!salir)
    {
        SDL_WaitEvent(&evento);

        switch (evento.type)
        {
        case SDL_KEYDOWN:
            salir = true;
            break;
        }
    }

    return 0;
}

VentanaDeJuego::~VentanaDeJuego() {}

