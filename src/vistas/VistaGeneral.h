#ifndef SRC_VISTAGENERAL_H_
#define SRC_VISTAGENERAL_H_

#include "../grafica/Textura.h"
#include "../comunicacion/MensajeServidor.h"

class VistaGeneral {

protected:
	Textura textura;
	Renderizador* renderizador;
    bool *ejecutarSonidoGolpeTiro;
    bool *ejecutarSonidoGolpeImpacto;
    bool *ejecutarSonidoSalto;
    bool *ejecutarSonidoCaida;
    bool *ejecutarSonidoDestruccion;

public:
	VistaGeneral();
	void renderizarConElMensaje(MensajeServidor* mensaje);
	virtual ~VistaGeneral();
};

#endif /* SRC_VISTAGENERAL_H_ */
