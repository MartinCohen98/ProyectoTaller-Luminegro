#include <stdio.h>
#include "VentanaDeJuego.h"
#include "Renderizador.h"
#include "Protagonista.h"
#include <SDL2/SDL.h>



int main () {
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "No se pudo iniciar SDL2 correctamente\n";
		return -1;
	}
	bool salir;
	SDL_Event evento;
	int retorno;
	VentanaDeJuego ventana;
	Renderizador renderizador(ventana.Get());
	for (int i = 0; i < 2; i++){
		salir = false;
		Parallax parallax(&renderizador);
		Protagonista protagonista(&renderizador);
		retorno = ventana.Abrir(&renderizador);

		if(i == 0) {
			parallax.cargarCapas("assets/images/backgrounds/clouds.bmp",
								"assets/images/backgrounds/buildings.bmp",
								"assets/images/backgrounds/terrain.bmp");
			parallax.cambiarLimite(992);
		};

		if(i == 1) {
			parallax.cargarCapas("assets/images/backgrounds/clouds.bmp",
								"assets/images/backgrounds/buildings.bmp",
								"assets/images/backgrounds/terrain2.bmp");
			parallax.cambiarLimite(735);
		};

		parallax.actualizar(&renderizador);
		while (!salir) {
			SDL_PollEvent(&evento);
			switch (evento.type){
				case SDL_KEYDOWN:
					switch (evento.key.keysym.sym){
						case SDLK_RIGHT:
							//Avanzar
							protagonista.avanzar(&parallax);
							break;
						case SDLK_LEFT:
							//Atras
							protagonista.retroceder();
							break;
						case SDLK_UP:
							//Arriba
							break;
						case SDLK_DOWN:
							//Abajo
							break;
						case SDLK_z:
							//Saltar
							break;
						case SDLK_x:
							//Agacharse
							protagonista.agacharse();
							break;
						case SDLK_c:
							//Pegar
							break;
						case SDLK_ESCAPE:
							//Salir
							salir = true;
							break;
					}
					break;
				case SDL_KEYUP:
					protagonista.parar();
					break;
				case SDL_QUIT:
					salir = true;
					break;
			}
			parallax.actualizar(&renderizador);
			protagonista.actualizar(&renderizador);
			renderizador.renderizar();
			if (!salir)
				salir = parallax.consultarFin();
			SDL_Delay(16);
		}
	}
	return retorno;
}


