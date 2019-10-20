#include "VistaFondo.h"

VistaFondo::VistaFondo(Renderizador* renderizador,
		pugi::xml_document *archiConfig, std::string nivel) {
	cielo = new VistaFondoCielo(renderizador, archiConfig, nivel);
	edificios = new VistaFondoEdificios(renderizador, archiConfig, nivel);
	terreno = new VistaFondoTerreno(renderizador, archiConfig, nivel);
}

void VistaFondo::renderizarConLosMensajes(MensajeServidor* mensajeCielo,
		MensajeServidor* mensajeEdificios, MensajeServidor* mensajeTerreno) {
	cielo->renderizarConElMensaje(mensajeCielo);
	edificios->renderizarConElMensaje(mensajeEdificios);
	terreno->renderizarConElMensaje(mensajeTerreno);
}

VistaFondo::~VistaFondo() {
	delete cielo;
	delete edificios;
	delete terreno;
}

