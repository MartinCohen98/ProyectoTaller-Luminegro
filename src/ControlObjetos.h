#ifndef SRC_CONTROLOBJETOS_H_
#define SRC_CONTROLOBJETOS_H_

#include "Renderizador.h"
#include "../lib/pugixml/pugixml.hpp"
#include <stdlib.h>
#include <time.h>
#include "modelos/BarrilModelo.h"
#include "modelos/CajaModelo.h"
#include "modelos/CuchilloModelo.h"
#include "modelos/TuboModelo.h"

class ControlObjetos {

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
	ControlObjetos(Renderizador *renderizador, pugi::xml_document *archiConfig, int terrenoWidth, int nivel);
	void movidaDePantalla();
	void actualizar(Renderizador *renderizador);
	void actualizarFrente(Renderizador* renderizador);
	virtual ~ControlObjetos();
};

#endif /* SRC_CONTROLOBJETOS_H_ */
