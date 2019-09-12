/*
 * Parallax.cpp
 *
 *  Created on: 4 sep. 2019
 *      Author: julio
 */

#include "Parallax.h"
#include "Textura.h"
#include "Renderizador.h"
#include "Imagen.h"



Parallax::Parallax(Renderizador *renderizador) {
	resolucionX = 640;
	resolucionY = 480;
	limite = 2442;
	velocidades[0] = 5;
	velocidades[1] = 10;
	velocidades[2] = 20;
	desplazamientos[0] = 0;
	desplazamientos[1] = 0;
	desplazamientos[2] = 0;
	capas[0].cargar("assets/images/general/load.png");
	capas[1].cargar("assets/images/general/load.png");
	capas[2].cargar("assets/images/general/load.png");
	encuadres[0].Modificar(0, 0, resolucionX, resolucionY);
	encuadres[1].Modificar(0, 0, resolucionX, resolucionY);
	encuadres[2].Modificar(0, 0, resolucionX, resolucionY);
	encuadreFijo.Modificar(0, 0, resolucionX, resolucionY);
	fin = false;
	for (int i = 0; i <= 2; i++) {
		 texturas[i].texturizar(renderizador, capas[i]);
		 texturas[i].copiarseEn(renderizador, encuadres[i], encuadreFijo);
	}
	renderizador->renderizar();
}

int Parallax::Actualizar(Renderizador *renderizador) {
	for (int i=0;i<=2;i++) {
		if (desplazamientos[i] < (limite - 640)) {
			desplazamientos[i] = desplazamientos[i] + velocidades[i];
		} else {
			fin = true;
		}
	    encuadres[i].Modificar(desplazamientos[i], 0, resolucionX, resolucionY);
	    texturas[i].texturizar(renderizador, capas[i]);
        texturas[i].copiarseEn(renderizador, encuadres[i], encuadreFijo);
	}
	return 0;
}

int Parallax::CargarCapas(const char *path1, const char *path2, const char *path3) {
	capas[0].cargar(path1);
	capas[1].cargar(path2);
	capas[2].cargar(path3);
	return 0;
}

bool Parallax::ConsultarFin() {
	return fin;
}

void Parallax::CambiarLimite(int nuevoLimite) {
	limite = nuevoLimite;
}

Parallax::~Parallax() {}
