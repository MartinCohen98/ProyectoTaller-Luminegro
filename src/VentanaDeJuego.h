#ifndef SRC_VENTANADEJUEGO_H_
#define SRC_VENTANADEJUEGO_H_

#include "Textura.h"
#include <iostream>

class VentanaDeJuego {

private:
	SDL_Window* ventana;

public:
	VentanaDeJuego();
	int abrir();
	virtual ~VentanaDeJuego();
};

#endif /* SRC_VENTANADEJUEGO_H_ */
