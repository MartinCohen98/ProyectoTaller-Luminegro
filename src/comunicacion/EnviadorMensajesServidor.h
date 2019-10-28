#ifndef SRC_COMUNICACION_ENVIADORMENSAJESSERVIDOR_H_
#define SRC_COMUNICACION_ENVIADORMENSAJESSERVIDOR_H_

#include "Socket.h"
#include "../varios/ColaMensajesServidor.h"
#include <thread>

class EnviadorMensajesServidor {

private:
	Socket* socket;
	ColaMensajesServidor* cola;
	MensajeServidor mensaje;

public:
	EnviadorMensajesServidor(Socket* unSocket, ColaMensajesServidor* unaCola);
	void operator()();
	virtual ~EnviadorMensajesServidor();
};

#endif /* SRC_COMUNICACION_ENVIADORMENSAJESSERVIDOR_H_ */
