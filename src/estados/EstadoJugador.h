#ifndef SRC_ESTADOJUGADOR_H_
#define SRC_ESTADOJUGADOR_H_

#include "../grafica/Encuadre.h"
#include "../comunicacion/MensajeServidor.h"

enum tipoDeArma {desarmado,
	       cuchillo, tubo};

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
    virtual EstadoJugador* serGolpeado();
	virtual bool puedeMoverse();
	virtual bool estaSaltando();
	virtual int obtenerElevacion();
	virtual int obtenerDanio();
	int obtenerAlto();
	int obtenerAncho();
	virtual ~EstadoJugador();

protected:
	Encuadre frameActual;
	int alto;
	int ancho;
	tipoDeSprite tipo;
	tipoDeArma arma;
};

#endif /* SRC_ESTADOJUGADOR_H_ */
