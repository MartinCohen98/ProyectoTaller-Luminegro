#include "FondoModelo.h"

FondoModelo::FondoModelo(pugi::xml_document* archiConfig, int nivel) {
	resolucionX = 800;
	resolucionY = 600;
	velocidades[0] = 1;
	velocidades[1] = 2;
	velocidades[2] = 4;
	desplazamientos[0] = 0;
	desplazamientos[1] = 0;
	desplazamientos[2] = 0;
	movido = false;

	std::string nivelNodeName = "nivel";
	nivelNodeName.append(std::to_string(nivel));

	std::string terrenoWidthString = archiConfig->child("configuracion").child("escenario")
                .child("niveles").child( nivelNodeName.data() ).child_value("terrenoWidth");

	limite = std::stoi(terrenoWidthString);

	encuadres[0].modificar(0, 0, 260, 195);
	encuadres[1].modificar(0, 0, 260, 195);
	encuadres[2].modificar(0, 0, 260, 195);
	encuadreFijo.modificar(0, 0, resolucionX, resolucionY);
	fin = false;
}

void FondoModelo::mover() {
	if (!movido)
		for (int i = 0; i <= 2; i++) {
			if (desplazamientos[i] < (limite - 260)) {
				desplazamientos[i] = desplazamientos[i] + velocidades[i];
			} else {
				fin = true;
			}
		}
	movido = true;
}


void FondoModelo::generarMensajes(MensajeServidor* mensajes, int* mensajeActual) {
	for (int i = 0; i <= 2; i++) {
		encuadres[i].modificar(desplazamientos[i], 0, 260, 195);
	}
	movido = false;
	for ((*mensajeActual) = 0; (*mensajeActual) < 3; (*mensajeActual)++) {
		mensajes[*mensajeActual].generarMensaje(&encuadres[*mensajeActual],
					&encuadreFijo, Jugador1);
	}
}


bool FondoModelo::seMovio() {
	return movido;
}


bool FondoModelo::consultarFin() {
	return (fin && !movido);
}


int FondoModelo::obtenerAncho() {
	return limite;
}

FondoModelo::~FondoModelo() {}

