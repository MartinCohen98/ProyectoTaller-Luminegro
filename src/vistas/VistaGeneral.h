#ifndef SRC_VISTAGENERAL_H_
#define SRC_VISTAGENERAL_H_

#include "Textura.h"
#include "MensajeServidor.h"

class VistaGeneral {

protected:
	Textura textura;
	Renderizador* renderizador;

public:
	VistaGeneral();
	void renderizarConElMensaje(MensajeServidor* mensaje);
	virtual ~VistaGeneral();
};

#endif /* SRC_VISTAGENERAL_H_ */
