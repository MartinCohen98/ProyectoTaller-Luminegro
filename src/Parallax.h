#ifndef PARALLAX_H_
#define PARALLAX_H_
#include "VentanaDeJuego.h"
#include "Renderizador.h"
#include "Imagen.h"
#include "Encuadre.h"
#include <stdio.h>

class Parallax {
    private:
	   int velocidades[3];
	   int desplazamientos[3];
       Imagen capas[3];
       Encuadre encuadres[3];
       Textura texturas[3];
       int limite;
       int resolucionX;
       int resolucionY;
       Encuadre encuadreFijo;
       bool fin;

    public:
	   Parallax(Renderizador *renderizador);
	   int Actualizar(Renderizador *renderizador);
	   int CargarCapas(const char *path1, const char *path2, const char *path3);
	   bool ConsultarFin();
	   void CambiarLimite(int nuevoLimite);
	   virtual ~Parallax();

};

#endif /* PARALLAX_H_ */

