#ifndef SRC_MODELOS_COLISIONADOR_H_
#define SRC_MODELOS_COLISIONADOR_H_

#include <list>
#include "../grafica/Encuadre.h"

class Colisionador {

private:
	std::list<Encuadre*> listaEncuadres;

public:
	Colisionador();
	void agregarEncuadre(Encuadre* encuadre);
	bool colisiona(Encuadre* encuadre);
	virtual ~Colisionador();

private:
	bool colisionan(Encuadre* unEncuadre, Encuadre* otroEncuadre);
	bool coincidenEnY(Encuadre* unEncuadre, Encuadre* otroEncuadre);
	bool seChocanEnX(Encuadre* unEncuadre, Encuadre* otroEncuadre);
};

#endif /* SRC_MODELOS_COLISIONADOR_H_ */
