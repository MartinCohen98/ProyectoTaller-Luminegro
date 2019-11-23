//
// Created by nico on 23/11/19.
//

#ifndef PROYECTOTALLER_LUMINEGRO_INFOJUGADOR_H
#define PROYECTOTALLER_LUMINEGRO_INFOJUGADOR_H


#include <cstdint>

class InfoJugador {
private:
    int16_t energia;
    uint8_t vidas;
    uint32_t puntaje;
    bool conectado;
public:
    InfoJugador();
    InfoJugador(int16_t energia, uint8_t vidas, uint32_t puntaje, bool estaConectado);
    int16_t getEnergia();
    uint8_t getVidas();
    uint32_t getPuntaje();
    bool estaConectado();
};


#endif //PROYECTOTALLER_LUMINEGRO_INFOJUGADOR_H
