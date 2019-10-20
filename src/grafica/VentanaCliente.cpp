/*
 * VentanaCliente.cpp
 *
 *  Created on: 9 oct. 2019
 *      Author: julio
 */

#include "VentanaCliente.h"

using namespace std;

VentanaCliente::VentanaCliente() {
	ventana = SDL_CreateWindow("Final Luminegro Fight",
								SDL_WINDOWPOS_CENTERED,
								SDL_WINDOWPOS_CENTERED,
								800, 600,
								0);
}

int VentanaCliente::abrir(pugi::xml_document* archiConfig) {

	if(!ventana)
		return -1;
	else
        return 0;

}

SDL_Window* VentanaCliente::get(){
	return ventana;
}

VentanaCliente::~VentanaCliente() {
	if (ventana)
		SDL_DestroyWindow(ventana);
	SDL_Quit();
}


