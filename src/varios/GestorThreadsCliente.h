#ifndef SRC_VARIOS_GESTORTHREADSCLIENTE_H_
#define SRC_VARIOS_GESTORTHREADSCLIENTE_H_

#include <pthread.h>
#include "../comunicacion/EnviadorMensajesCliente.h"
#include "../comunicacion/RecibidorMensajesServidor.h"

class GestorThreadsCliente {

private:
	Socket* socket;
	ColaMensajesCliente colaCliente;
	ColaMensajesServidor colaServidor;
	std::thread* threadEnviadora;
	std::thread* threadRecibidora;

public:
	GestorThreadsCliente(Socket* unSocket);
	void comenzar();
	void enviarMensaje(MensajeCliente* mensaje);
	MensajeServidor recibirMensaje();
	virtual ~GestorThreadsCliente();
};

#endif /* SRC_VARIOS_GESTORTHREADSCLIENTE_H_ */
