#ifndef SRC_CONTROLENEMIGOSMODELO_H_
#define SRC_CONTROLENEMIGOSMODELO_H_

#include "../modelos/EnemigoModelo.h"

class ControlEnemigosModelo {

private:
	EnemigoModelo **enemigos;
	int enemigosCantidad;

public:
	ControlEnemigosModelo(int nivel);
	int obtenerCantidad();
	void realizarMovimientos();
	void movimientosIniciales();
	void buscarObjetivo();
	void movidaDePantalla();
	int calcularDistancia(int x1, int y1, int x2, int y2);
	void generarMensajes(MensajeServidor* mensajes, int* mensajeActual);
	virtual ~ControlEnemigosModelo();
};

#endif /* SRC_CONTROLENEMIGOSMODELO_H_ */
