#ifndef SRC_MENSAJECLIENTE_H_
#define SRC_MENSAJECLIENTE_H_

enum teclas {Right,Left,Up,Down,
		Jump, Crouch, Hit, Exit,
		StopGoingRight, StopGoingLeft,
		StopGoingUp, StopGoingDown,
		Rise,Nothing};

class MensajeCliente {

private:
	int datos;

public:
	MensajeCliente();
	void Codificar(enum teclas input);
	int get(void);
	virtual ~MensajeCliente();
};

#endif /* SRC_MENSAJECLIENTE_H_ */
