#ifndef SRC_CONTROLENEMIGOSMODELO_H_
#define SRC_CONTROLENEMIGOSMODELO_H_

#include "modelos/EnemigoModelo.h"

class ControlEnemigosModelo {

private:
	EnemigoModelo **enemigos;
	int enemigosCantidad;

public:
	ControlEnemigosModelo(int nivel);
	int obtenerCantidad();
	void realizarMovimientos();
	void movidaDePantalla();
	void enviarEncuadres(Socket *sockets, int cantidadDeSockets);
	virtual ~ControlEnemigosModelo();
};

#endif /* SRC_CONTROLENEMIGOSMODELO_H_ */
