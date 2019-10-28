#ifndef SRC_VARIOS_GESTORTHREADSSERVIDOR_H_
#define SRC_VARIOS_GESTORTHREADSSERVIDOR_H_

#include "../comunicacion/RecibidorMensajesCliente.h"
#include "../comunicacion/EnviadorMensajesServidor.h"
#include <pthread.h>

class GestorThreadsServidor {

private:
	int jugadores;
	ColaMensajesCliente* colasRecibidoras;
	ColaMensajesServidor* colasEnviadoras;
	Socket** sockets;
	std::thread** threadsRecibidoras;
	std::thread** threadsEnviadoras;

public:
	GestorThreadsServidor(int cantidadDeJugadores);
	void agregarJugador(Socket* socket, int numero);
	void recibirMensajeDeCliente(MensajeCliente* mensaje, int cliente);
	void enviarMensaje(MensajeServidor* mensaje);
	virtual ~GestorThreadsServidor();
};

#endif /* SRC_VARIOS_GESTORTHREADSSERVIDOR_H_ */
