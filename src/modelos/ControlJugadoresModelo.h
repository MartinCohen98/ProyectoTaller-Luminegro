#ifndef SRC_MODELOS_CONTROLJUGADORESMODELO_H_
#define SRC_MODELOS_CONTROLJUGADORESMODELO_H_

#include "JugadorModelo.h"

class ControlJugadoresModelo {

private:
	JugadorModelo** jugadores;
	int cantidad;

public:
	ControlJugadoresModelo(pugi::xml_document *archiConfig, int cantidadJugadores);
	void procesarInput(MensajeCliente* mensaje, int numeroDeJugador);
	void realizarMovimientos(FondoModelo* fondo);
	void generarMensajes(MensajeServidor* mensajes, int* mensajeActual);
	bool llegaronAlFin(FondoModelo* fondo);
	virtual ~ControlJugadoresModelo();
};

#endif /* SRC_MODELOS_CONTROLJUGADORESMODELO_H_ */
