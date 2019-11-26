#ifndef SRC_ESTADOJUGADOR_H_
#define SRC_ESTADOJUGADOR_H_

#include "../grafica/Encuadre.h"
#include "../comunicacion/MensajeServidor.h"
#include "../modelos/TipoDeArma.h"

class EstadoJugador {


protected:
	Encuadre frameActual;
	int alto;
	int ancho;
	tipoDeSprite tipo;
	tipoDeArma arma;

public:
	EstadoJugador();
	EstadoJugador(int ancho,int alto);
	Encuadre obtenerSprite();
	virtual EstadoJugador* parar();
	virtual EstadoJugador* avanzar();
	virtual EstadoJugador* agacharse();
	virtual EstadoJugador* saltar();
	virtual EstadoJugador* pegar();
    virtual EstadoJugador* acuchillar();
    virtual EstadoJugador* apalear();
    virtual EstadoJugador* serGolpeado();
    virtual EstadoJugador* morir();
    virtual EstadoJugador* congelarse();
	virtual bool estaSaltando();
	virtual bool estaAtacando();
	virtual bool puedeMoverse();
	virtual bool estaPateando();
	virtual bool terminado();
	virtual int obtenerElevacion();
	virtual int obtenerDanio();
	virtual int obtenerPuntosDeGolpe();
	virtual bool estaMuerto();
	void asignarArma(tipoDeArma tipoDeArma);
	virtual int obtenerAlto();
	int obtenerAncho();
	virtual ~EstadoJugador();
};

#endif /* SRC_ESTADOJUGADOR_H_ */
