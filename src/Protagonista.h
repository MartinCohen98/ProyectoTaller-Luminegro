#ifndef PROTAGONISTA_H_
#define PROTAGONISTA_H_

#include "Imagen.h"
#include "Renderizador.h"
#include "../lib/pugixml/pugixml.hpp"
#include "EstadoJugadorParado.h"
#include "Fondo.h"
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
	void realizarMovimientos(Fondo* fondo);
	void actualizar(Renderizador *renderizador);
	bool llegoAlFin(Fondo *fondo);
	virtual ~Protagonista();

private:
	void actualizarPosicion(Fondo* fondo);
	bool moverEnX(Fondo* fondo);
	bool moverEnY();
	int escalar(int tamanio);
};



#endif /* PROTAGONISTA_H_ */
