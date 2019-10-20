#ifndef PROTAGONISTA_H_
#define PROTAGONISTA_H_

#include "Imagen.h"
#include "Renderizador.h"
#include "../lib/pugixml/pugixml.hpp"
#include "estados/EstadoJugadorParado.h"
#include "Persona.h"

class Protagonista: public Persona {
private:
	int escaladoDeSprite;
	int movimientoEnX;
	int movimientoEnY;
	int movimientoAlSaltarEnX;
	int movimientoAlSaltarEnY;
	int posicionXMaxima;
	bool agachado;
	EstadoJugadorParado* estadoOriginal;

public:
    Protagonista();
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
	void actualizar(Renderizador *renderizador);
	virtual ~Protagonista();

private:
	bool moverEnY();
	int escalar(int tamanio);
};



#endif /* PROTAGONISTA_H_ */
