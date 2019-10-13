#ifndef SRC_ELEMENTO_H_
#define SRC_ELEMENTO_H_

#include "Imagen.h"
#include "Textura.h"
#include "Encuadre.h"

class Elemento {

public:
	Elemento();
	void movidaDePantalla();
	void actualizar(Renderizador *renderizador);
	virtual ~Elemento();

protected:
	int posicionX;
	int posicionY;
	int ancho;
	int alto;
	Imagen sprite;
	Encuadre encuadre;
	Encuadre insercion;
	Textura textura;
};

#endif /* SRC_ELEMENTO_H_ */
