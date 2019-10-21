#ifndef SRC_VISTAFONDOTERRENO_H_
#define SRC_VISTAFONDOTERRENO_H_

#include "VistaGeneral.h"
#include "../../lib/pugixml/pugixml.hpp"

class VistaFondoTerreno: public VistaGeneral {
public:
	VistaFondoTerreno(Renderizador* elRenderizador,
			pugi::xml_document *archiConfig, std::string nivel);
	virtual ~VistaFondoTerreno();
};

#endif /* SRC_VISTAFONDOTERRENO_H_ */
