#ifndef SRC_CAJA_H_
#define SRC_CAJA_H_

#include "Renderizador.h"
#include "../lib/pugixml/pugixml.hpp"
#include "Elemento.h"

class Caja: public Elemento {

public:
	Caja(Renderizador *renderizador, int posXinicial, int posYinicial, pugi::xml_document *archiConfig);
	virtual ~Caja();
};

#endif /* SRC_CAJA_H_ */
