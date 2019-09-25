#ifndef FONDO_H_
#define FONDO_H_

#include "Textura.h"
#include "Renderizador.h"
#include "Imagen.h"
#include "Encuadre.h"
#include "../lib/pugixml/pugixml.hpp"
#include <iostream>

class Fondo {
    private:
	   int velocidades[3];
	   int desplazamientos[3];
       Encuadre encuadres[3];
       Textura texturas[3];
       int limite;
       int resolucionX;
       int resolucionY;
       Encuadre encuadreFijo;
       bool movido;
       bool fin;

    public:
	   Fondo(Renderizador *renderizador,
			   pugi::xml_document* archiConfig, int nivel);
	   int actualizar(Renderizador *renderizador);
	   void mover();
	   bool consultarFin();
	   bool seMovio();
	   int consultarAvance();
	   int obtenerAncho();
	   virtual ~Fondo();

};

#endif /* PARALLAX_H_ */

