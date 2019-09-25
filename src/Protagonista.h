#ifndef PROTAGONISTA_H_
#define PROTAGONISTA_H_

#include "Imagen.h"
#include "Textura.h"
#include "Renderizador.h"
#include "EstadoJugador.h"
#include "../lib/pugixml/pugixml.hpp"
#include "EstadoJugadorParado.h"
#include "Fondo.h"

class Protagonista {
private:
	int posicionX;
	int posicionY;
	int escaladoDeSprite;
	int movimientoEnX;
	int movimientoEnY;
	int posicionXMaxima;
	bool dadoVuelta;
	bool agachado;
	EstadoJugador* estado;
	EstadoJugadorParado* estadoOriginal;
	Encuadre insercion;
	Textura textura;
    pugi::xml_document *archiConfig;

public:
	Protagonista(Renderizador *renderizador, pugi::xml_document *archiConfig);
	void avanzar();
	void dejarDeAvanzar();
	void retroceder();
	void dejarDeRetroceder();
	void agacharse();
	void dejarDeAgacharse();
	void subir();
	void dejarDeSubir();
	void bajar();
	void dejarDeBajar();
	void pegar();
	void saltar();
	void actualizar(Renderizador *renderizador, Fondo* fondo);
	bool llegoAlFin(Fondo *fondo);
	virtual ~Protagonista();

private:
	void actualizarPosicion(Fondo* fondo);
	bool moverEnX(Fondo* fondo);
	bool moverEnY();
	int escalar(int tamanio);
};



#endif /* PROTAGONISTA_H_ */
