#ifndef PROYECTOTALLER_LUMINEGRO_SOCKET_H
#define PROYECTOTALLER_LUMINEGRO_SOCKET_H

#include "Logger.h"
#include <string>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>


class Socket {
    private:
        int numero;
    public:
        Socket();
        int esperarYAceptarCliente(char* puerto, Socket *socketConectado);
        int conectarConServidor(char* direccionIP, char* puerto);
};


#endif //PROYECTOTALLER_LUMINEGRO_SOCKET_H
