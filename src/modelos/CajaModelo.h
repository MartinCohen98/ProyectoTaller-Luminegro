#ifndef CAJAMODELO_H_
#define CAJAMODELO_H_

#include "ElementoModelo.h"

class CajaModelo: public ElementoModelo {

public:
	CajaModelo(int posXinicial, int posYinicial);
	int recibirDanioDe(Colisionable* colisionable);
	virtual ~CajaModelo();
};

#endif /* CAJAMODELO_H_ */
