#ifndef ELEMENTOMODELO_H_
#define ELEMENTOMODELO_H_

#include "../comunicacion/Socket.h"
#include "Colisionable.h"

class ElementoModelo: public Colisionable {

protected:
	int posicionX;
	int posicionY;
	int ancho;
	int alto;
	int golpesResistidos;
	tipoDeSprite sprite;
	Encuadre encuadre;

public:
	ElementoModelo();
	void movidaDePantalla();
	void generarMensaje(MensajeServidor* mensajes, int* mensajeActual);
	virtual ~ElementoModelo();
};

#endif /* ELEMENTOMODELO_H_ */
