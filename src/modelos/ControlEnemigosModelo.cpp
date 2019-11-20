#include "ControlEnemigosModelo.h"

ControlEnemigosModelo::ControlEnemigosModelo(int nivel) {
	enemigosCantidad = 6;

	enemigos = new EnemigoModelo*[enemigosCantidad];

	if (nivel == 1){
		enemigos[0] = new EnemigoModelo(1000, 220, Enemigo1);
		enemigos[1] = new EnemigoModelo(500, 320, Enemigo2);
		enemigos[2] = new EnemigoModelo(3000, 220, Enemigo3);
		enemigos[3] = new EnemigoJefeModelo(-500, 220);
		enemigos[4] = new EnemigoModelo(5000, 220, Enemigo2);
		enemigos[5] = new EnemigoModelo(7000, 220, Enemigo1);
	}

	if (nivel == 2){
		enemigos[0] = new EnemigoModelo(550, 220, Enemigo3);
		enemigos[1] = new EnemigoModelo(700, 320, Enemigo2);
		enemigos[2] = new EnemigoModelo(2500, 220, Enemigo1);
		enemigos[3] = new EnemigoModelo(-300, 320, Enemigo1);
		enemigos[4] = new EnemigoModelo(4000, 220, Enemigo2);
		enemigos[5] = new EnemigoJefeModelo(5500, 220);
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

void ControlEnemigosModelo::realizarMovimientos(int atacante, ControlJugadoresModelo *jugadores,
										Colisionador* colisionador) {
    int x,y;
    int posicionX,posicionY;
    JugadorModelo *jugador;
    int objetivo;
    int enemigoAtacante = atacante;
    enemigoAtacante = 0;
    objetivo = enemigos[atacante]->consultarJugadorObjetivo();
    jugador=jugadores->darJugador(objetivo);
    x=jugador->darPosicionX();
    y=jugador->darPosicionY();
   for (int i=0;i<enemigosCantidad;i++) {
	   enemigos[i]->guardarPosicionesActuales();
       posicionY=enemigos[i]->darPosicionY();
     //  if (posicionY==250 || posicionY==200 || posicionY==300)
    //       enemigos[i]->pegar();
   //   if (i!=enemigoAtacante)
          enemigos[i]->patrullar();
      enemigos[i]->realizarMovimientos(colisionador);
      };
  // enemigos[enemigoAtacante]->atacar(x,y);
  // enemigos[enemigoAtacante]->realizarMovimientos(colisionador);
}

void ControlEnemigosModelo::movimientosIniciales(){

    enemigos[0]->retroceder();
    enemigos[1]->avanzar();
    enemigos[2]->retroceder();
    enemigos[3]->avanzar();
    enemigos[4]->retroceder();
    enemigos[5]->retroceder();

}

int ControlEnemigosModelo::buscarObjetivo(ControlJugadoresModelo *jugadores){
int jugadorObjetivo = 0;
int enemigoAtacante = 0;
EnemigoModelo *enemigo;
int distancia, distAux;
int i,j;
for(i = 0; i < (jugadores->consultarCantidadJugadores()); i++){
	for(j = 0; j < enemigosCantidad; j++){
		distAux=distancia;
		distancia=calcularDistancia(jugadores->darJugador(i),darEnemigo(j));
        if (distancia<distAux){
        	jugadorObjetivo=i;
        	enemigoAtacante=j;
        };
	};
 };
 enemigo=darEnemigo(enemigoAtacante);
 enemigo->modificarJugadorObjetivo(jugadorObjetivo);
 printf("%d/n", enemigoAtacante);
 return enemigoAtacante;
}

void ControlEnemigosModelo::matar(){
    for(int i=0;i<enemigosCantidad;i++)
    enemigos[i]->morir();
}

void ControlEnemigosModelo::golpear(){
    for(int i=0;i<enemigosCantidad;i++)
    enemigos[i]->serGolpeado();
}

void ControlEnemigosModelo::generarMensajes(MensajeServidor* mensajes, int* mensajeActual) {
	for(int i = 0; i < enemigosCantidad; i++) {
		enemigos[i]->generarMensaje(mensajes, mensajeActual);
	}
}


void ControlEnemigosModelo::agregarEnemigosEnColisionador(Colisionador* colisionador) {
	for(int i = 0; i < enemigosCantidad; i++) {
		colisionador->agregarEntidad(enemigos[i]);
	}
}


ControlEnemigosModelo::~ControlEnemigosModelo() {
	for (int i = 0; i < enemigosCantidad; i++) {
		delete enemigos[i];
	}
	delete[] enemigos;
}

