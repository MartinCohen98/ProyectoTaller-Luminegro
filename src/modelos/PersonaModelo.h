#ifndef SRC_PERSONAMODELO_H_
#define SRC_PERSONAMODELO_H_

#include "../estados/EstadoJugador.h"
#include "Colisionable.h"

class PersonaModelo: public Colisionable {

protected:
	int posicionX;
	int posicionY;
	int posicionXAnterior;
	int posicionYAnterior;
	bool dadoVuelta;
	int energia;
	EstadoJugador* estado;

public:
	PersonaModelo();
	int darPosicionX();
	int darPosicionY();
	bool consultarDadoVuelta();
	virtual void sumarPuntos();
	virtual ~PersonaModelo();
};

#endif /* SRC_PERSONAMODELO_H_ */
