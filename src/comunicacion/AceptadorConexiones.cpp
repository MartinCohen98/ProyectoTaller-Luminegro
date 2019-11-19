#include "AceptadorConexiones.h"

AceptadorConexiones::AceptadorConexiones(Socket* unSocket, ContadorDeJugadores* unContador,
                                        int *nivelActual, MensajeInicioPartida* mensaje) {
    socketAceptador = unSocket;
    contador = unContador;
    nroNivel = nivelActual;
    this->mensajeInicio = mensaje;
}


void AceptadorConexiones::operator()() {
    MensajeCredenciales mensajeCredenciales;
    Logger::Log *logueador = Logger::Log::ObtenerInstancia();
    Socket socketDeCliente;

    while (socketAceptador->getEstado() == Socket::ESTADO_ESCUCHANDO) {
        int resultadoAccion = socketAceptador->esperarYAceptarCliente(&socketDeCliente);

        if (resultadoAccion == EXIT_FAILURE) {
            // Ya fue logueado en la clase
            socketAceptador->cerrar();
            break;
        }

        if (!contador->hayEspacioDisponible()) {
        	// Se le avisa que no hay cupo disponible para que se conecte el jugador
        	mensajeCredenciales.setEstado(MensajeCredenciales::ESTADO_NO_MAS_JUGADORES_PERMITIDOS);
        	resultadoAccion = socketDeCliente.enviar(&mensajeCredenciales);

        	logueador->Info("Se rechazó una conexión por haberse alcanzado el máximo de jugadores.");

        } else {
        	mensajeCredenciales.setEstado(MensajeCredenciales::ESTADO_ESPERANDO_CONEXIONES);
        	socketDeCliente.enviar(&mensajeCredenciales);

        	while (mensajeCredenciales.getEstado() != MensajeCredenciales::ESTADO_AUTENTICADO) {
        		socketDeCliente.recibir(&mensajeCredenciales);
        	    contador->validarCredenciales(&mensajeCredenciales, &socketDeCliente, nroNivel);
        	}
        	socketDeCliente.enviar((char *) mensajeInicio, sizeof(MensajeInicioPartida));
        }
    }
}
