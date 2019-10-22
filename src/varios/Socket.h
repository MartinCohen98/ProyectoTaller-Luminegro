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
#include "MensajeServidor.h"


class Socket {
    private:
        int numero;
        int estado = ESTADO_DESCONECTADO;

    public:
        static const int ESTADO_CONECTADO = 1;
        static const int ESTADO_DESCONECTADO = 2;

        static const int ERROR_SOCKET_BROKEN_PIPE = 32;
        static const int ERROR_SOCKET_OPERATION_ON_NO_SOCKET = 88;

        int servidorInicializar(char* puerto);
        int esperarYAceptarCliente(Socket *socketConectado);
        int conectarAUnServidor(char* direccionIP, char* puerto);
        int enviar(int* datos, int* cantidadDeBytes);
        int enviar(MensajeCliente* mensaje);
        int enviar(MensajeServidor* mensajes, int cantidad);
        int enviar(int unNumero);
        int recibir(unsigned char* datos, int* tamanoMaximo, bool* elSocketEsValido);
        int recibir(MensajeCliente* mensaje);
        int recibir(MensajeServidor* mensaje, int cantidad);
        int recibir(int* unNumero);
        int getEstado();
        int cerrar();
        ~Socket();
};


#endif //PROYECTOTALLER_LUMINEGRO_SOCKET_H