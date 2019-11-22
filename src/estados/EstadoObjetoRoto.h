#ifndef SRC_ESTADOS_ESTADOOBJETOROTO_H_
#define SRC_ESTADOS_ESTADOOBJETOROTO_H_


#include "../estados/EstadoObjeto.h"

class EstadoObjetoRoto: public EstadoObjeto {

private:
	int framesTranscurridas;
	int numeroDeFrame;
	bool roturaTerminada;

public:
    EstadoObjetoRoto(tipoDeSprite tipo);
    EstadoObjeto* romperse(tipoDeSprite tipo);
    bool estaRoto();
    bool terminado();
    void cambiarFrame();
    virtual ~EstadoObjetoRoto();
};

#endif /* SRC_ESTADOS_ESTADOOBJETOROTO_H_ */
