#ifndef SRC_VARIOS_GESTORTHREADS_H_
#define SRC_VARIOS_GESTORTHREADS_H_

#include "../comunicacion/RecibidorMensajesCliente.h"
#include <pthread.h>

class GestorThreads {

private:
	int jugadores;
	ColaMensajesCliente* colas;
	Socket** sockets;
	std::thread** threadsRecibidoras;

public:
	GestorThreads(int cantidadDeJugadores);
	void agregarJugador(Socket* socket, int numero);
	void recibirMensajeDeCliente(MensajeCliente* mensaje, int cliente);
	virtual ~GestorThreads();
};

#endif /* SRC_VARIOS_GESTORTHREADS_H_ */
