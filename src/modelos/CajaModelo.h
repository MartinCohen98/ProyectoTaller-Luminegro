#ifndef CAJAMODELO_H_
#define CAJAMODELO_H_

#include "ElementoModelo.h"
#include "../estados/EstadoObjetoEntero.h"
#include "../estados/EstadoObjetoRoto.h"

class CajaModelo: public ElementoModelo {
private:
    bool comenzoARomperse = false;

public:
	CajaModelo(int posXinicial, int posYinicial);
	int recibirDanioDe(Colisionable* colisionable);
	void romperse();
	void actualizar();
	virtual ~CajaModelo();
};

#endif /* CAJAMODELO_H_ */
