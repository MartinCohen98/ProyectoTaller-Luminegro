#ifndef SRC_BARRILMODELO_H_
#define SRC_BARRILMODELO_H_

#include "ElementoModelo.h"

class BarrilModelo: public ElementoModelo {

public:
	BarrilModelo(int posXinicial, int posYinicial);
	int recibirDanioDe(Colisionable* colisionable);
	virtual ~BarrilModelo();
};

#endif /* SRC_BARRILMODELO_H_ */
