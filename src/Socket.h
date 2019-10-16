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
#include "MensajeCliente.h"


class Socket {
    private:
        int numero;

    public:
        int servidorInicializar(char* puerto);
        int esperarYAceptarCliente(Socket *socketConectado);
        int conectarAUnServidor(char* direccionIP, char* puerto);
        int enviar(int* datos, int* cantidadDeBytes);
        int enviar(MensajeCliente* mensaje);
        int recibir(unsigned char* datos, int* tamanoMaximo, bool* elSocketEsValido);
        int recibir(MensajeCliente* mensaje);
        int cerrar();
        ~Socket();
};


#endif //PROYECTOTALLER_LUMINEGRO_SOCKET_H
