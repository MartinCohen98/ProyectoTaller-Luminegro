#ifndef BARRIL_H_
#define BARRIL_H_

#include "Renderizador.h"
#include "../lib/pugixml/pugixml.hpp"
#include "Elemento.h"

class Barril: public Elemento {

public:
	Barril(Renderizador *renderizador, int posXinicial, int posYinicial, pugi::xml_document *archiConfig);
	virtual ~Barril();
};

#endif /* BARRIL_H_ */
