#ifndef PROYECTOTALLER_LUMINEGRO_SOCKET_H
#define PROYECTOTALLER_LUMINEGRO_SOCKET_H

#include "../varios/Logger.h"
#include <string>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>
#include "MensajeCliente.h"
#include "MensajeServidor.h"
#include "MensajeCredenciales.h"

#ifndef SOL_TCP
    #define SOL_TCP 6  // socket options TCP level
#endif
#ifndef TCP_USER_TIMEOUT
    #define TCP_USER_TIMEOUT 18  // how long for loss retry before timeout [ms]
#endif


class Socket {
private:
    int numero;
    int estado = ESTADO_DISPONIBLE;
    bool arrancoElJuego = false;
    bool seguirRecibiendo = true;
    bool seguirEnviando = true;

public:
    static const int ESTADO_CONECTADO = 1;
    static const int ESTADO_DESCONECTADO = 2;
    static const int ESTADO_DISPONIBLE = 3;
    static const int ESTADO_ESCUCHANDO = 4;

    static const int ERROR_SOCKET_BROKEN_PIPE = 32;
    static const int ERROR_SOCKET_OPERATION_ON_NO_SOCKET = 88;

    int servidorInicializar(char* puerto);
    int esperarYAceptarCliente(Socket *socketConectado);
    int conectarAUnServidor(char* direccionIP, char* puerto);
    int enviar(MensajeCredenciales *mensaje);
    int enviar(MensajeCliente* mensaje);
    int enviar(MensajeServidor* mensajes);
    int recibir(MensajeCredenciales *mensaje);
    int recibir(MensajeCliente* mensaje);
    int recibir(MensajeServidor* mensaje);
    int getEstado();
    void asignarNumero(int unNumero);
    int obtenerNumero();
    int cerrar();
    ~Socket();
};


#endif //PROYECTOTALLER_LUMINEGRO_SOCKET_H
