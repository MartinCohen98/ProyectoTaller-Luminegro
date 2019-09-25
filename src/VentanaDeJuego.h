#ifndef SRC_VENTANADEJUEGO_H_
#define SRC_VENTANADEJUEGO_H_

#include <iostream>
#include "Renderizador.h"
#include "Protagonista.h"
#include "ControlObjetos.h"
#include "ControlEnemigos.h"
#include <SDL2/SDL.h>
#include "Logger.h"

class VentanaDeJuego {

private:
	SDL_Window* ventana;

public:
	VentanaDeJuego();
	int abrir(pugi::xml_document* archiConfig);
	virtual ~VentanaDeJuego();
};

#endif /* SRC_VENTANADEJUEGO_H_ */
