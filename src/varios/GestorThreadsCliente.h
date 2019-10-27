#ifndef SRC_VARIOS_GESTORTHREADSCLIENTE_H_
#define SRC_VARIOS_GESTORTHREADSCLIENTE_H_

#include <pthread.h>
#include "../comunicacion/EnviadorMensajesCliente.h"

class GestorThreadsCliente {

private:
	Socket* socket;
	ColaMensajesCliente colaCliente;
	std::thread* threadEnviadora;

public:
	GestorThreadsCliente(Socket* unSocket);
	void comenzarAEnviar();
	void enviarMensaje(MensajeCliente* mensaje);
	virtual ~GestorThreadsCliente();
};

#endif /* SRC_VARIOS_GESTORTHREADSCLIENTE_H_ */
