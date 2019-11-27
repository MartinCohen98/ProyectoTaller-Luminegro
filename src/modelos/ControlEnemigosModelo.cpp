#include "ControlEnemigosModelo.h"

ControlEnemigosModelo::ControlEnemigosModelo(int nivel, FondoModelo* fondo) {
	enemigosCantidad = 8;

	enemigos = new EnemigoModelo*[enemigosCantidad];

	if (nivel == 1){
		enemigos[0] = new EnemigoModelo(1900, 250, Enemigo3, fondo);
		enemigos[1] = new EnemigoModelo(1000, 320, Enemigo2, fondo);
		enemigos[2] = new EnemigoModelo(2700, 220, Enemigo1, fondo);
		enemigos[3] = new EnemigoModelo(-400, 300, Enemigo3, fondo);
		enemigos[4] = new EnemigoModelo(3000, 220, Enemigo2, fondo);
		enemigos[5] = new EnemigoModelo(3500, 280, Enemigo1, fondo);
		enemigos[6] = new EnemigoModelo(4200, 220, Enemigo2, fondo);
		enemigos[7] = new EnemigoModelo(4700, 250, Enemigo3, fondo);
	}
	if (nivel == 2) {
		enemigos[0] = new EnemigoModelo(1000, 250, Enemigo3, fondo);
		enemigos[1] = new EnemigoModelo(1500, 320, Enemigo2, fondo);
		enemigos[2] = new EnemigoModelo(2000, 220, Enemigo1, fondo);
		enemigos[3] = new EnemigoModelo(-400, 320, Enemigo1, fondo);
		enemigos[4] = new EnemigoModelo(2500, 250, Enemigo2, fondo);
		enemigos[5] = new EnemigoModelo(3000, 320, Enemigo3, fondo);
		enemigos[6] = new EnemigoModelo(3500, 280, Enemigo2, fondo);
		enemigos[7] = new EnemigoJefeModelo(4000, 220, fondo);
	}
	ciclosDeBusqueda = 0;
}

int ControlEnemigosModelo::obtenerCantidad() {
	return enemigosCantidad;
}

void ControlEnemigosModelo::movidaDePantalla() {
	for (int i = 0; i < enemigosCantidad; i++) {
		enemigos[i]->retrocesoDePantalla();
	}
}

int ControlEnemigosModelo::calcularDistancia(JugadorModelo *protagonista,
		EnemigoModelo *enemigo) {
	int x1, x2, y1, y2;
	x1 = protagonista->darPosicionX();
	y1 = protagonista->darPosicionY();
	x2 = enemigo->darPosicionX();
	y2 = enemigo->darPosicionY();
	return sqrt(((x1 - x2) ^ 2) + ((y1 - y2) ^ 2));
}

bool ControlEnemigosModelo::consultarTodosMuertos() {
	bool todosMuertos = false;
	int j = 0;
	for (int i = 0; i < enemigosCantidad; i++)
		if (!enemigos[i]->estaVivo())
			j++;
	if (j == enemigosCantidad)
		todosMuertos = true;
	return todosMuertos;
}

EnemigoModelo* ControlEnemigosModelo::darEnemigo(int j) {
	return enemigos[j];
}

void ControlEnemigosModelo::realizarMovimientos(
		ControlJugadoresModelo *jugadores, Colisionador* colisionador) {

	JugadorModelo* jugador;
	for (int i = 0; i < enemigosCantidad; i++) {
		jugador = enemigos[i]->consultarObjetivo();
	    int distancia = calcularDistancia(jugador, enemigos[i]);
	    accionDeEnemigo modo=enemigos[i]->consultarModo();
	    if (distancia<200 & (modo==Patrullando) & !(enemigos[i]->consultarEsAtacante())){
	      enemigos[i]->cambiarModo(Atacando);
	      enemigos[i]->ponerAtacante();
	    }
		enemigos[i]->verificarMuerte();
		enemigos[i]->guardarPosicionesActuales();
		enemigos[i]->realizarMovimientos(colisionador);
	};
}

void ControlEnemigosModelo::movimientosIniciales() {

	enemigos[0]->retroceder();
	enemigos[1]->avanzar();
	enemigos[2]->retroceder();
	enemigos[3]->avanzar();
	enemigos[4]->retroceder();
	enemigos[5]->retroceder();
	for (int i = 0; i < enemigosCantidad; i++)
		enemigos[i]->cambiarModo(Detenido);
}

void ControlEnemigosModelo::buscarObjetivos(ControlJugadoresModelo *jugadores) {
	EnemigoModelo *enemigo;
	JugadorModelo *jugador;
	int distancia, distAux;
	int i, j;

	if (ciclosDeBusqueda == 20)
		ciclosDeBusqueda = 0;

	if (jugadores->consultarCantidadJugadores() > 1 & ciclosDeBusqueda == 0) {
		for (i = 0; i < enemigosCantidad; i++) {
			distAux = 0;
			int jugadorObjetivo;
			for (j = 0; j < (jugadores->consultarCantidadJugadores()); j++) {
				jugador = jugadores->darJugador(j);
				if (j > 0)
					distAux = distancia;
				distancia = calcularDistancia(jugador, darEnemigo(i));
				if (j == 0)
					distAux = distancia;
				if (distancia <= distAux & !(jugador->consultarDerrotado())
						& !(jugador->estaDesconectado()))
					jugadorObjetivo = j;
			}
			enemigo = darEnemigo(i);
			enemigo->asignarObjetivo(jugadores->darJugador(jugadorObjetivo));
			enemigo->modificarJugadorObjetivo(jugadorObjetivo);
		}
	}

	if (jugadores->consultarCantidadJugadores() == 1 & ciclosDeBusqueda == 0) {
		for (i = 0; i < enemigosCantidad; i++) {
			enemigo = darEnemigo(i);
			enemigo->asignarObjetivo(jugadores->darJugador(0));
		}
	}

	ciclosDeBusqueda++;
}

void ControlEnemigosModelo::matar() {
	for (int i = 0; i < enemigosCantidad; i++)
		enemigos[i]->morir();
}

void ControlEnemigosModelo::golpear() {
	for (int i = 0; i < enemigosCantidad; i++)
		enemigos[i]->pegar();
}

void ControlEnemigosModelo::generarMensajes(MensajeServidor* mensajes,
		int* mensajeActual) {
	for (int i = 0; i < enemigosCantidad; i++) {
		enemigos[i]->generarMensaje(mensajes, mensajeActual);
	}
}

void ControlEnemigosModelo::agregarEnemigosEnColisionador(
		Colisionador* colisionador) {
	for (int i = 0; i < enemigosCantidad; i++) {
		colisionador->agregarColisionable(enemigos[i]);
	}
}

ControlEnemigosModelo::~ControlEnemigosModelo() {
	for (int i = 0; i < enemigosCantidad; i++) {
		delete enemigos[i];
	}
	delete[] enemigos;
}

