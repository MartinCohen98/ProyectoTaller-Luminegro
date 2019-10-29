#ifndef PROYECTOTALLER_LUMINEGRO_RECHAZADORCONEXIONES_H
#define PROYECTOTALLER_LUMINEGRO_RECHAZADORCONEXIONES_H

#include "Socket.h"
#include "../varios/ColaMensajesCliente.h"
#include <thread>

// Rechaza las conexiones cuando el máximo de jugadores ya se conectó
class RechazadorConexiones {

private:
    Socket* socketAceptador;
    Socket* socketDeCliente;

public:
    RechazadorConexiones(Socket* unSocket);
    void operator()();
};


#endif //PROYECTOTALLER_LUMINEGRO_RECHAZADORCONEXIONES_H
