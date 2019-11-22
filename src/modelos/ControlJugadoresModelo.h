#ifndef SRC_MODELOS_CONTROLJUGADORESMODELO_H_
#define SRC_MODELOS_CONTROLJUGADORESMODELO_H_

#include "JugadorModelo.h"

class ControlJugadoresModelo {

private:
	JugadorModelo** jugadores;
	int cantidadJugadores;
	bool matar;
	bool golpear;

public:
	ControlJugadoresModelo(pugi::xml_document *archiConfig, int cantidad);
	void procesarInput(MensajeCliente* mensaje, int numeroDeJugador);
	void realizarMovimientos(FondoModelo* fondo, Colisionador* colisionador);
	void movidaDePantalla(FondoModelo* fondo);
	void generarMensajes(MensajeServidor* mensajes, int* mensajeActual);
	bool llegaronAlFin(FondoModelo* fondo);
	bool verificarRezagado(FondoModelo* fondo);
	void desconectar(int jugador);
	void conectar(int jugador);
	void desaparecer(int jugador);
	bool consultarMatar();
	bool consultarGolpear();
	void dejarDeMatar();
	void dejarDeGolpear();
	int consultarCantidadJugadores();
	JugadorModelo* darJugador(int i);
	void agregarJugadoresEnColisionador(Colisionador* colisionador);
    void generarMensajesEstado(MensajeEstadoJugador *estadosJugadores);
	virtual ~ControlJugadoresModelo();
};

#endif /* SRC_MODELOS_CONTROLJUGADORESMODELO_H_ */
