#include "ElementoModelo.h"

ElementoModelo::ElementoModelo() {
	posicionX = 0;
	posicionY = 0;
	ancho = 0;
	alto = 0;
}


void ElementoModelo::movidaDePantalla() {
	posicionX = posicionX - 12;
	insercion.modificar(posicionX, posicionY, ancho, alto);
}


void ElementoModelo::enviarEncuadres(Socket*& sockets, int cantidad) {
	MensajeServidor mensaje;
	mensaje.generarMensaje(&encuadre, &insercion, Jugador1);
	for (int i = 0; i < cantidad; i++) {
		sockets[i].enviar(&mensaje);
	}
}


ElementoModelo::~ElementoModelo() {}

