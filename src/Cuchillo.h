#ifndef SRC_CUCHILLO_H_
#define SRC_CUCHILLO_H_

#include "Renderizador.h"
#include "../lib/pugixml/pugixml.hpp"
#include "Elemento.h"

class Cuchillo: public Elemento {

public:
	Cuchillo(Renderizador *renderizador, int posXinicial, int posYinicial, pugi::xml_document *archiConfig);
	virtual ~Cuchillo();
};

#endif /* SRC_CUCHILLO_H_ */
