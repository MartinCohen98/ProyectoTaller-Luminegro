#include "ControlEnemigosModelo.h"

ControlEnemigosModelo::ControlEnemigosModelo(int nivel, FondoModelo* fondo) {
	enemigosCantidad = 8;

	enemigos = new EnemigoModelo*[enemigosCantidad];

	if (nivel == 1){
		enemigos[0] = new EnemigoModelo(2100, 250, Enemigo1, fondo);
		enemigos[1] = new EnemigoModelo(1000, 320, Enemigo2, fondo);
		enemigos[2] = new EnemigoModelo(2700, 220, Enemigo3, fondo);
		enemigos[3] = new EnemigoModelo(-400, 300, Enemigo3, fondo);
		enemigos[4] = new EnemigoModelo(3000, 220, Enemigo2, fondo);
		enemigos[5] = new EnemigoModelo(3500, 280, Enemigo1, fondo);
		enemigos[6] = new EnemigoModelo(4000, 220, Enemigo2, fondo);
		enemigos[7] = new EnemigoModelo(4500, 250, Enemigo3, fondo);
	}

	if (nivel == 2){
		enemigos[0] = new EnemigoModelo(1000, 250, Enemigo3, fondo);
		enemigos[1] = new EnemigoModelo(1500, 320, Enemigo2, fondo);
		enemigos[2] = new EnemigoModelo(2000, 220, Enemigo1, fondo);
		enemigos[3] = new EnemigoModelo(-300, 320, Enemigo3, fondo);
		enemigos[4] = new EnemigoModelo(2500, 250, Enemigo2, fondo);
		enemigos[5] = new EnemigoModelo(3000, 320, Enemigo1, fondo);
		enemigos[6] = new EnemigoModelo(3500, 280, Enemigo2, fondo);
	//	enemigos[7] = new EnemigoModelo(4000, 280, Enemigo2, fondo);
		enemigos[7] = new EnemigoJefeModelo(4000, 220, fondo);
	}
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
											EnemigoModelo *enemigo){
	int x1,x2,y1,y2;
	x1=protagonista->darPosicionX();
	y1=protagonista->darPosicionY();
	x2=enemigo->darPosicionX();
	y2=enemigo->darPosicionY();
	return sqrt(((x1-x2)^2)+((y1-y2)^2));
}

EnemigoModelo* ControlEnemigosModelo::darEnemigo(int j){
	return enemigos[j];
}

void ControlEnemigosModelo::realizarMovimientos(ControlJugadoresModelo *jugadores,
										Colisionador* colisionador) {

/*	JugadorModelo* jugador;
	jugador = &(enemigos[0]->consultarObjetivo);
	int distancia = calcularDistancia(enemigos[0], jugador);
	if (distancia<200)
		enemigos[0]->cambiarModo(Atacando);*/
    for (int i = 0;i<enemigosCantidad;i++) {
    	enemigos[i]->verificarMuerte();
		enemigos[i]->guardarPosicionesActuales();
		enemigos[i]->realizarMovimientos(colisionador);
    };
}

void ControlEnemigosModelo::movimientosIniciales(){

    enemigos[0]->atacar();
    enemigos[1]->avanzar();
    enemigos[2]->retroceder();
    enemigos[3]->avanzar();
    enemigos[4]->retroceder();
    enemigos[5]->retroceder();
    for (int i=0;i<enemigosCantidad;i++)
   	   enemigos[i]->cambiarModo(Detenido);
}


void ControlEnemigosModelo::buscarObjetivos(ControlJugadoresModelo *jugadores){
   EnemigoModelo *enemigo;
 /*  int distancia, distAux;
   int i,j;
   for(i = 0; i < (jugadores->consultarCantidadJugadores()); i++){
	distAux = 0;
	int jugadorObjetivo = 0;
	int enemigoAtacante = 0;
	for(j = 0; j < enemigosCantidad; j++){
		distAux=distancia;
		distancia=calcularDistancia(jugadores->darJugador(i),darEnemigo(j));
        if (distancia<distAux){
        	jugadorObjetivo=i;
        	enemigoAtacante=j;
          };
	   };
	enemigo = darEnemigo(enemigoAtacante);
	enemigo->asignarObjetivo(jugadores->darJugador(jugadorObjetivo));
	enemigo->modificarJugadorObjetivo(jugadorObjetivo);
    };*/

   int j=0;
   int cantidadJugadores = jugadores->consultarCantidadJugadores();
   for (int i=0;i<enemigosCantidad;i++){
	   if (j==cantidadJugadores )
		   j=0;
       enemigo = darEnemigo(i);
       enemigo->asignarObjetivo(jugadores->darJugador(j));
       j++;
   }
}

void ControlEnemigosModelo::matar(){
    for(int i = 0;i<enemigosCantidad;i++)
    enemigos[i]->morir();
}

void ControlEnemigosModelo::golpear(){
    for(int i = 0;i<enemigosCantidad;i++)
    enemigos[i]->pegar();
}

void ControlEnemigosModelo::generarMensajes(MensajeServidor* mensajes, int* mensajeActual) {
	for(int i = 0; i < enemigosCantidad; i++) {
		enemigos[i]->generarMensaje(mensajes, mensajeActual);
	}
}


void ControlEnemigosModelo::agregarEnemigosEnColisionador(Colisionador* colisionador) {
	for(int i = 0; i < enemigosCantidad; i++) {
		colisionador->agregarColisionable(enemigos[i]);
	}
}


ControlEnemigosModelo::~ControlEnemigosModelo() {
	for (int i = 0; i < enemigosCantidad; i++) {
		delete enemigos[i];
	}
	delete[] enemigos;
}

