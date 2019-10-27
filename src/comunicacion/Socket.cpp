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
        std::string mensajeError = "Clase socket - Método servidorInicializar - Error en getaddrinfo(): ";
        mensajeError.append( gai_strerror(resultadoAccion) );

        logueador->Error(mensajeError);
        return EXIT_FAILURE;
    }

    numero = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

    if (numero == -1) {
        std::string mensajeError = "Clase Socket - Método servidorInicializar - Error en socket(): ";
        mensajeError.append(strerror(errno));

        logueador->Error(mensajeError);

        freeaddrinfo(ptr);
        return EXIT_FAILURE;
    }

    // Activamos la opción de reusar la dirección en caso de que esta no esté disponible por un TIME_WAIT
    val = 1;
    resultadoAccion = setsockopt(numero, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
    if (resultadoAccion == -1) {
        std::string mensajeError = "Clase Socket - Método servidorInicializar - Error en setsockopt(): ";
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
        std::string mensajeError = "Clase Socket - Método servidorInicializar - Error en bind(): ";
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
        std::string mensajeError = "Clase Socket - Método servidorInicializar - Error en listen(): ";
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
        std::string mensajeError = "Clase Socket - Método esperarYAceptarCliente - Error en accept(): ";
        mensajeError.append(strerror(errno));

        logueador->Error(mensajeError);

        elSocketAceptadoEsValido = false;
    }

    if (elSocketAceptadoEsValido) {
        socketConectado->estado = ESTADO_CONECTADO;
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
        std::string mensajeError = "Clase Socket - Método conectarAUnServidor - Error en getaddrinfo(): ";
        mensajeError.append( gai_strerror(resultadoAccion) );

        logueador->Error(mensajeError);
        return -1;
    }

    for (ptr = result; ptr != NULL && !estaConectado; ptr = ptr->ai_next) {
        // Creamos el socket definiendo la familia (deberia ser AF_INET IPv4),
        // el tipo de socket (deberia ser SOCK_STREAM TCP) y el protocolo (0)
        numero = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

        if (numero == -1) {
            std::string mensajeError = "Clase Socket - Método conectarAUnServidor - Error en socket(): ";
            mensajeError.append(strerror(errno));

            logueador->Error(mensajeError);
        } else {
            resultadoAccion = connect(numero, ptr->ai_addr, ptr->ai_addrlen);
            if (resultadoAccion == -1) {
                std::string mensajeError = "Clase Socket - Método conectarAUnServidor - Error en connect(): ";
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
        estado = ESTADO_CONECTADO;
    } else {
        std::string error = "Clase Socket - Método conectarAUnServidor - se queda sin direcciones validas";
        error.append(" y se desconecta.");
        logueador->Error(error);
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
            std::string mensajeError = "Clase Socket - Método enviar(int* datos ...) - Error en send(): ";
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


int Socket::enviar(MensajeCliente* mensaje) {
	Logger::Log *logueador = Logger::Log::ObtenerInstancia();

    bool hayUnErrorDeSocket = false;
    bool elSocketRemotoEstaCerrado = false;

    char* datos = (char*) mensaje;
    int bytesEnviados = 0;
    int cantidadDeBytes = sizeof(MensajeCliente);
    int resultadoAccion;

    while (bytesEnviados < cantidadDeBytes && !hayUnErrorDeSocket && !elSocketRemotoEstaCerrado) {

        resultadoAccion = send(numero, &datos[bytesEnviados], cantidadDeBytes - bytesEnviados,MSG_NOSIGNAL);

        if (resultadoAccion < 0) {
            if (errno == ERROR_SOCKET_OPERATION_ON_NO_SOCKET) {
                elSocketRemotoEstaCerrado = true;
                estado = ESTADO_DESCONECTADO;
            }

            std::string mensajeError = "Clase Socket - Método enviar(MensajeCliente* mensaje) - Error en send(): ";
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


int Socket::enviar(MensajeServidor* mensajes, int cantidad) {
	Logger::Log *logueador = Logger::Log::ObtenerInstancia();

    bool hayUnErrorDeSocket = false;
    bool elSocketRemotoEstaCerrado = false;

    char* datos = (char*) mensajes;
    int bytesEnviados = 0;
    int cantidadDeBytes = (sizeof(MensajeServidor) * cantidad);
    int resultadoAccion;

    while (bytesEnviados < cantidadDeBytes && !hayUnErrorDeSocket && !elSocketRemotoEstaCerrado) {

        resultadoAccion = send(numero, &datos[bytesEnviados], cantidadDeBytes - bytesEnviados,MSG_NOSIGNAL);

        if (resultadoAccion < 0) {
            hayUnErrorDeSocket = true;

            if (errno == ERROR_SOCKET_OPERATION_ON_NO_SOCKET) {
                elSocketRemotoEstaCerrado = true;
                estado = ESTADO_DESCONECTADO;
            }

            std::string mensajeError = "Clase Socket - Método enviar(MensajeServidor* mensaje) - Error en send(): ";
            mensajeError.append(strerror(errno));
            logueador->Error(mensajeError);

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

int Socket::enviar(int unNumero) {
	Logger::Log *logueador = Logger::Log::ObtenerInstancia();

    bool hayUnErrorDeSocket = false;
    bool elSocketRemotoEstaCerrado = false;

    char* datos = (char*) &unNumero;
    int bytesEnviados = 0;
    int cantidadDeBytes = sizeof(int);
    int resultadoAccion;

    while (bytesEnviados < cantidadDeBytes && !hayUnErrorDeSocket && !elSocketRemotoEstaCerrado) {

        resultadoAccion = send(numero, &datos[bytesEnviados], cantidadDeBytes - bytesEnviados,MSG_NOSIGNAL);

        if (resultadoAccion < 0) {
            std::string mensajeError = "Clase Socket - Método enviar(int unNumero) - Error en send(): ";
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
            std::string error = "Clase Socket - Método recibir(unsigned char(*datos), ...) - Error en recv()";
            logueador->Error(error);
            return EXIT_FAILURE;
        } else {
            recibido += resultadoAccion;
        }
    }
    return recibido;
}


int Socket::recibir(MensajeCliente* mensaje) {
    Logger::Log *logueador = Logger::Log::ObtenerInstancia();

    int recibido = 0;
    int resultadoAccion = 0;
    int tamanoMaximo = sizeof(MensajeCliente);
    char* datos = (char*) mensaje;

    while (recibido < tamanoMaximo) {
        int bytesCantidadMaximaParaRecibir = tamanoMaximo - recibido;

        resultadoAccion = recv(numero, &datos[recibido], bytesCantidadMaximaParaRecibir,MSG_NOSIGNAL);

        if (resultadoAccion == 0) {
            // Nos cerraron el socket
            return EXIT_FAILURE;

        } else if (resultadoAccion < 0) {
            // Hubo un error
            if (errno == ERROR_SOCKET_OPERATION_ON_NO_SOCKET) {
                estado = ESTADO_DESCONECTADO;
            }

            std::string mensajeError = "Clase Socket - Método recibir(MensajeCliente* mensaje) - Error en recv(): ";
            mensajeError.append(strerror(errno));

            logueador->Error(mensajeError);
            return EXIT_FAILURE;
        } else {
            recibido += resultadoAccion;
        }
    }
    return recibido;
}


int Socket::recibir(MensajeServidor* mensaje, int cantidad) {
    Logger::Log *logueador = Logger::Log::ObtenerInstancia();

    int recibido = 0;
    int resultadoAccion = 0;
    int tamanoMaximo = sizeof(MensajeServidor) * cantidad;
    char* datos = (char*) mensaje;

    while (recibido < tamanoMaximo) {
        int bytesCantidadMaximaParaRecibir = tamanoMaximo - recibido;

        resultadoAccion = recv(numero, &datos[recibido], bytesCantidadMaximaParaRecibir,MSG_NOSIGNAL);

        if (resultadoAccion == 0) {
            // Nos cerraron el socket
            return EXIT_FAILURE;

        } else if (resultadoAccion < 0) {
            // Hubo un error
            std::string mensajeError = "Clase Socket - Método recibir(MensajeServidor* mensaje) - Error en recv(): ";
            mensajeError.append(strerror(errno));
            logueador->Error(mensajeError);
            return EXIT_FAILURE;
        } else {
            recibido += resultadoAccion;
        }
    }
    return recibido;
}


int Socket::recibir(int* unNumero) {
    Logger::Log *logueador = Logger::Log::ObtenerInstancia();

    int recibido = 0;
    int resultadoAccion = 0;
    int tamanoMaximo = sizeof(int);
    char* datos = (char*) unNumero;

    while (recibido < tamanoMaximo) {
        int bytesCantidadMaximaParaRecibir = tamanoMaximo - recibido;

        resultadoAccion = recv(numero, &datos[recibido], bytesCantidadMaximaParaRecibir,MSG_NOSIGNAL);

        if (resultadoAccion == 0) {
            // Nos cerraron el socket
            return EXIT_FAILURE;

        } else if (resultadoAccion < 0) {
            // Hubo un error
            logueador->Error("Clase Socket - Método recibir(int* unNumero) - Error en recv()");
            return EXIT_FAILURE;
        } else {
            recibido += resultadoAccion;
        }
    }
    return recibido;
}


int Socket::getEstado() {
    return estado;
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
