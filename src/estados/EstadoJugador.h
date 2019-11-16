#ifndef SRC_ESTADOJUGADOR_H_
#define SRC_ESTADOJUGADOR_H_

#include "../grafica/Encuadre.h"
#include "../comunicacion/MensajeServidor.h"

class EstadoJugador {

public:
	EstadoJugador();
	EstadoJugador(int ancho,int alto);
	Encuadre obtenerSprite();
	virtual EstadoJugador* avanzar();
	virtual EstadoJugador* parar();
	virtual EstadoJugador* agacharse();
	virtual EstadoJugador* pegar();
	virtual EstadoJugador* saltar();
    virtual EstadoJugador* congelarse();
    virtual EstadoJugador* morir();
    virtual EstadoJugador* acuchillar();
    virtual EstadoJugador* apalear();
	virtual bool puedeMoverse();
	virtual bool estaSaltando();
	virtual int obtenerElevacion();
	int obtenerAlto();
	int obtenerAncho();
	virtual ~EstadoJugador();

protected:
	Encuadre frameActual;
	int alto;
	int ancho;
	tipoDeSprite tipo;
};

#endif /* SRC_ESTADOJUGADOR_H_ */
