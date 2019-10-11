/*
 * MensajeCliente.h
 *
 *  Created on: 9 oct. 2019
 *      Author: julio
 */

#ifndef SRC_MENSAJECLIENTE_H_
#define SRC_MENSAJECLIENTE_H_

enum teclas {Right,Left,Up,Down,
		Jump, Crouch, Hit, Exit,
		StopGoingRight, StopGoingLeft,
		StopGoingUp, StopGoingDown,
		Rise};

class MensajeCliente {
private:
	int datos;
public:
	MensajeCliente();
	void Codificar(enum teclas input);
	int DarDatos(void);
	virtual ~MensajeCliente();
};

#endif /* SRC_MENSAJECLIENTE_H_ */
