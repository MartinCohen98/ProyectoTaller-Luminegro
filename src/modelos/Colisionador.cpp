#include "Colisionador.h"

Colisionador::Colisionador() {}


void Colisionador::agregarColisionable(Colisionable* colisionable) {
	listaColisionables.push_front(colisionable);
}


void Colisionador::agregarLevantable(Colisionable* levantable) {
	listaLevantables.push_front(levantable);
}


void Colisionador::vaciar() {
	while (!listaColisionables.empty())
		listaColisionables.pop_front();
}


bool Colisionador::colisiona(Colisionable* colisionable, tipoDeSprite* tipoColision) {
	bool colisiona = false;
	int puntos;
	for (std::list<Colisionable*>::iterator it = listaColisionables.begin();
										it != listaColisionables.end(); ++it) {
		if (((*it)->obtenerInsercion() != colisionable->obtenerInsercion()))
			if (colisionan(colisionable->obtenerInsercion(),
							(*it)->obtenerInsercion())) {
				colisiona = true;
				*tipoColision = (*it)->consultarTipo();
				if (colisionable->estaAtacando())
					puntos = (*it)->recibirDanioDe(colisionable);
				  //  colisionable->sumarPuntos(puntos);
			}
	}
	return colisiona;
}


Colisionable* Colisionador::levantarSiHay(Colisionable* jugador) {
	Colisionable* levantable = NULL;
	for (std::list<Colisionable*>::iterator it = listaLevantables.begin();
										it != listaLevantables.end(); ++it) {
		if (((*it)->obtenerInsercion() != jugador->obtenerInsercion()))
			if (colisionan(jugador->obtenerInsercion(),
							(*it)->obtenerInsercion())) {
				levantable = (*it);
				levantable->desaparecer();
			}
	}
	return levantable;
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

