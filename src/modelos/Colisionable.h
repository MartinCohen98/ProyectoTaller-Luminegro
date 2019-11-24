#ifndef SRC_MODELOS_COLISIONABLE_H_
#define SRC_MODELOS_COLISIONABLE_H_

#include "../grafica/Encuadre.h"
#include "TipoDeArma.h"
#include "../comunicacion/MensajeServidor.h"

class Colisionable {

protected:
	Encuadre insercion;
	tipoDeSprite tipo;

public:
	Colisionable();
	Encuadre* obtenerInsercion();
	virtual bool estaAtacando();
	virtual int recibirDanioDe(Colisionable* colisionable);
	virtual int obtenerDanio();
	virtual int obtenerPuntosDeGolpe();
	virtual void sumarPuntos(int puntos);
	virtual tipoDeArma obtenerTipoDeArma();
	virtual void desaparecer();
	tipoDeSprite consultarTipo();
	virtual ~Colisionable();
};

#endif /* SRC_MODELOS_COLISIONABLE_H_ */
