#ifndef SRC_VARIOS_GESTORTHREADS_H_
#define SRC_VARIOS_GESTORTHREADS_H_

#include "RecibidorMensajesCliente.h"

class GestorThreads {

private:
	int jugadores;
	ColaMensajesCliente* colas;
	Socket** sockets;
	std::thread** threadsRecibidoras;

public:
	GestorThreads(int cantidadDeJugadores);
	void agregarJugador(Socket* socket, int numero);
	virtual ~GestorThreads();
};

#endif /* SRC_VARIOS_GESTORTHREADS_H_ */
