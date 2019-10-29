#include "RechazadorConexiones.h"


RechazadorConexiones::RechazadorConexiones(Socket* unSocket) {
    socketAceptador = unSocket;
}


void RechazadorConexiones::operator()() {
    int estado = 0;
    MensajeCredenciales mensajeCredenciales;
    Logger::Log *logueador = Logger::Log::ObtenerInstancia();

    while (estado == 0) {
        int resultadoAccion = socketAceptador->esperarYAceptarCliente(socketDeCliente);
        if (resultadoAccion == EXIT_FAILURE) {
            // Ya fue logueado en la clase
            socketAceptador->cerrar();
            estado = 1;
            break;
        }

        // Se le avisa que no hay cupo disponible para que se conecte el jugador
        mensajeCredenciales.setEstado(MensajeCredenciales::ESTADO_NO_MAS_JUGADORES_PERMITIDOS);
        resultadoAccion = socketDeCliente->enviar(&mensajeCredenciales);
        if (resultadoAccion == EXIT_FAILURE) {
            // Ya fue logueado en la clase
            socketAceptador->cerrar();
            estado = 1;
            break;
        }

        logueador->Info("Se rechazó una conexión por no haberse alcanzado el máximo de jugadores.");
    }
}
