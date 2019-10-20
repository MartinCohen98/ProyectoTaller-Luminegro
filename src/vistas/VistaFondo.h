#ifndef SRC_VISTAFONDO_H_
#define SRC_VISTAFONDO_H_

#include "VistaFondoCielo.h"
#include "VistaFondoEdificios.h"
#include "VistaFondoTerreno.h"

class VistaFondo {

private:
	VistaFondoCielo* cielo;
	VistaFondoEdificios* edificios;
	VistaFondoTerreno* terreno;

public:
	VistaFondo(Renderizador* renderizador, pugi::xml_document *archiConfig,
				std::string nivel);
	void renderizarConLosMensajes(MensajeServidor* mensajeCielo,
			MensajeServidor* mensajeEdificios, MensajeServidor* mensajeTerreno);
	virtual ~VistaFondo();
};

#endif /* SRC_VISTAFONDO_H_ */
