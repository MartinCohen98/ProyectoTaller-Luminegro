#ifndef SRC_VISTAOBJETO_H_
#define SRC_VISTAOBJETO_H_

#include "VistaGeneral.h"
#include "../lib/pugixml/pugixml.hpp"

class VistaObjeto: public VistaGeneral {

public:
	VistaObjeto(Renderizador* elRenderizador, pugi::xml_document *archiConfig,
			sprite codigoObjeto);
	virtual ~VistaObjeto();
};

#endif /* SRC_VISTAOBJETO_H_ */
