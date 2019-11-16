#ifndef SRC_PERSONAMODELO_H_
#define SRC_PERSONAMODELO_H_

#include "../estados/EstadoJugador.h"
#include "Colisionable.h"

enum arma {cuchillo,tubo,desarmado};

class PersonaModelo: public Colisionable {

protected:
	int posicionX;
	int posicionY;
	bool dadoVuelta;
	int energia;
	int arma=desarmado;
	EstadoJugador* estado;

public:
	PersonaModelo();
	int darPosicionX();
	int darPosicionY();
	bool consultarDadoVuelta();
	virtual ~PersonaModelo();
};

#endif /* SRC_PERSONAMODELO_H_ */
