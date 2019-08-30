#include "VentanaDeJuego.h"

int main () {
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "No se pudo iniciar SDL2 correctamente\n";
        return -1;
    }

	VentanaDeJuego ventana;
	int retorno = ventana.abrir();
	return retorno;
}

