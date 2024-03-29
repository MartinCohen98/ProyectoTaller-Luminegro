#ifndef SRC_FONDOMODELO_H_
#define SRC_FONDOMODELO_H_

#include "../grafica/Encuadre.h"
#include "../comunicacion/Socket.h"
#include "../../lib/pugixml/pugixml.hpp"

class FondoModelo {

private:
	int velocidades[3];
	int desplazamientos[3];
    Encuadre encuadres[3];
    int limite;
    int resolucionX;
    int resolucionY;
    Encuadre encuadreFijo;
    bool movido;
    bool fin;

public:
	FondoModelo(pugi::xml_document* archiConfig, int nivel);
	void mover();
	int obtenerAncho();
	void generarMensajes(MensajeServidor* mensajes, int* mensajeActual);
	bool seMovio();
	bool consultarFin();
	int darInicioTerreno();
	virtual ~FondoModelo();

};

#endif /* SRC_FONDOMODELO_H_ */
