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

	for (int i=0;i<2;i++){


	   VentanaDeJuego ventana;
	   Renderizador renderizador(ventana.Get());
	   retorno = ventana.Abrir(&renderizador);
       salir=false;
	   Parallax parallax(&renderizador);
	   Protagonista protagonista(&renderizador);


		   if(i==0) {
			    parallax.CargarCapas("assets/images/backgrounds/clouds.bmp",
			    		             "assets/images/backgrounds/buildings.bmp",
			    		             "assets/images/backgrounds/terrain.bmp");
			    parallax.CambiarLimite(2442);
	          };

		   if(i==1) {
				 parallax.CargarCapas("assets/images/backgrounds/clouds.bmp",
						    		             "assets/images/backgrounds/buildings.bmp",
						    		             "assets/images/backgrounds/terrain2.bmp");
				 parallax.CambiarLimite(1809);
		      };


	   while (!salir) {
	          SDL_WaitEvent(&evento);
	          switch (evento.type){
	               case SDL_KEYDOWN:
	                	 switch (evento.key.keysym.sym){
	                         case SDLK_RIGHT:
	                            parallax.Actualizar(&renderizador);
	                            protagonista.CambiarPosicion(&renderizador,5,1);
	                            break;
	                         case SDLK_LEFT:
	                        	 //Atras
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
	                        	 break;
	                       }
	           }
	        renderizador.renderizar();
	        salir=parallax.ConsultarFin();
	   }

	}

	return retorno;

}





