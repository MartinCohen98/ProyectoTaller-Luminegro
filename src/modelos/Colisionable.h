#ifndef SRC_MODELOS_COLISIONABLE_H_
#define SRC_MODELOS_COLISIONABLE_H_

#include "../grafica/Encuadre.h"

class Colisionable {

protected:
	Encuadre insercion;

public:
	Colisionable();
	Encuadre* obtenerInsercion();
	virtual bool estaAtacando();
	virtual void recibirDanioDe(Colisionable* colisionable);
	virtual int obtenerDanio();
	virtual ~Colisionable();
};

#endif /* SRC_MODELOS_COLISIONABLE_H_ */
