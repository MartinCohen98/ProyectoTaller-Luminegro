#ifndef ELEMENTOMODELO_H_
#define ELEMENTOMODELO_H_

#include "../grafica/Encuadre.h"
#include "../comunicacion/Socket.h"

class ElementoModelo {

protected:
	int posicionX;
	int posicionY;
	int ancho;
	int alto;
	tipoDeSprite sprite;
	Encuadre encuadre;
	Encuadre insercion;

public:
	ElementoModelo();
	void movidaDePantalla();
	void generarMensaje(MensajeServidor* mensajes, int* mensajeActual);
	virtual ~ElementoModelo();
};

#endif /* ELEMENTOMODELO_H_ */
