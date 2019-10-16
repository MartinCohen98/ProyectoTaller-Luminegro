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
	Socket socketAceptador;
	Socket* socketsDeClientes;

public:
	Servidor(int cantidadDeJugadores, char* puerto);
	void correr(pugi::xml_document* archiConfig);
	void recibirInput(JugadorModelo* jugador);
	void enviarEncuadres(JugadorModelo* jugador, ControlEnemigosModelo* enemigos,
							ControlObjetosModelo* objetos);
	virtual ~Servidor();
};

#endif /* SRC_SERVIDOR_H_ */
