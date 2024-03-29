#ifndef SRC_VENTANACLIENTE_H_
#define SRC_VENTANACLIENTE_H_

#include <iostream>
#include "Renderizador.h"
#include <SDL2/SDL.h>
#include "../varios/Logger.h"
#include "../comunicacion/MensajeCliente.h"
#include "../../lib/pugixml/pugixml.hpp"

class VentanaCliente {
private:
	SDL_Window* ventana;
public:
	VentanaCliente();
	int abrir();
	SDL_Window* get();
	virtual ~VentanaCliente();
};

#endif /* SRC_VENTANACLIENTE_H_ */
