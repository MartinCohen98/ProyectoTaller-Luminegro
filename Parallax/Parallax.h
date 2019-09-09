/*
 * Parallax.h
 *
 *  Created on: 4 sep. 2019
 *      Author: julio
 */

#ifndef PARALLAX_H_
#define PARALLAX_H_
#include "VentanaDeJuego.h"
#include "Renderizador.h"
#include <stdio.h>

class Parallax {
    private:
	   int velocidades[3];
	   int desplazamientos[3];
       SDL_Surface * capas[3];
       SDL_Rect marcos[3];
       SDL_Texture * texturas[3];
       int limite;
       int resolucionX;
       int resolucionY;
       SDL_Rect marcoFijo;
       bool fin;

    public:
	   Parallax(Renderizador *renderizador);
	   int Actualizar(Renderizador *renderizador);
	   bool ConsultarFin();
	   virtual ~Parallax();

};

#endif /* PARALLAX_H_ */

