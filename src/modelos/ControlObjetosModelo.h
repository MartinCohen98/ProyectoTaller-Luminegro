#ifndef SRC_CONTROLOBJETOSMODELO_H_
#define SRC_CONTROLOBJETOSMODELO_H_

#include "../../lib/pugixml/pugixml.hpp"
#include "BarrilModelo.h"
#include "CajaModelo.h"
#include "CuchilloModelo.h"
#include "TuboModelo.h"
#include "../comunicacion/Socket.h"
#include <stdlib.h>
#include <time.h>
#include "Colisionador.h"

class ControlObjetosModelo {

private:
	int barrilesCantidad;
	int cajasCantidad;
	int cuchillosCantidad;
	int tubosCantidad;
	BarrilModelo **barriles;
	CajaModelo **cajas;
	CuchilloModelo **cuchillos;
	TuboModelo **tubos;

public:
	ControlObjetosModelo(pugi::xml_document *archiConfig,
								int terrenoWidth, int nivel);
	int obtenerCantidad();
	void movidaDePantalla();
	void generarMensajes(MensajeServidor* mensajes, int* mensajeActual);
	void agregarObjetosEnColisionador(Colisionador* colisionador);
	void actualizarPosiciones();
	virtual ~ControlObjetosModelo();
};

#endif /* SRC_CONTROLOBJETOSMODELO_H_ */
