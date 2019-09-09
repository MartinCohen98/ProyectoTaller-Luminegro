/*
 * Parallax.cpp
 *
 *  Created on: 4 sep. 2019
 *      Author: julio
 */

#include "Parallax.h"
#include "Textura.h"
#include "Renderizador.h"



Parallax::Parallax(Renderizador *renderizador){
	resolucionX=640;
	resolucionY=480;
	limite=2442;
	velocidades[0]=5;
	velocidades[1]=10;
	velocidades[2]=20;
	desplazamientos[0]=0;
	desplazamientos[1]=0;
	desplazamientos[2]=0;
	capas[0] = SDL_LoadBMP("assets/images/backgrounds/clouds.bmp");
	capas[1] = SDL_LoadBMP("assets/images/backgrounds/buildings.bmp");
	capas[2] = SDL_LoadBMP("assets/images/backgrounds/terrain.bmp");
	marcos[0] = {0,0,resolucionX,resolucionY};
	marcos[1] = {0,0,resolucionX,resolucionY};
	marcos[2] = {0,0,resolucionX,resolucionY};
	marcoFijo = {0,0,resolucionX,resolucionY};
	fin=false;
	for (int i=0;i<=2;i++) {
		 texturas[i]=SDL_CreateTextureFromSurface(renderizador->get(),capas[i]);
		 SDL_RenderCopy(renderizador->get(),texturas[i],&marcos[i],&marcoFijo);
	}
	SDL_RenderPresent(renderizador->get());
}

int Parallax::Actualizar(Renderizador *renderizador) {
	          for (int i=0;i<=2;i++) {
	             if (desplazamientos[i]<limite-640){
		             desplazamientos[i]=desplazamientos[i]+velocidades[i];
	             }
	             else {
	            	 fin=true;
	             }
	             marcos[i]={desplazamientos[i],0,resolucionX,resolucionY};
                 texturas[i]=SDL_CreateTextureFromSurface(renderizador->get(),capas[i]);
                 SDL_RenderCopy(renderizador->get(),texturas[i],&marcos[i],&marcoFijo);
                 SDL_RenderPresent(renderizador->get());
	             }
	          return 0;
}

bool Parallax::ConsultarFin(){
	      return fin;
	             }


Parallax::~Parallax(){

}
