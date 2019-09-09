#ifndef SRC_VENTANADEJUEGO_H_
#define SRC_VENTANADEJUEGO_H_

#include "Textura.h"
#include <iostream>
#include "Renderizador.h"

class VentanaDeJuego {

private:
	SDL_Window* ventana;

public:
	VentanaDeJuego();
	int Abrir(Renderizador *renderizador);
	SDL_Window* Get();
	virtual ~VentanaDeJuego();
};

#endif /* SRC_VENTANADEJUEGO_H_ */
