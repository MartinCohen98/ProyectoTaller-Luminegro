/*
 * mainParallax.cpp
 *
 *  Created on: 4 sep. 2019
 *      Author: julio
 */


#include <stdio.h>
#include "VentanaDeJuego.h"
#include "Renderizador.h"
#include "Parallax.h"
#include <SDL2/SDL.h>



int main () {
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
	        std::cout << "No se pudo iniciar SDL2 correctamente\n";
	        return -1;
	    }
	bool salir=false;
	SDL_Event evento;
	VentanaDeJuego ventana;
	Renderizador renderizador(ventana.Get());
	int retorno = ventana.Abrir(&renderizador);
	Parallax parallax(&renderizador);

	 while (!salir) {
	        SDL_WaitEvent(&evento);
	        switch (evento.type){
	             case SDL_KEYDOWN:
	            	 switch (evento.key.keysym.sym){
	                       case SDLK_RIGHT:
	                            parallax.Actualizar(&renderizador);
	                       }
	           }
	        salir=parallax.ConsultarFin();
	   }
	return retorno;

}





