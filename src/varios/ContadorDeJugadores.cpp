#include "ContadorDeJugadores.h"

ContadorDeJugadores::ContadorDeJugadores(int jugadores) {
	espaciosDisponibles = jugadores;
	conectados = new bool[jugadores];
	for (int i = 0; i < jugadores; i++) {
		conectados[i] =  true;
	}
	cantidadDeRecieves = 0;
}


bool ContadorDeJugadores::hayEspacioDisponible() {
	return (espaciosDisponibles > 0);
}


void ContadorDeJugadores::seDesconectoElJugador(int jugador) {
	m.lock();
	conectados[jugador] = false;
	espaciosDisponibles++;
	m.unlock();
}


void ContadorDeJugadores::seConectoElJugador(int jugador) {
	m.lock();
	conectados[jugador] = true;
	espaciosDisponibles--;
	m.unlock();
}


void ContadorDeJugadores::actualizarCantidadDeRecieves(int recieves) {
	m.lock();
	cantidadDeRecieves = recieves;
	m.unlock();
}


int ContadorDeJugadores::obtenerCantidadDeRecieves() {
	return cantidadDeRecieves;
}


bool ContadorDeJugadores::estaConectado(int jugador) {
	return conectados[jugador];
}


ContadorDeJugadores::~ContadorDeJugadores() {}

