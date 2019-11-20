/*
 * EstadoObjetoRoto.h
 *
 *  Created on: 20 nov. 2019
 *      Author: julio
 */

#ifndef SRC_ESTADOS_ESTADOOBJETOROTO_H_
#define SRC_ESTADOS_ESTADOOBJETOROTO_H_


#include "../estados/EstadoObjeto.h"

class EstadoObjetoRoto: public EstadoObjeto {
private:
	Encuadre frameActual;
	int alto;
	int ancho;
	tipoDeSprite tipo;
	int framesTranscurridas;
	int numeroDeFrame;
	bool roturaTerminada;
public:
    EstadoObjetoRoto(tipoDeSprite tipo);
    EstadoObjeto* romperse(tipoDeSprite tipo);
    bool terminado();
    void cambiarFrame();
    virtual ~EstadoObjetoRoto();
};

#endif /* SRC_ESTADOS_ESTADOOBJETOROTO_H_ */
