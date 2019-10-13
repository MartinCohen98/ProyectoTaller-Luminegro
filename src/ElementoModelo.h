#ifndef ELEMENTOMODELO_H_
#define ELEMENTOMODELO_H_

#include "Encuadre.h"

class ElementoModelo {

protected:
	int posicionX;
	int posicionY;
	int ancho;
	int alto;
	Encuadre encuadre;
	Encuadre insercion;

public:
	ElementoModelo();
	void movidaDePantalla();
	virtual ~ElementoModelo();
};

#endif /* ELEMENTOMODELO_H_ */
