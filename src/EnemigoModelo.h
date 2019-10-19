#ifndef SRC_ENEMIGOMODELO_H_
#define SRC_ENEMIGOMODELO_H_

#include "PersonaModelo.h"
#include "EstadoEnemigoParado.h"
#include "Socket.h"

class EnemigoModelo: public PersonaModelo {

private:
	int ancho;
	int alto;

public:
	EnemigoModelo(int posXinicial, int posYinicial);
	void avanzar();
	void parar();
	void retroceder();
	void agacharse();
	void subir();
	void bajar();
	void retrocesoDePantalla();
	void enviarEncuadres(Socket*& sockets, int cantidad);
	virtual ~EnemigoModelo();

private:
	void actualizarInsercion();
	void moverEnX(int movimiento);
	void moverEnY(int movimiento);
};

#endif /* SRC_ENEMIGOMODELO_H_ */
