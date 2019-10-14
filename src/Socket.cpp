#include "Socket.h"

int Socket::servidorInicializar(char* puerto) {
    int resultadoAccion;

    Logger::Log *logueador = Logger::Log::ObtenerInstancia();

    struct addrinfo hints;
    struct addrinfo *ptr;

    numero = 0;
    int val;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;       // IPv4 (or AF_INET6 for IPv6)
    hints.ai_socktype = SOCK_STREAM; // TCP  (or SOCK_DGRAM for UDP)
    hints.ai_flags = AI_PASSIVE;     // AI_PASSIVE for server

    resultadoAccion = getaddrinfo(NULL, puerto, &hints, &ptr);

    if (resultadoAccion != 0) {
        std::string mensajeError = "Clase socket - Error getaddrinfo: ";
        mensajeError.append( gai_strerror(resultadoAccion) );

        logueador->Error(mensajeError);
        return EXIT_FAILURE;
    }

    numero = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

    if (numero == -1) {
        std::string mensajeError = "Clase Socket - Error: ";
        mensajeError.append(strerror(errno));

        logueador->Error(mensajeError);

        freeaddrinfo(ptr);
        return EXIT_FAILURE;
    }

    // Activamos la opción de reusar la dirección en caso de que esta no esté disponible por un TIME_WAIT
    val = 1;
    resultadoAccion = setsockopt(numero, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
    if (resultadoAccion == -1) {
        std::string mensajeError = "Clase Socket - Error: ";
        mensajeError.append(strerror(errno));

        logueador->Error(mensajeError);

        close(numero);
        freeaddrinfo(ptr);
        return EXIT_FAILURE;
    }

    // Decimos en qué dirección local queremos escuchar, en especial el puerto. De otra manera el sistema operativo
    // elegiría un puerto random y el cliente no sabría como conectarse.
    resultadoAccion = bind(numero, ptr->ai_addr, ptr->ai_addrlen);
    if (resultadoAccion == -1) {
        std::string mensajeError = "Clase Socket - Error: ";
        mensajeError.append(strerror(errno));

        logueador->Error(mensajeError);

        close(numero);
        freeaddrinfo(ptr);
        return EXIT_FAILURE;
    }

    freeaddrinfo(ptr);

    // ¿Cuántos clientes podemos mantener en espera antes de poder acceptarlos?
    resultadoAccion = listen(numero, 20);
    if (resultadoAccion == -1) {
        std::string mensajeError = "Clase Socket - Error: ";
        mensajeError.append(strerror(errno));

        logueador->Error(mensajeError);
        close(numero);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}


int Socket::esperarYAceptarCliente(Socket *socketConectado) {
    Logger::Log *logueador = Logger::Log::ObtenerInstancia();
    bool elSocketAceptadoEsValido = true;

    // Aceptamos cliente
    socketConectado->numero = accept(numero, NULL, NULL);

    if (socketConectado->numero == -1) {
        std::string mensajeError = "Clase Socket - Error: ";
        mensajeError.append(strerror(errno));

        logueador->Error(mensajeError);

        elSocketAceptadoEsValido = false;
    }

    if (elSocketAceptadoEsValido) {
        std::string mensajeError = "Clase Socket - Servidor conectado";
        logueador->Info(mensajeError);

    } else {
        std::string mensajeError = "Clase Socket - El socket aceptado no es válido.";
        logueador->Error(mensajeError);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}


int Socket::conectarAUnServidor(char* direccionIP, char* puerto) {
    int resultadoAccion;
    bool estaConectado = false;
    Logger::Log *logueador = Logger::Log::ObtenerInstancia();

    // A qué nos conectaremos
    struct addrinfo hints;
    struct addrinfo *result, *ptr;

    numero = 0;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;       // IPv4 (or AF_INET6 for IPv6)
    hints.ai_socktype = SOCK_STREAM; // TCP  (or SOCK_DGRAM for UDP)
    hints.ai_flags = 0;              // None (or AI_PASSIVE for server)

    resultadoAccion = getaddrinfo(direccionIP, puerto, &hints, &result);

    if (resultadoAccion != 0) {
        std::string mensajeError = "Clase socket - Error getaddrinfo: ";
        mensajeError.append( gai_strerror(resultadoAccion) );

        logueador->Error(mensajeError);
        return -1;
    }

    for (ptr = result; ptr != NULL && !estaConectado; ptr = ptr->ai_next) {
        // Creamos el socket definiendo la familia (deberia ser AF_INET IPv4),
        // el tipo de socket (deberia ser SOCK_STREAM TCP) y el protocolo (0)
        numero = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

        if (numero == -1) {
            std::string mensajeError = "Clase Socket - Error: ";
            mensajeError.append(strerror(errno));

            logueador->Error(mensajeError);
        } else {
            resultadoAccion = connect(numero, ptr->ai_addr, ptr->ai_addrlen);
            if (resultadoAccion == -1) {
                std::string mensajeError = "Clase Socket - Error: ";
                mensajeError.append(strerror(errno));

                logueador->Error(mensajeError);
            } else {
                estaConectado = true;
            }
        }
    }

    freeaddrinfo(result);

    if (estaConectado) {
        logueador->Info("Clase Socket - Cliente conectado.");
    } else {
        logueador->Error("Clase Socket - Error: se queda sin direcciones validas y se desconecta.");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}


int Socket::enviar(int* datos, int* cantidadDeBytes) {
    Logger::Log *logueador = Logger::Log::ObtenerInstancia();

    bool hayUnErrorDeSocket = false;
    bool elSocketRemotoEstaCerrado = false;

    int bytesEnviados = 0;
    int resultadoAccion;

    while (bytesEnviados < *cantidadDeBytes && !hayUnErrorDeSocket && !elSocketRemotoEstaCerrado) {

        resultadoAccion = send(numero, &datos[bytesEnviados], *cantidadDeBytes - bytesEnviados,MSG_NOSIGNAL);

        if (resultadoAccion < 0) {
            std::string mensajeError = "Clase Socket - Error: ";
            mensajeError.append(strerror(errno));

            logueador->Error(mensajeError);

            hayUnErrorDeSocket = true;

        } else if (resultadoAccion == 0) {
            elSocketRemotoEstaCerrado = true;

        } else {
            bytesEnviados += resultadoAccion;
        }
    }

    if (elSocketRemotoEstaCerrado || hayUnErrorDeSocket) {
        cerrar();
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}


int Socket::recibir(unsigned char(*datos), int* tamanoMaximo, bool* elSocketEsValido) {
    Logger::Log *logueador = Logger::Log::ObtenerInstancia();

    int recibido = 0;
    int resultadoAccion = 0;

    while (recibido < *tamanoMaximo && *elSocketEsValido) {
        int bytesCantidadMaximaParaRecibir = *tamanoMaximo - recibido;

        resultadoAccion = recv(numero, &datos[recibido], bytesCantidadMaximaParaRecibir,MSG_NOSIGNAL);

        if (resultadoAccion == 0) {
            // Nos cerraron el socket
            *elSocketEsValido = false;

        } else if (resultadoAccion < 0) {
            // Hubo un error
            logueador->Error("Clase Socket - Error al recibir.");
            return EXIT_FAILURE;
        } else {
            recibido += resultadoAccion;
        }
    }

    return recibido;
}


int Socket::cerrar() {
	if (numero > 0) {
		shutdown(numero, SHUT_RDWR);
		close(numero);
		numero = 0;
	}

	return EXIT_SUCCESS;
}

Socket::~Socket() {
	cerrar();
}
