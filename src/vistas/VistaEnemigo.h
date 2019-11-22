#ifndef SRC_VISTAENEMIGO_H_
#define SRC_VISTAENEMIGO_H_

#include "VistaGeneral.h"
#include "../../lib/pugixml/pugixml.hpp"

class VistaEnemigo: public VistaGeneral {

public:
	VistaEnemigo(Renderizador* elRenderizador, pugi::xml_document *archiConfig,	tipoDeSprite codigoEnemigo,
	        bool *ejecutarSonidoGolpeTiro, bool *ejecutarSonidoGolpeImpacto, bool *ejecutarSonidoSalto,
        bool *ejecutarSonidoCaida);

	virtual ~VistaEnemigo();
};

#endif /* SRC_VISTAENEMIGO_H_ */
