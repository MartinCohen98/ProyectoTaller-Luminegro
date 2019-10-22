#ifndef SRC_SERVIDOR_H_
#define SRC_SERVIDOR_H_

#include "Socket.h"
#include "../modelos/ControlJugadoresModelo.h"
#include "../modelos/ControlEnemigosModelo.h"
#include "../modelos/ControlObjetosModelo.h"
#include "MensajeCliente.h"

class Servidor {

private:
	int jugadores;
	MensajeCliente mensajeCliente;
	MensajeServidor* mensajesServidor;
	int cantidadDeMensajes;
	Socket socketAceptador;
	Socket* socketsDeClientes;

public:
	Servidor(int cantidadDeJugadores, char* puerto);
	void correr(pugi::xml_document* archiConfig);
	virtual ~Servidor();

private:
	void recibirInputs(ControlJugadoresModelo* protagonistas);
	void enviarCantidadDeReceives(ControlEnemigosModelo* enemigos,
							ControlObjetosModelo* objetos);
	void enviarEncuadres(ControlJugadoresModelo* protagonistas, FondoModelo* fondo,
			ControlEnemigosModelo* enemigos, ControlObjetosModelo* objetos);
	void enviarMensajeDeNivelTerminado(bool nivelTerminado);
	void generarMensajesParaEnviar();
};

#endif /* SRC_SERVIDOR_H_ */
