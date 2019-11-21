#ifndef SRC_ESTADOS_ESTADOOBJETO_H_
#define SRC_ESTADOS_ESTADOOBJETO_H_

#include "../comunicacion/MensajeServidor.h"

class EstadoObjeto {
public:
	EstadoObjeto();
	virtual EstadoObjeto* romperse();
	virtual ~EstadoObjeto();
};

#endif /* SRC_ESTADOS_ESTADOOBJETO_H_ */
