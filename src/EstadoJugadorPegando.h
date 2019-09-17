#ifndef SRC_ESTADOJUGADORPEGANDO_H_
#define SRC_ESTADOJUGADORPEGANDO_H_

#include "EstadoJugador.h"
#include "EstadoJugadorParado.h"

class EstadoJugadorPegando: public EstadoJugador {

public:

	EstadoJugadorPegando();
	EstadoJugador* avanzar();
	EstadoJugador* parar();
	EstadoJugador* agacharse();
	EstadoJugador* pegar();
	bool terminado();
	virtual ~EstadoJugadorPegando();
};

#endif /* SRC_ESTADOJUGADORPEGANDO_H_ */
