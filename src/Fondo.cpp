#include "Fondo.h"

Fondo::Fondo(Renderizador *renderizador, pugi::xml_document* archiConfig, int nivel) {
	resolucionX = 800;
	resolucionY = 600;
	velocidades[0] = 1;
	velocidades[1] = 2;
	velocidades[2] = 4;
	desplazamientos[0] = 0;
	desplazamientos[1] = 0;
	desplazamientos[2] = 0;
	movido = false;
    Imagen capas[3];

    std::string nivelNodeName = "nivel";
    nivelNodeName.append(std::to_string(nivel));

    std::string nubesBMPPath = archiConfig->child("configuracion").child("escenario")
            .child("niveles").child( nivelNodeName.data() ).child_value("nubes");

    std::string edificiosBMPPath = archiConfig->child("configuracion").child("escenario")
            .child("niveles").child( nivelNodeName.data() ).child_value("edificios");

    std::string terrenoBMPPath = archiConfig->child("configuracion").child("escenario")
            .child("niveles").child( nivelNodeName.data() ).child_value("terreno");

    std::string terrenoWidthString = archiConfig->child("configuracion").child("escenario")
            .child("niveles").child( nivelNodeName.data() ).child_value("terrenoWidth");


	capas[0].cargar(nubesBMPPath.data(), Imagen::TIPO_FONDO);
	capas[1].cargar(edificiosBMPPath.data(), Imagen::TIPO_FONDO);
	capas[2].cargar(terrenoBMPPath.data(), Imagen::TIPO_FONDO);

	limite = std::stoi(terrenoWidthString);

	encuadres[0].modificar(0, 0, 260, 195);
	encuadres[1].modificar(0, 0, 260, 195);
	encuadres[2].modificar(0, 0, 260, 195);
	encuadreFijo.modificar(0, 0, resolucionX, resolucionY);
	fin = false;
	for (int i = 0; i <= 2; i++) {
		 texturas[i].texturizar(renderizador, capas[i]);
		 texturas[i].copiarseEn(renderizador, encuadres[i], encuadreFijo);
	}
}

int Fondo::actualizar(Renderizador *renderizador) {
	for (int i = 0; i <= 2; i++) {
	    encuadres[i].modificar(desplazamientos[i], 0, 260, 195);
        texturas[i].copiarseEn(renderizador, encuadres[i], encuadreFijo);
	}
	movido = false;
	return 0;
}

void Fondo::mover() {
	for (int i = 0; i <= 2; i++) {
		if (desplazamientos[i] < (limite - 260)) {
			desplazamientos[i] = desplazamientos[i] + velocidades[i];
		} else {
			fin = true;
		}
	}
	movido = true;
}

bool Fondo::consultarFin() {
	return fin;
}

bool Fondo::seMovio() {
	return movido;
}

int Fondo::obtenerAncho() {
	return limite;
}

Fondo::~Fondo() {}
