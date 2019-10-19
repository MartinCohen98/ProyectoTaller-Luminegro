#ifndef SRC_MENSAJESERVIDOR_H_
#define SRC_MENSAJESERVIDOR_H_

#include "Encuadre.h"
#include <string>

enum tipoDeSprite {Jugador1, Jugador2, Jugador3, Jugador4,
	Enemigo1, Enemigo2, Enemigo3, Barril, Caja,
	Cuchillo, Tubo
};

class MensajeServidor {

private:
	Encuadre frame;
	Encuadre insercion;
	bool dadoVuelta;
	tipoDeSprite sprite;

public:
	MensajeServidor();
	void generarMensaje(Encuadre* unFrame, Encuadre* unaInsercion, tipoDeSprite tipo);
	void darVuelta();
	Encuadre* obtenerFrame();
	Encuadre* obtenerInsercion();
	bool estaDadoVuelta();
	tipoDeSprite obtenerTipoDeSprite();
	std::string codificarMensaje(void);
	void decodificarMensaje(std::string mensaje);
	virtual ~MensajeServidor();
};

#endif /* SRC_MENSAJESERVIDOR_H_ */
