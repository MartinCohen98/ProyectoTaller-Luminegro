#ifndef SRC_MODELOS_COLISIONADOR_H_
#define SRC_MODELOS_COLISIONADOR_H_

#include <list>
#include "Colisionable.h"

class Colisionador {

private:
	std::list<Colisionable*> listaColisionables;
	std::list<Colisionable*> listaLevantables;

public:
	Colisionador();
	void agregarColisionable(Colisionable* colisionable);
	void agregarLevantable(Colisionable* levantable);
	bool colisiona(Colisionable* colisionable, tipoDeSprite* tipoColision, bool* estaAtacando);
	Colisionable* levantarSiHay(Colisionable* jugador);
	void vaciar();
	virtual ~Colisionador();

private:
	bool colisionan(Encuadre* unEncuadre, Encuadre* otroEncuadre);
	bool coincidenEnY(Encuadre* unEncuadre, Encuadre* otroEncuadre);
	bool seChocanEnX(Encuadre* unEncuadre, Encuadre* otroEncuadre);
};

#endif /* SRC_MODELOS_COLISIONADOR_H_ */
