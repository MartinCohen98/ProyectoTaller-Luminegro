#ifndef SRC_CONTROLOBJETOS_H_
#define SRC_CONTROLOBJETOS_H_

#include "Renderizador.h"
#include "Barril.h"
#include "Caja.h"
#include "Cuchillo.h"
#include "Tubo.h"
#include "../lib/pugixml/pugixml.hpp"
#include "Fondo.h"
#include <stdlib.h>
#include <time.h>

class ControlObjetos {

private:
	int barrilesCantidad;
	int cajasCantidad;
	int cuchillosCantidad;
	int tubosMetalicosCantidad;
	Barril **barriles;
	Caja **cajas;
	Cuchillo **cuchillos;
	Tubo **tubos;

public:
	ControlObjetos(Renderizador *renderizador, pugi::xml_document *archiConfig, int terrenoWidth, int nivel);
	void movidaDePantalla();
	void actualizar(Renderizador *renderizador);
	void actualizarFrente(Renderizador* renderizador);
	virtual ~ControlObjetos();
};

#endif /* SRC_CONTROLOBJETOS_H_ */
