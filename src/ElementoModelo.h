#ifndef ELEMENTOMODELO_H_
#define ELEMENTOMODELO_H_

#include "Encuadre.h"
#include "Socket.h"

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
	void enviarEncuadres(Socket*& sockets, int cantidad);
	virtual ~ElementoModelo();
};

#endif /* ELEMENTOMODELO_H_ */
