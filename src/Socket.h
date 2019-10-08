#ifndef PROYECTOTALLER_LUMINEGRO_SOCKET_H
#define PROYECTOTALLER_LUMINEGRO_SOCKET_H

#include "Logger.h"
#include <string>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>


class Socket {
    private:
        int numero;

    public:
        int servidorInicializar(char* puerto);
        int esperarYAceptarCliente(Socket *socketConectado);
        int conectarAUnServidor(char* direccionIP, char* puerto);
        int enviar(unsigned char* datos, int* cantidadDeBytes);
        int recibir(unsigned char* datos, int* tamanoMaximo, bool* elSocketEsValido);
        int cerrar();
};


#endif //PROYECTOTALLER_LUMINEGRO_SOCKET_H
