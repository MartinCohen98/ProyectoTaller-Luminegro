#ifndef SRC_CONTROLENEMIGOSMODELO_H_
#define SRC_CONTROLENEMIGOSMODELO_H_

#include "EnemigoJefeModelo.h"
#include "JugadorModelo.h"
#include "ControlJugadoresModelo.h"

class ControlEnemigosModelo {

private:
	EnemigoModelo **enemigos;
	int enemigosCantidad;
	int ciclosDeBusqueda;

public:
	ControlEnemigosModelo(int nivel,FondoModelo* fondo);
	int obtenerCantidad();
	void realizarMovimientos(ControlJugadoresModelo *jugadores,
												Colisionador* colisionador);
	void movimientosIniciales();
	void buscarObjetivos(ControlJugadoresModelo *jugadores);
	void matar();
	void golpear();
	void movidaDePantalla();
	int calcularDistancia(JugadorModelo *protagonista,EnemigoModelo *enemigo);
	bool consultarTodosMuertos();
	EnemigoModelo* darEnemigo(int j);
	void generarMensajes(MensajeServidor* mensajes, int* mensajeActual);
	void agregarEnemigosEnColisionador(Colisionador* colisionador);
	virtual ~ControlEnemigosModelo();
};

#endif /* SRC_CONTROLENEMIGOSMODELO_H_ */
