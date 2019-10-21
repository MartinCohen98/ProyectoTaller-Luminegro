#ifndef SRC_VISTAFONDOCIELO_H_
#define SRC_VISTAFONDOCIELO_H_

#include "VistaGeneral.h"
#include "../../lib/pugixml/pugixml.hpp"

class VistaFondoCielo: public VistaGeneral {

public:
	VistaFondoCielo(Renderizador* elRenderizador, pugi::xml_document *archiConfig,
			 std::string nivel);
	virtual ~VistaFondoCielo();
};

#endif /* SRC_VISTAFONDOCIELO_H_ */
