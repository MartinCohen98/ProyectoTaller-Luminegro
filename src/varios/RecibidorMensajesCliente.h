#ifndef SRC_VARIOS_RECIBIDORMENSAJESCLIENTE_H_
#define SRC_VARIOS_RECIBIDORMENSAJESCLIENTE_H_

#include "Cola.h"
#include "Socket.h"
#include "ColaMensajesCliente.h"

class RecibidorMensajesCliente {

private:
	ColaMensajesCliente* cola;
	Socket* socket;
	MensajeCliente mensaje;

public:
	RecibidorMensajesCliente(Socket* unSocket, ColaMensajesCliente* unaCola);
	void operator()();
	virtual ~RecibidorMensajesCliente();
};

#endif /* SRC_VARIOS_RECIBIDORMENSAJESCLIENTE_H_ */
