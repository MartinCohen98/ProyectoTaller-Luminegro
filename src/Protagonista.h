#ifndef PROTAGONISTA_H_
#define PROTAGONISTA_H_

#include "Imagen.h"
#include "Textura.h"
#include "Renderizador.h"
#include "Parallax.h"
#include "EstadoJugador.h"
#include "../lib/pugixml/pugixml.hpp"
#include "EstadoJugadorParado.h"

class Protagonista {
private:
	int posicionX;
	int posicionY;
	int escalado;
	bool dadoVuelta;
	EstadoJugador* estado;
	EstadoJugadorParado* estadoOriginal;
	Encuadre insercion;
	Textura textura;
    pugi::xml_document *archiConfig;

public:
	Protagonista(Renderizador *renderizador, pugi::xml_document *archiConfig);
	int avanzar(Parallax *parallax);
	void parar();
	void retroceder();
	void agacharse();
	void subir();
	void bajar();
	void pegar();
	void actualizar(Renderizador *renderizador);
	bool llegoAlFin(Parallax *parallax);
	virtual ~Protagonista();

private:
	void moverEnX(int movimiento);
	int moverEnY(int nuevoY);
	int escalar(int tamanio);
};



#endif /* PROTAGONISTA_H_ */
