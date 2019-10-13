#ifndef SRC_CONTROLOBJETOSMODELO_H_
#define SRC_CONTROLOBJETOSMODELO_H_

#include "../lib/pugixml/pugixml.hpp"
#include "BarrilModelo.h"
#include "CajaModelo.h"
#include "CuchilloModelo.h"
#include "TuboModelo.h"
#include <stdlib.h>
#include <time.h>

class ControlObjetosModelo {

private:
	int barrilesCantidad;
	int cajasCantidad;
	int cuchillosCantidad;
	int tubosMetalicosCantidad;
	BarrilModelo **barriles;
	CajaModelo **cajas;
	CuchilloModelo **cuchillos;
	TuboModelo **tubos;

public:
	ControlObjetosModelo(pugi::xml_document *archiConfig,
								int terrenoWidth, int nivel);
	void movidaDePantalla();
	virtual ~ControlObjetosModelo();
};

#endif /* SRC_CONTROLOBJETOSMODELO_H_ */
