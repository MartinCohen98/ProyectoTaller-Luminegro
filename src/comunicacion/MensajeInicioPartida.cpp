#include "MensajeInicioPartida.h"
#include <string>
#include <cstring>

int MensajeInicioPartida::getVidaMax() {
    return vidaMax;
}

int MensajeInicioPartida::getNivelInicio() {
    return nivelInicio;
}

MensajeInicioPartida::MensajeInicioPartida(int nivelInicio, int vidaMax) {
    this->nivelInicio = nivelInicio;
    this->vidaMax = vidaMax;
}

void MensajeInicioPartida::setNombreJugador(int numeroJugador, std::string nombre) {
    if(numeroJugador >= 0 && numeroJugador < 4) {
        strcpy(this->jugadores[numeroJugador], nombre.c_str());
    }
}

std::string MensajeInicioPartida::getNombreJugador(int numeroJugador) {
    if(numeroJugador < 1 || numeroJugador > 4)
        return "Error número";
    return jugadores[numeroJugador];
}

MensajeInicioPartida::MensajeInicioPartida() {
    nivelInicio = 1;
    vidaMax = 80;
}






