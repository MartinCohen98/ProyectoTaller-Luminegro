#ifndef PARALLAX_H_
#define PARALLAX_H_

#include "Textura.h"
#include "Renderizador.h"
#include "Imagen.h"
#include "Encuadre.h"
#include <stdio.h>

class Parallax {
    private:
	   int velocidades[3];
	   int desplazamientos[3];
       Encuadre encuadres[3];
       Textura texturas[3];
       int limite;
       int resolucionX;
       int resolucionY;
       Encuadre encuadreFijo;
       bool fin;

    public:
	   Parallax(Renderizador *renderizador);
	   int actualizar(Renderizador *renderizador);
	   void mover();
	   int cargarCapas(const char *path1, const char *path2,
			   	   	   const char *path3, Renderizador* renderizador);
	   bool consultarFin();
	   int consultarAvance();
	   void cambiarLimite(int nuevoLimite);
	   virtual ~Parallax();

};

#endif /* PARALLAX_H_ */

