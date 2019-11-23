#include "InfoJugador.h"

InfoJugador::InfoJugador(int16_t energia, uint8_t vidas, uint32_t puntaje, bool estaConectado) {
    this->energia = energia;
    this->vidas = vidas;
    this->puntaje = puntaje;
    this->conectado = estaConectado;
}

int16_t InfoJugador::getEnergia() {
    return energia;
}

uint8_t InfoJugador::getVidas() {
    return vidas;
}

bool InfoJugador::estaConectado() {
    return conectado;
}

uint32_t InfoJugador::getPuntaje() {
    return puntaje;
}

InfoJugador::InfoJugador(): InfoJugador(0,0,0, false){};


