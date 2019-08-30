#ifndef SRC_VENTANADEJUEGO_H_
#define SRC_VENTANADEJUEGO_H_

#include "Renderizador.h"
#include <iostream>

class VentanaDeJuego {

private:
	int anchoPantalla;
	int altoPantalla;

public:
	VentanaDeJuego();
	int abrir();
	virtual ~VentanaDeJuego();
};

#endif /* SRC_VENTANADEJUEGO_H_ */
