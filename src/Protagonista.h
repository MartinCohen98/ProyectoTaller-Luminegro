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
	int escaladoDeSprite;
	int movimientoEnX;
	int movimientoEnY;
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
	void actualizar(Renderizador *renderizador, Parallax* parallax);
	bool llegoAlFin(Parallax *parallax);
	virtual ~Protagonista();

private:
	void actualizarPosicion(Parallax* parallax);
	bool moverEnX(Parallax* parallax);
	bool moverEnY();
	int escalar(int tamanio);
};



#endif /* PROTAGONISTA_H_ */
