#ifndef SRC_VISTAFONDOEDIFICIOS_H_
#define SRC_VISTAFONDOEDIFICIOS_H_

#include "VistaGeneral.h"
#include "pugixml.hpp"

class VistaFondoEdificios: public VistaGeneral {
public:
	VistaFondoEdificios(Renderizador* elRenderizador,
			pugi::xml_document *archiConfig, std::string nivel);
	virtual ~VistaFondoEdificios();
};

#endif /* SRC_VISTAFONDOEDIFICIOS_H_ */
