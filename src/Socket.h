#ifndef PROYECTOTALLER_LUMINEGRO_SOCKET_H
#define PROYECTOTALLER_LUMINEGRO_SOCKET_H

#include "Logger.h"


class Socket {
    private:
        int numero;
    public:
        Socket();
        int esperarYAceptarCliente(char* puerto, Socket *socketConectado);
};


#endif //PROYECTOTALLER_LUMINEGRO_SOCKET_H
