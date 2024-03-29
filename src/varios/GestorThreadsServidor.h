#ifndef SRC_VARIOS_GESTORTHREADSSERVIDOR_H_
#define SRC_VARIOS_GESTORTHREADSSERVIDOR_H_

#include "../comunicacion/RecibidorMensajesCliente.h"
#include "../comunicacion/EnviadorMensajesServidor.h"
#include "../comunicacion/AceptadorConexiones.h"
#include "../modelos/Modelo.h"
#include <pthread.h>
#include "../comunicacion/MensajeInicioPartida.h"

class GestorThreadsServidor {

private:
	int jugadores;
	ColaMensajesCliente* colasRecibidoras;
	ColaMensajesServidor* colasEnviadoras;
	Socket** sockets;
	std::thread** threadsRecibidoras;
	std::thread** threadsEnviadoras;
	std::thread* threadAceptador;
	ContadorDeJugadores* contador;

public:
	GestorThreadsServidor(int cantidadDeJugadores);
    void comenzarAAceptar(Socket *socketAceptador, MensajeCredenciales *credenciales,
            int *nivelActual, MensajeInicioPartida *mensaje);
	void agregarJugador(Socket* socket, int numero);
	void recibirMensajeDeCliente(MensajeCliente* mensaje, int cliente);
	void enviarMensaje(MensajeServidor* mensaje);
	void checkearConecciones(int cantidadDeRecieves, Modelo* modelo);
	bool estaConectado(int jugador);
    int enviarMensajeInicioPartida(MensajeInicioPartida *mensajeInicio);

    virtual ~GestorThreadsServidor();


};

#endif /* SRC_VARIOS_GESTORTHREADSSERVIDOR_H_ */
