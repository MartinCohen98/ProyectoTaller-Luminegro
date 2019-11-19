#include "Colisionador.h"

Colisionador::Colisionador() {}


void Colisionador::agregarEntidad(Colisionable* colisionable) {
	listaColisionables.push_front(colisionable);
}


void Colisionador::vaciar() {
	while (!listaColisionables.empty())
		listaColisionables.pop_front();
}


bool Colisionador::colisiona(Colisionable* colisionable) {
	bool colisiona = false;
	for (std::list<Colisionable*>::iterator it = listaColisionables.begin();
										it != listaColisionables.end(); ++it) {
		if (((*it)->obtenerInsercion() != colisionable->obtenerInsercion()) && !colisiona)
			colisiona = colisionan(colisionable->obtenerInsercion(), (*it)->obtenerInsercion());
	}
	return colisiona;
}


bool Colisionador::colisionan(Encuadre* unEncuadre, Encuadre* otroEncuadre) {
	bool colisionan = false;
	if (coincidenEnY(unEncuadre, otroEncuadre) &&
			seChocanEnX(unEncuadre, otroEncuadre)) {
		colisionan = true;
	}
	return colisionan;
}


bool Colisionador::coincidenEnY(Encuadre* unEncuadre, Encuadre* otroEncuadre) {
	bool coinciden = false;
	int unaPosicionY = unEncuadre->getY() + unEncuadre->getAlto();
	int otraPosicionY = otroEncuadre->getY() + otroEncuadre->getAlto();
	if ((unaPosicionY + 10 > otraPosicionY - 10) &&
			(unaPosicionY - 10 < otraPosicionY + 10))
		coinciden = true;
	return coinciden;
}


bool Colisionador::seChocanEnX(Encuadre* unEncuadre, Encuadre* otroEncuadre) {
	bool seChocan = false;
	int unaPrimeraPosicion = unEncuadre->getX();
	int unaUltimaPosicion = unEncuadre->getX() + unEncuadre->getAncho();
	int otraPrimeraPosicion = otroEncuadre->getX();
	int otraUltimaPosicion = otroEncuadre->getX() + otroEncuadre->getAncho();
	if ((unaPrimeraPosicion < otraUltimaPosicion) &&
			(unaUltimaPosicion > otraPrimeraPosicion))
		seChocan = true;
	return seChocan;
}


Colisionador::~Colisionador() {
	vaciar();
}

