#ifndef SRC_PERSONAMODELO_H_
#define SRC_PERSONAMODELO_H_

#include "grafica/Encuadre.h"
#include "estados/EstadoJugador.h"

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
