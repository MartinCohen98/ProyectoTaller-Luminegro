#ifndef SRC_MODELOS_COLISIONABLE_H_
#define SRC_MODELOS_COLISIONABLE_H_

#include "../grafica/Encuadre.h"
#include "Colisionador.h"

class Colisionable {

protected:
	Encuadre insercion;

public:
	Colisionable();
	void agregarEnColisionador(Colisionador* colisionador);
	virtual ~Colisionable();
};

#endif /* SRC_MODELOS_COLISIONABLE_H_ */
