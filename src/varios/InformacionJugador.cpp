#include "InformacionJugador.h"

InformacionJugador::InformacionJugador(int socket, int elNumeroDeJugador) {
	numeroSocket = socket;
	numeroDeJugador = elNumeroDeJugador;
}


int InformacionJugador::obtenerSocket() {
	return numeroSocket;
}


int InformacionJugador::obtenerNumeroDeJugador() {
	return numeroDeJugador;
}


InformacionJugador::~InformacionJugador() {}

