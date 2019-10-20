#ifndef SRC_VISTAJUGADOR_H_
#define SRC_VISTAJUGADOR_H_

#include "VistaGeneral.h"
#include "pugixml.hpp"

class VistaJugador: public VistaGeneral {

public:
	VistaJugador(Renderizador* elRenderizador, pugi::xml_document *archiConfig,
					tipoDeSprite jugador);
	virtual ~VistaJugador();
};

#endif /* SRC_VISTAJUGADOR_H_ */
