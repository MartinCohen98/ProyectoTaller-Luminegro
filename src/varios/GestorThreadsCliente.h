#ifndef SRC_VARIOS_GESTORTHREADSCLIENTE_H_
#define SRC_VARIOS_GESTORTHREADSCLIENTE_H_

#include <pthread.h>
#include "../comunicacion/EnviadorMensajesCliente.h"
#include "../comunicacion/RecibidorMensajesServidor.h"
#include "../comunicacion/MensajeInicioPartida.h"

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
	bool seDesconecto();
	void enviarMensaje(MensajeCliente* mensaje);
	MensajeServidor recibirMensaje();
	MensajeInicioPartida recibirMensajeDeInicio();
	virtual ~GestorThreadsCliente();
};

#endif /* SRC_VARIOS_GESTORTHREADSCLIENTE_H_ */
