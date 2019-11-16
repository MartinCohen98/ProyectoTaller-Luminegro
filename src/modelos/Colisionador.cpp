#include "Colisionador.h"

Colisionador::Colisionador() {}


void Colisionador::agregarEncuadre(Encuadre* encuadre) {
	listaEncuadres.push_front(encuadre);
}


void Colisionador::vaciar() {
	while (!listaEncuadres.empty())
		listaEncuadres.pop_front();
}


bool Colisionador::colisiona(Encuadre* encuadre) {
	bool colisiona = false;
	for (std::list<Encuadre*>::iterator it = listaEncuadres.begin();
										it != listaEncuadres.end(); ++it) {
		if (((*it) != encuadre) && !colisiona)
			colisiona = colisionan(encuadre, *it);
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
	if ((unaPosicionY + 5 > otraPosicionY - 5) &&
			(unaPosicionY - 5 < otraPosicionY + 5))
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

