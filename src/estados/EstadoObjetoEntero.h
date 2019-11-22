#ifndef SRC_ESTADOS_ESTADOOBJETOENTERO_H_
#define SRC_ESTADOS_ESTADOOBJETOENTERO_H_

#include "../estados/EstadoObjeto.h"
#include "../estados/EstadoObjetoRoto.h"

class EstadoObjetoEntero: public EstadoObjeto {

public:
	EstadoObjetoEntero(tipoDeSprite tipo);
	EstadoObjeto* romperse(tipoDeSprite tipo);
	virtual ~EstadoObjetoEntero();
};

#endif /* SRC_ESTADOS_ESTADOOBJETOENTERO_H_ */
