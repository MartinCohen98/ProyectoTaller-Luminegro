#ifndef SRC_BARRILMODELO_H_
#define SRC_BARRILMODELO_H_

#include "ElementoModelo.h"
#include "../estados/EstadoObjetoEntero.h"
#include "../estados/EstadoObjetoRoto.h"

class BarrilModelo: public ElementoModelo {

public:
	BarrilModelo(int posXinicial, int posYinicial);
	int recibirDanioDe(Colisionable* colisionable);
	void romperse();
	virtual ~BarrilModelo();
};

#endif /* SRC_BARRILMODELO_H_ */
