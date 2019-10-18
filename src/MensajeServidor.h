#ifndef SRC_MENSAJESERVIDOR_H_
#define SRC_MENSAJESERVIDOR_H_

#include "Encuadre.h"
#include <string>

enum sprite {Jugador1, Jugador2, Jugador3, Jugador4,
	Enemigo1, Enemigo2, Enemigo3, Barril, Caja,
	Cuchillo, Tubo
};

class MensajeServidor {

private:
	Encuadre* frame;
	Encuadre* insercion;
	bool dadoVuelta;
	sprite tipoDeSprite;

public:
	MensajeServidor();
	void generarMensaje(Encuadre* unFrame, Encuadre* unaInsercion, sprite tipo);
	void darVuelta();
	std::string codificarMensaje(void);
	void decodificar(std::string mensaje);
	virtual ~MensajeServidor();
};

#endif /* SRC_MENSAJESERVIDOR_H_ */
