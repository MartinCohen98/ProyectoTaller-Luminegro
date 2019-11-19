#ifndef SRC_CONTROLENEMIGOSMODELO_H_
#define SRC_CONTROLENEMIGOSMODELO_H_

#include "EnemigoJefeModelo.h"
#include "JugadorModelo.h"
#include "ControlJugadoresModelo.h"

class ControlEnemigosModelo {

private:
	EnemigoModelo **enemigos;
	int enemigosCantidad;

public:
	ControlEnemigosModelo(int nivel);
	int obtenerCantidad();
	void realizarMovimientos(int atacante, ControlJugadoresModelo *jugadores,
												Colisionador* colisionador);
	void movimientosIniciales();
	int buscarObjetivo(ControlJugadoresModelo *jugadores);
	void matar();
	void golpear();
	void movidaDePantalla();
	int calcularDistancia(JugadorModelo *protagonista,EnemigoModelo *enemigo);
	EnemigoModelo* darEnemigo(int j);
	void generarMensajes(MensajeServidor* mensajes, int* mensajeActual);
	void agregarEnemigosEnColisionador(Colisionador* colisionador);
	virtual ~ControlEnemigosModelo();
};

#endif /* SRC_CONTROLENEMIGOSMODELO_H_ */
