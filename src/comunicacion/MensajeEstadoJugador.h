#ifndef PROYECTOTALLER_LUMINEGRO_MENSAJEESTADOJUGADOR_H
#define PROYECTOTALLER_LUMINEGRO_MENSAJEESTADOJUGADOR_H


#include <stdint-gcc.h>

class MensajeEstadoJugador {
public:
    uint8_t numeroJugador; //0 a 3
    uint8_t vidas;
    int16_t energia;
    bool conectado;
    uint32_t puntaje;
    MensajeEstadoJugador();
};



#endif //PROYECTOTALLER_LUMINEGRO_MENSAJEESTADOJUGADOR_H
