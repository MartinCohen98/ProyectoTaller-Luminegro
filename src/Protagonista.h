/*
 * Protagonista.h
 *
 *  Created on: 11 sep. 2019
 *      Author: julio
 */

#ifndef PROTAGONISTA_H_
#define PROTAGONISTA_H_

#include "Imagen.h"
#include "Encuadre.h"
#include "Textura.h"
#include "Renderizador.h"

class Protagonista {
private:
       int posicionX;
       int posicionY;
       Imagen sprite;
       Encuadre frameActual;
       Encuadre insercion;
       Textura textura;
public:
       Protagonista(Renderizador *renderizador);
       int CambiarPosicion(Renderizador *renderizador, int nuevoX, int nuevoY);
       virtual ~Protagonista();
};



#endif /* PROTAGONISTA_H_ */
