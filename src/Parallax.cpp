#include "Parallax.h"
#include "Textura.h"
#include "Renderizador.h"
#include "Imagen.h"



Parallax::Parallax(Renderizador *renderizador) {
	resolucionX = 800;
	resolucionY = 600;
	limite = 0;
	velocidades[0] = 2;
	velocidades[1] = 3;
	velocidades[2] = 7;
	desplazamientos[0] = 0;
	desplazamientos[1] = 0;
	desplazamientos[2] = 0;
	capas[0].cargar("assets/images/general/load.png");
	capas[1].cargar("assets/images/general/load.png");
	capas[2].cargar("assets/images/general/load.png");
	encuadres[0].modificar(0, 0, 260, 195);
	encuadres[1].modificar(0, 0, 260, 195);
	encuadres[2].modificar(0, 0, 260, 195);
	encuadreFijo.modificar(0, 0, resolucionX, resolucionY);
	fin = false;
	for (int i = 0; i <= 2; i++) {
		 texturas[i].texturizar(renderizador, capas[i]);
		 texturas[i].copiarseEn(renderizador, encuadres[i], encuadreFijo);
	}
	renderizador->renderizar();
}

int Parallax::actualizar(Renderizador *renderizador) {
	for (int i=0;i<=2;i++) {
	    encuadres[i].modificar(desplazamientos[i], 0, 260, 195);
	    texturas[i].texturizar(renderizador, capas[i]);
        texturas[i].copiarseEn(renderizador, encuadres[i], encuadreFijo);
	}
	return 0;
}

void Parallax::mover() {
	for (int i=0;i<=2;i++) {
		if (desplazamientos[i] < (limite - 260)) {
			desplazamientos[i] = desplazamientos[i] + velocidades[i];
		} else {
			fin = true;
		}
	}
}

int Parallax::cargarCapas(const char *path1, const char *path2, const char *path3) {
	capas[0].cargar(path1);
	capas[1].cargar(path2);
	capas[2].cargar(path3);
	return 0;
}

bool Parallax::consultarFin() {
	return fin;
}

void Parallax::cambiarLimite(int nuevoLimite) {
	limite = nuevoLimite;
}

Parallax::~Parallax() {}
