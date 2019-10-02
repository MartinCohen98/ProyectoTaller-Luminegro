#ifndef ENEMIGO_H_
#define ENEMIGO_H_

#include "EstadoEnemigoParado.h"
#include "Imagen.h"
#include "Textura.h"
#include "Renderizador.h"
#include "EstadoJugador.h"
#include "Fondo.h"
#include "Persona.h"

class Enemigo: public Persona {

private:
	int ancho;
	int alto;
	bool contactoVisual;
	bool modoBusqueda;
	Imagen sprite;

public:
	Enemigo(Renderizador *renderizador, int posXinicial, int posYinicial, const char* path);
	void avanzar();
	void parar();
	void retroceder();
	void agacharse();
	void subir();
	void bajar();
	void actualizar(Renderizador *renderizador);
	void actualizarRetroceso();
	int cambiarFrameInicial(int x,int y,int ancho,int alto);
	virtual ~Enemigo();

private:
	void moverEnX(int movimiento);
	int moverEnY(int nuevoY);

};

#endif /* ENEMIGO_H_ */
