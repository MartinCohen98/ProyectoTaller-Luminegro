#ifndef SRC_COMUNICACION_RECIBIDORMENSAJESSERVIDOR_H_
#define SRC_COMUNICACION_RECIBIDORMENSAJESSERVIDOR_H_

#include "Socket.h"
#include "../varios/ColaMensajesServidor.h"

class RecibidorMensajesServidor {

private:
	ColaMensajesServidor* cola;
	Socket* socket;
	MensajeServidor mensaje;

public:
	RecibidorMensajesServidor(Socket* unSocket, ColaMensajesServidor* unaCola);
	void operator()();
	virtual ~RecibidorMensajesServidor();
};

#endif /* SRC_COMUNICACION_RECIBIDORMENSAJESSERVIDOR_H_ */
