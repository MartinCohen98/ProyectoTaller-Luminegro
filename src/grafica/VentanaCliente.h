#ifndef SRC_VENTANACLIENTE_H_
#define SRC_VENTANACLIENTE_H_

#include <iostream>
#include "Renderizador.h"
#include <SDL2/SDL.h>
#include "varios/Logger.h"
#include "varios/MensajeCliente.h"
#include "pugixml.hpp"

class VentanaCliente {
private:
	SDL_Window* ventana;
public:
	VentanaCliente();
	int abrir(pugi::xml_document* archiConfig);
	SDL_Window* get();
	virtual ~VentanaCliente();
};

#endif /* SRC_VENTANACLIENTE_H_ */
