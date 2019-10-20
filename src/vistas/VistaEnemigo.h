#ifndef SRC_VISTAENEMIGO_H_
#define SRC_VISTAENEMIGO_H_

#include "VistaGeneral.h"
#include "pugixml.hpp"

class VistaEnemigo: public VistaGeneral {

public:
	VistaEnemigo(Renderizador* elRenderizador, pugi::xml_document *archiConfig,
					tipoDeSprite codigoEnemigo);
	virtual ~VistaEnemigo();
};

#endif /* SRC_VISTAENEMIGO_H_ */
