#ifndef SRC_COMUNICACION_ENVIADORMENSAJESCLIENTE_H_
#define SRC_COMUNICACION_ENVIADORMENSAJESCLIENTE_H_

#include "Socket.h"
#include "../varios/ColaMensajesCliente.h"
#include <thread>

class EnviadorMensajesCliente {

private:
	ColaMensajesCliente* cola;
	Socket* socket;
	MensajeCliente mensaje;

public:
	EnviadorMensajesCliente(Socket* unSocket, ColaMensajesCliente* unaCola);
	void operator()();
	virtual ~EnviadorMensajesCliente();
};

#endif /* SRC_COMUNICACION_ENVIADORMENSAJESCLIENTE_H_ */
