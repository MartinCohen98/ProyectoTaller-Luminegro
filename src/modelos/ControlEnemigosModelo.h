#ifndef SRC_CONTROLENEMIGOSMODELO_H_
#define SRC_CONTROLENEMIGOSMODELO_H_

#include "../modelos/EnemigoModelo.h"
#include "../modelos/EnemigoJefeModelo.h"
#include "../modelos/JugadorModelo.h"
#include "../modelos/ControlJugadoresModelo.h"

class ControlEnemigosModelo {

private:
	EnemigoModelo **enemigos;
	int enemigosCantidad;

public:
	ControlEnemigosModelo(int nivel);
	int obtenerCantidad();
	void realizarMovimientos(int atacante, ControlJugadoresModelo *jugadores);
	void movimientosIniciales();
	int buscarObjetivo(ControlJugadoresModelo *jugadores);
	void matar();
	void movidaDePantalla();
	int calcularDistancia(JugadorModelo *protagonista,EnemigoModelo *enemigo);
	EnemigoModelo* darEnemigo(int j);
	void generarMensajes(MensajeServidor* mensajes, int* mensajeActual);
	virtual ~ControlEnemigosModelo();
};

#endif /* SRC_CONTROLENEMIGOSMODELO_H_ */
