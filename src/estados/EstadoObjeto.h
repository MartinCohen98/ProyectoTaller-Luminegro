#ifndef SRC_ESTADOS_ESTADOOBJETO_H_
#define SRC_ESTADOS_ESTADOOBJETO_H_

#include "../comunicacion/MensajeServidor.h"

class EstadoObjeto {

protected:
	Encuadre frameActual;
	int alto;
	int ancho;
	tipoDeSprite tipo;

public:
	EstadoObjeto();
	virtual EstadoObjeto* romperse(tipoDeSprite tipo);
	virtual bool estaRoto();
	virtual bool terminado();
	Encuadre* obtenerEncuadre();
	virtual ~EstadoObjeto();
};

#endif /* SRC_ESTADOS_ESTADOOBJETO_H_ */
