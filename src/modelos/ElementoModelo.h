#ifndef ELEMENTOMODELO_H_
#define ELEMENTOMODELO_H_

#include "../comunicacion/Socket.h"
#include "Colisionable.h"
#include "../estados/EstadoObjeto.h"

class ElementoModelo: public Colisionable {

protected:
	int posicionX;
	int posicionY;
	int ancho;
	int alto;
	int golpes;
	tipoDeSprite sprite;
	Encuadre encuadre;
	EstadoObjeto* estado;
    bool ejecutarSonidoDestruccion = false;

public:
	ElementoModelo();
	void movidaDePantalla();
	void generarMensaje(MensajeServidor* mensajes, int* mensajeActual);
	void desaparecer();
	void actualizarInsercion();
	void actualizarPosicion();
	virtual ~ElementoModelo();
};

#endif /* ELEMENTOMODELO_H_ */
