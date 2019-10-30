#ifndef PROYECTOTALLER_LUMINEGRO_RECHAZADORCONEXIONES_H
#define PROYECTOTALLER_LUMINEGRO_RECHAZADORCONEXIONES_H

#include "Socket.h"
#include "../varios/ContadorDeJugadores.h"
#include <thread>

// Rechaza las conexiones cuando el máximo de jugadores ya se conectó
class AceptadorConexiones {

private:
    Socket* socketAceptador;
    ContadorDeJugadores* contador;

public:
    AceptadorConexiones(Socket* unSocket, ContadorDeJugadores* unContador);
    void operator()();
};


#endif //PROYECTOTALLER_LUMINEGRO_RECHAZADORCONEXIONES_H