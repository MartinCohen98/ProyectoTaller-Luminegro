#ifndef SRC_MODELOS_MODELO_H_
#define SRC_MODELOS_MODELO_H_

#include "FondoModelo.h"
#include "ControlEnemigosModelo.h"
#include "ControlObjetosModelo.h"

class Modelo {

private:
	int cantidadJugadores;
    pugi::xml_document* archivoConfiguracion;
    FondoModelo* fondo;
    ControlJugadoresModelo* protagonistas;
    ControlEnemigosModelo* enemigos;
    ControlObjetosModelo* objetos;
    Colisionador* colisionador;
    int nivelActual;
    int atacante;

public:
	Modelo(pugi::xml_document* archiConfig, int cantidadDeJugadores);
	int obtenerCantidadDeEntidades();
	void procesarInputDeJugador(MensajeCliente* mensaje, int jugador);
	void realzarMovimientos();
	void generarMensajesServidor(MensajeServidor* mensajes);
	bool nivelTerminado();
	void pasarNivel();
	void desaparecerJugador(int jugador);
	void desconectarJugador(int jugador);
	void conectarJugador(int jugador);
	virtual ~Modelo();

private:
	void llenarColisionador();
};

#endif /* SRC_MODELOS_MODELO_H_ */
