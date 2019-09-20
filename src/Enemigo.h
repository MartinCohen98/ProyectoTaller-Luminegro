/*
 * Enemigo.h
 *
 *  Created on: 15 sep. 2019
 *      Author: julio
 */

#ifndef ENEMIGO_H_
#define ENEMIGO_H_

#include "EstadoEnemigoParado.h"
#include "Imagen.h"
#include "Textura.h"
#include "Renderizador.h"
#include "Parallax.h"
#include "EstadoJugador.h"

class Enemigo {
private:
	int posicionX;
	int posicionY;
	int ancho;
	int alto;
	bool dadoVuelta;
	bool contactoVisual;
	bool modoBusqueda;
	EstadoJugador* estado;
	Imagen sprite;
	Encuadre insercion;
	Textura textura;

public:
	Enemigo(Renderizador *renderizador, int posXinicial, int posYinicial, const char* path);
	int avanzar();
	void parar();
	void retroceder();
	void agacharse();
	void subir();
	void bajar();
	void actualizar(Renderizador *renderizador);
	bool llegoAlFin(Parallax *parallax);
	int cambiarFrameInicial(int x,int y,int ancho,int alto);
	virtual ~Enemigo();

private:
	void moverEnX(int movimiento);
	int moverEnY(int nuevoY);

};

#endif /* ENEMIGO_H_ */
