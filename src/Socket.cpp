#include <string>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include "Socket.h"
#include "Logger.h"

Socket::Socket() {

}


int Socket::esperarYAceptarCliente(char* puerto, Socket *socketConectado) {
    int result;
    bool elSocketAceptadoEsValido = true;
    Logger::Log *logueador = Logger::Log::ObtenerInstancia();

    struct addrinfo hints;
    struct addrinfo *ptr;

    numero = 0;
    int val;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;       // IPv4 (or AF_INET6 for IPv6)
    hints.ai_socktype = SOCK_STREAM; // TCP  (or SOCK_DGRAM for UDP)
    hints.ai_flags = AI_PASSIVE;     // AI_PASSIVE for server

    result = getaddrinfo(NULL, puerto, &hints, &ptr);

    if (result != 0) {
        std::string mensajeError = "Clase socket - Error getaddrinfo: ";
        mensajeError.append( gai_strerror(result) );

        logueador->Error(mensajeError);
        return 1;
    }

    numero = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

    if (numero == -1) {
        std::string mensajeError = "Clase Socket - Error: ";
        mensajeError.append(strerror(errno));

        logueador->Error(mensajeError);

        freeaddrinfo(ptr);
        return 1;
    }

    // Activamos la opción de reusar la dirección en caso de que esta no esté disponible por un TIME_WAIT
    val = 1;
    result = setsockopt(numero, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
    if (result == -1) {
        std::string mensajeError = "Clase Socket - Error: ";
        mensajeError.append(strerror(errno));

        logueador->Error(mensajeError);

        close(numero);
        freeaddrinfo(ptr);
        return 1;
    }

    // Decimos en qué dirección local queremos escuchar, en especial el puerto. De otra manera el sistema operativo
    // elegiría un puerto random y el cliente no sabría como conectarse.
    result = bind(numero, ptr->ai_addr, ptr->ai_addrlen);
    if (result == -1) {
        std::string mensajeError = "Clase Socket - Error: ";
        mensajeError.append(strerror(errno));

        logueador->Error(mensajeError);

        close(numero);
        freeaddrinfo(ptr);
        return 1;
    }

    freeaddrinfo(ptr);

    // ¿Cuántos clientes podemos mantener en espera antes de poder acceptarlos?
    result = listen(numero, 20);
    if (result == -1) {
        std::string mensajeError = "Clase Socket - Error: ";
        mensajeError.append(strerror(errno));

        logueador->Error(mensajeError);
        close(numero);
        return 1;
    }

    // Aceptamos cliente
    socketConectado->numero = accept(numero, NULL, NULL);

    if (socketConectado->numero == -1) {
        std::string mensajeError = "Clase Socket - Error: ";
        mensajeError.append(strerror(errno));

        logueador->Error(mensajeError);

        elSocketAceptadoEsValido = false;
    }

    if (elSocketAceptadoEsValido) {
        return 0;
    } else {
        std::string mensajeError = "Clase Socket - El socket aceptado no es válido.";
        logueador->Error(mensajeError);
        return 1;
    }
}