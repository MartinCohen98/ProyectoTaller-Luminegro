#ifndef SRC_CONTROLENEMIGOS_H_
#define SRC_CONTROLENEMIGOS_H_

#include "Enemigo.h"
#include "Renderizador.h"
#include "Parallax.h"
#include "../lib/pugixml/pugixml.hpp"


class ControlEnemigos {

private: Enemigo **enemigos;
         int enemigosCantidad;

public:
	ControlEnemigos(Renderizador *renderizador, pugi::xml_document *archiConfig);
	void realizarMovimientos();
	void movidaDePantalla();
	void actualizarFondo(Renderizador* renderizador);
	void actualizarFrente(Renderizador* renderizador);
	virtual ~ControlEnemigos();
};

#endif /* SRC_CONTROLENEMIGOS_H_ */
