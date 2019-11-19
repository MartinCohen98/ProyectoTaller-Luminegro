#ifndef SRC_MODELOS_COLISIONADOR_H_
#define SRC_MODELOS_COLISIONADOR_H_

#include <list>
#include "Colisionable.h"

class Colisionador {

private:
	std::list<Colisionable*> listaColisionables;

public:
	Colisionador();
	void agregarEntidad(Colisionable* colisionable);
	bool colisiona(Colisionable* colisionable);
	void vaciar();
	virtual ~Colisionador();

private:
	bool colisionan(Encuadre* unEncuadre, Encuadre* otroEncuadre);
	bool coincidenEnY(Encuadre* unEncuadre, Encuadre* otroEncuadre);
	bool seChocanEnX(Encuadre* unEncuadre, Encuadre* otroEncuadre);
};

#endif /* SRC_MODELOS_COLISIONADOR_H_ */
