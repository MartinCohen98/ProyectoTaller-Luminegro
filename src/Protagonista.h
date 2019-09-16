#ifndef PROTAGONISTA_H_
#define PROTAGONISTA_H_

#include "Imagen.h"
#include "Textura.h"
#include "Renderizador.h"
#include "Parallax.h"
#include "EstadoJugador.h"
#include "EstadoJugadorFrenado.h"
#include "../lib/pugixml/pugixml.hpp"

class Protagonista {
private:
	int posicionX;
	int posicionY;
	int ancho;
	int alto;
	bool dadoVuelta;
	EstadoJugador* estado;
	Imagen sprite;
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
	void actualizar(Renderizador *renderizador);
	bool llegoAlFin(Parallax *parallax);
	virtual ~Protagonista();

private:
	void moverEnX(int movimiento);
	int moverEnY(int nuevoY);
};



#endif /* PROTAGONISTA_H_ */
