/*
 * Persona.h
 *
 *  Created on: 2 oct. 2019
 *      Author: julio
 */

#ifndef SRC_PERSONA_H_
#define SRC_PERSONA_H_

#include "EstadoJugador.h"
#include "Textura.h"
#include "Encuadre.h"

class Persona {
public:
	Persona();
	virtual void avanzar()=0;
	virtual void retroceder()=0;
	virtual void agacharse()=0;
	virtual void subir()=0;
	virtual void bajar()=0;
	virtual void actualizar(Renderizador *renderizador)=0;
	virtual ~Persona();
protected:
	int posicionX;
	int posicionY;
	bool dadoVuelta;
	EstadoJugador* estado;
	Encuadre insercion;
	Textura textura;


};

#endif /* SRC_PERSONA_H_ */
