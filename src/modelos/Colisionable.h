#ifndef SRC_MODELOS_COLISIONABLE_H_
#define SRC_MODELOS_COLISIONABLE_H_

#include "../grafica/Encuadre.h"
#include "TipoDeArma.h"

class Colisionable {

protected:
	Encuadre insercion;

public:
	Colisionable();
	Encuadre* obtenerInsercion();
	virtual bool estaAtacando();
	virtual int recibirDanioDe(Colisionable* colisionable);
	virtual int obtenerDanio();
	virtual int obtenerPuntosDeGolpe();
	virtual tipoDeArma obtenerTipoDeArma();
	virtual void desaparecer();
	virtual ~Colisionable();
};

#endif /* SRC_MODELOS_COLISIONABLE_H_ */
