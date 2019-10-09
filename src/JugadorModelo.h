#ifndef SRC_JUGADORMODELO_H_
#define SRC_JUGADORMODELO_H_

#include "EstadoJugadorParado.h"
#include "Persona.h"
#include "../lib/pugixml/pugixml.hpp"
#include <string>
#include "FondoModelo.h"

class JugadorModelo: public Persona {

private:
	int escaladoDeSprite;
	int movimientoEnX;
	int movimientoEnY;
	int movimientoAlSaltarEnX;
	int movimientoAlSaltarEnY;
	int posicionXMaxima;
	bool agachado;
	EstadoJugadorParado* estadoOriginal;

public:
	JugadorModelo(pugi::xml_document *archiConfig);
	void avanzar();
	void dejarDeAvanzar();
	void retroceder();
	void dejarDeRetroceder();
	void agacharse();
	void dejarDeAgacharse();
	void subir();
	void dejarDeSubir();
	void bajar();
	void dejarDeBajar();
	void pegar();
	void saltar();
	void realizarMovimientos(FondoModelo* fondo);
	bool llegoAlFin(FondoModelo *fondo);
	virtual ~JugadorModelo();

private:
	void actualizarPosicion(FondoModelo* fondo);
	void actualizarInsercion();
	bool moverEnX(FondoModelo* fondo);
	bool moverEnY();
	int escalar(int tamanio);
};

#endif /* SRC_JUGADORMODELO_H_ */
