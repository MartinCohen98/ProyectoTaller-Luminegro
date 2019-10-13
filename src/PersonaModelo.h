#ifndef SRC_PERSONAMODELO_H_
#define SRC_PERSONAMODELO_H_

#include "Encuadre.h"
#include "EstadoJugador.h"

class PersonaModelo {

protected:
	int posicionX;
	int posicionY;
	bool dadoVuelta;
	EstadoJugador* estado;
	Encuadre insercion;

public:
	PersonaModelo();
	virtual ~PersonaModelo();
};

#endif /* SRC_PERSONAMODELO_H_ */
