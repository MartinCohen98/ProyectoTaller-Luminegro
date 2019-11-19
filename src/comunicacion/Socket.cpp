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

    estado = ESTADO_ESCUCHANDO;

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
        std::string mensajeError = "Clase Socket - Se conecto un cliente al servidor";
        logueador->Info(mensajeError);

    } else {
        std::string mensajeError = "Clase Socket - El socket aceptado no es válido.";
        logueador->Error(mensajeError);
        return EXIT_FAILURE;
    }

    int timeout = 4000;  // timeout en millisegundos [ms]
    setsockopt(socketConectado->obtenerNumero(),
    			SOL_TCP, TCP_USER_TIMEOUT, (char*) &timeout, sizeof (timeout));

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

            // Si el cliente se desconecta (por ejemplo físicamente) el receive no debe esperar hasta el infinito
            struct timeval tv;
            tv.tv_sec = 4;
            tv.tv_usec = 0;
            setsockopt(numero, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);

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

    int timeout = 4000;  // timeout en millisegundos [ms]
    setsockopt(numero, SOL_TCP, TCP_USER_TIMEOUT, (char*) &timeout, sizeof (timeout));

    return EXIT_SUCCESS;
}


int Socket::enviar(MensajeCredenciales* mensaje) {
    Logger::Log *logueador = Logger::Log::ObtenerInstancia();

    bool hayUnErrorDeSocket = false;
    bool elSocketRemotoEstaCerrado = false;

    char* datos = (char*) mensaje;
    int bytesEnviados = 0;
    int cantidadDeBytes = sizeof(MensajeCredenciales);
    int resultadoAccion;

    while (bytesEnviados < cantidadDeBytes && !hayUnErrorDeSocket && !elSocketRemotoEstaCerrado) {

        resultadoAccion = send(numero, &datos[bytesEnviados], cantidadDeBytes - bytesEnviados,MSG_NOSIGNAL);

        if (resultadoAccion < 0) {
            if (errno == ERROR_SOCKET_OPERATION_ON_NO_SOCKET) {
                elSocketRemotoEstaCerrado = true;
            }

            std::string mensajeError = "Clase Socket - Método enviar(MensajeCredenciales* mensaje) - Error en send(): ";
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
        estado = ESTADO_DESCONECTADO;
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


        seguirEnviando = true;
        // Esto previene que se desconecte por timeout antes de arrancar el juego mientras se espera otros jugadores
        while (seguirEnviando) {
            resultadoAccion = send(numero, &datos[bytesEnviados], cantidadDeBytes - bytesEnviados,MSG_NOSIGNAL);
            seguirEnviando = (resultadoAccion < 0 && !arrancoElJuego);
        }
        arrancoElJuego = true;

        if (resultadoAccion < 0) {
            if (errno == ERROR_SOCKET_OPERATION_ON_NO_SOCKET) {
                elSocketRemotoEstaCerrado = true;
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
    	estado = ESTADO_DESCONECTADO;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}


int Socket::enviar(MensajeServidor* mensajes) {
	Logger::Log *logueador = Logger::Log::ObtenerInstancia();

    bool hayUnErrorDeSocket = false;
    bool elSocketRemotoEstaCerrado = false;

    char* datos = (char*) mensajes;
    int bytesEnviados = 0;
    int cantidadDeBytes = sizeof(MensajeServidor);
    int resultadoAccion;

    while (bytesEnviados < cantidadDeBytes && !hayUnErrorDeSocket && !elSocketRemotoEstaCerrado) {

        resultadoAccion = send(numero, &datos[bytesEnviados], cantidadDeBytes - bytesEnviados,MSG_NOSIGNAL);

        if (resultadoAccion < 0) {
            hayUnErrorDeSocket = true;

            if (errno == ERROR_SOCKET_OPERATION_ON_NO_SOCKET) {
                elSocketRemotoEstaCerrado = true;
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
    	estado = ESTADO_DESCONECTADO;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}


int Socket::recibir(MensajeCredenciales *mensaje) {
    Logger::Log *logueador = Logger::Log::ObtenerInstancia();

    int recibido = 0;
    int resultadoAccion = 0;
    int tamanoMaximo = sizeof(MensajeCredenciales);
    char* datos = (char*) mensaje;

    while (recibido < tamanoMaximo) {
        int bytesCantidadMaximaParaRecibir = tamanoMaximo - recibido;

        seguirRecibiendo = true;
        // Esto previene que se desconecte por timeout antes de arrancar el juego mientras se espera otros jugadores
        while (seguirRecibiendo) {
            resultadoAccion = recv(numero, &datos[recibido], bytesCantidadMaximaParaRecibir,MSG_NOSIGNAL);
            seguirRecibiendo = (resultadoAccion < 0 && !arrancoElJuego);
        }

        if (resultadoAccion == 0) {
            // Nos cerraron el socket
        	estado = ESTADO_DESCONECTADO;
            return EXIT_FAILURE;

        } else if (resultadoAccion < 0) {
            // Hubo un error

            std::string mensajeError = "Clase Socket - Método recibir(MensajeCredenciales* mensaje) - Error en recv(): ";
            mensajeError.append(strerror(errno));

            logueador->Error(mensajeError);
            estado = ESTADO_DESCONECTADO;
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
        	estado = ESTADO_DESCONECTADO;
            return EXIT_FAILURE;

        } else if (resultadoAccion < 0) {
            // Hubo un error
            std::string mensajeError = "Clase Socket - Método recibir(MensajeCliente* mensaje) - Error en recv(): ";
            mensajeError.append(strerror(errno));

            logueador->Error(mensajeError);
            estado = ESTADO_DESCONECTADO;
            return EXIT_FAILURE;
        } else {
            recibido += resultadoAccion;
        }
    }
    return recibido;
}


int Socket::recibir(MensajeServidor* mensaje) {
	Logger::Log *logueador = Logger::Log::ObtenerInstancia();

    int recibido = 0;
    int resultadoAccion = 0;
    int tamanoMaximo = sizeof(MensajeServidor);
    char* datos = (char*) mensaje;

    while (recibido < tamanoMaximo) {
        int bytesCantidadMaximaParaRecibir = tamanoMaximo - recibido;

        seguirRecibiendo = true;
        // Esto previene que se desconecte por timeout antes de arrancar el juego mientras se espera otros jugadores
        while (seguirRecibiendo) {
            resultadoAccion = recv(numero, &datos[recibido], bytesCantidadMaximaParaRecibir,MSG_NOSIGNAL);
            seguirRecibiendo = (resultadoAccion < 0 && !arrancoElJuego);
        }
        arrancoElJuego = true;

        if (resultadoAccion == 0) {
            // Nos cerraron el sock et
        	estado = ESTADO_DESCONECTADO;
            return EXIT_FAILURE;

        } else if (resultadoAccion < 0) {
            // Hubo un error
            std::string mensajeError = "Clase Socket - Método recibir(MensajeServidor* mensaje) - Error en recv(): ";
            mensajeError.append(strerror(errno));
            logueador->Error(mensajeError);
            logueador->Info("CERRANDO JUEGO DE CLIENTE POR DESCONEXIÓN");
            estado = ESTADO_DESCONECTADO;
            return EXIT_FAILURE;
        } else {
            recibido += resultadoAccion;
        }
    }
    return recibido;
}

int Socket::recibir(char *mensaje, int tamanio) {
    Logger::Log *logueador = Logger::Log::ObtenerInstancia();

    int recibido = 0;
    int resultadoAccion = 0;
    int tamanoMaximo = tamanio;
    char* datos = mensaje;

    while (recibido < tamanoMaximo) {
        int bytesCantidadMaximaParaRecibir = tamanoMaximo - recibido;

        seguirRecibiendo = true;
        // Esto previene que se desconecte por timeout antes de arrancar el juego mientras se espera otros jugadores
        while (seguirRecibiendo) {
            resultadoAccion = recv(numero, &datos[recibido], bytesCantidadMaximaParaRecibir,MSG_NOSIGNAL);
            seguirRecibiendo = (resultadoAccion < 0 && !arrancoElJuego);
        }

        if (resultadoAccion == 0) {
            // Nos cerraron el socket
            estado = ESTADO_DESCONECTADO;
            return EXIT_FAILURE;

        } else if (resultadoAccion < 0) {
            // Hubo un error

            std::string mensajeError = "Clase Socket - Método recibir genérico - Error en recv(): ";
            mensajeError.append(strerror(errno));

            logueador->Error(mensajeError);
            estado = ESTADO_DESCONECTADO;
            return EXIT_FAILURE;
        } else {
            recibido += resultadoAccion;
        }
    }
    return recibido;
}

int Socket::enviar(char *mensaje, int tamanio){
    Logger::Log *logueador = Logger::Log::ObtenerInstancia();

    bool hayUnErrorDeSocket = false;
    bool elSocketRemotoEstaCerrado = false;

    char* datos = mensaje;
    int bytesEnviados = 0;
    int cantidadDeBytes = tamanio;
    int resultadoAccion;

    while (bytesEnviados < cantidadDeBytes && !hayUnErrorDeSocket && !elSocketRemotoEstaCerrado) {

        resultadoAccion = send(numero, &datos[bytesEnviados], cantidadDeBytes - bytesEnviados,MSG_NOSIGNAL);

        if (resultadoAccion < 0) {
            hayUnErrorDeSocket = true;

            if (errno == ERROR_SOCKET_OPERATION_ON_NO_SOCKET) {
                elSocketRemotoEstaCerrado = true;
            }

            std::string mensajeError = "Clase Socket - Método enviar genérico - Error en send(): ";
            mensajeError.append(strerror(errno));
            logueador->Error(mensajeError);

        } else if (resultadoAccion == 0) {
            elSocketRemotoEstaCerrado = true;

        } else {
            bytesEnviados += resultadoAccion;
        }
    }
    if (elSocketRemotoEstaCerrado || hayUnErrorDeSocket) {
        estado = ESTADO_DESCONECTADO;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}


int Socket::getEstado() {
    return estado;
}


void Socket::asignarNumero(int unNumero) {
	numero = unNumero;
	estado = ESTADO_CONECTADO;
}


int Socket::obtenerNumero() {
	return numero;
}


int Socket::cerrar() {
	if (numero > 0) {
		shutdown(numero, SHUT_RDWR);
		close(numero);
		numero = 0;
	}
	estado = ESTADO_DISPONIBLE;
	return EXIT_SUCCESS;
}

Socket::~Socket() {
	cerrar();
}


