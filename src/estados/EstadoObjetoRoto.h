/*
 * EstadoObjetoRoto.h
 *
 *  Created on: 20 nov. 2019
 *      Author: julio
 */

#ifndef SRC_ESTADOS_ESTADOOBJETOROTO_H_
#define SRC_ESTADOS_ESTADOOBJETOROTO_H_

#include "../comunicacion/MensajeServidor.h"

class EstadoObjetoRoto {
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
    EstadoObjetoRoto* romperse(tipoDeSprite tipo);
    bool terminado();
    void cambiarFrame();
    virtual ~EstadoObjetoRoto();
};

#endif /* SRC_ESTADOS_ESTADOOBJETOROTO_H_ */
