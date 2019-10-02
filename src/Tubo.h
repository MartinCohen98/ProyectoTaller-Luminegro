#ifndef SRC_TUBO_H_
#define SRC_TUBO_H_

#include "Renderizador.h"
#include "../lib/pugixml/pugixml.hpp"
#include "Elemento.h"

class Tubo: public Elemento {

public:
	Tubo(Renderizador *renderizador, int posXinicial, int posYinicial, pugi::xml_document *archiConfig);
	virtual ~Tubo();
};

#endif /* SRC_TUBO_H_ */
