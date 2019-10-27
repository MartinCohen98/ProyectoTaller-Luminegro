#ifndef SRC_VARIOS_GESTORTHREADSSERVIDOR_H_
#define SRC_VARIOS_GESTORTHREADSSERVIDOR_H_

#include "../comunicacion/RecibidorMensajesCliente.h"
#include <pthread.h>

class GestorThreadsServidor {

private:
	int jugadores;
	ColaMensajesCliente* colas;
	Socket** sockets;
	std::thread** threadsRecibidoras;

public:
	GestorThreadsServidor(int cantidadDeJugadores);
	void agregarJugador(Socket* socket, int numero);
	void recibirMensajeDeCliente(MensajeCliente* mensaje, int cliente);
	virtual ~GestorThreadsServidor();
};

#endif /* SRC_VARIOS_GESTORTHREADSSERVIDOR_H_ */
