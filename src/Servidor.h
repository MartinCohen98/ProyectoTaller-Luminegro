#ifndef SRC_SERVIDOR_H_
#define SRC_SERVIDOR_H_

#include "Socket.h"
#include "JugadorModelo.h"
#include "ControlEnemigosModelo.h"
#include "ControlObjetosModelo.h"
#include "MensajeCliente.h"

class Servidor {

private:
	int jugadores;
	MensajeCliente mensajeCliente;
	MensajeServidor mensajeServidor;
	Socket socketAceptador;
	Socket* socketsDeClientes;

public:
	Servidor(int cantidadDeJugadores, char* puerto);
	void correr(pugi::xml_document* archiConfig);

	virtual ~Servidor();

private:
	void recibirInput(JugadorModelo* jugador);
	void enviarCantidadDeReceives(ControlEnemigosModelo* enemigos,
							ControlObjetosModelo* objetos);
	void enviarEncuadres(JugadorModelo* jugador, FondoModelo* fondo,
			ControlEnemigosModelo* enemigos, ControlObjetosModelo* objetos);
	void enviarMensajeDeNivelTerminado(bool nivelTerminado);
};

#endif /* SRC_SERVIDOR_H_ */
