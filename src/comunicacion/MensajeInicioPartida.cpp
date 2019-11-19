#include "MensajeInicioPartida.h"
#include <string>
#include <cstring>

int MensajeInicioPartida::getVidaMax() {
    return vidaMax;
}

int MensajeInicioPartida::getNivelInicial() {
    return nivelInicio;
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

void MensajeInicioPartida::setNivelInicial(int nivel) {
    nivelInicio = nivel;
}

void MensajeInicioPartida::setVidaMax(int vidaMaxima) {
    vidaMax = vidaMaxima;
}






