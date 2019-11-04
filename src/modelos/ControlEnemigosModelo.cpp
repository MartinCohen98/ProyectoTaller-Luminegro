#include "ControlEnemigosModelo.h"

ControlEnemigosModelo::ControlEnemigosModelo(int nivel) {
	enemigosCantidad = 6;

	enemigos = new EnemigoModelo*[enemigosCantidad];

	if (nivel == 1){
		enemigos[0] = new EnemigoModelo(1000, 220, Enemigo1);
		enemigos[1] = new EnemigoModelo(500, 320, Enemigo2);
		enemigos[2] = new EnemigoModelo(3000, 220, Enemigo3);
		enemigos[3] = new EnemigoModelo(-500, 320, Enemigo3);
		enemigos[4] = new EnemigoModelo(5000, 220, Enemigo2);
		enemigos[5] = new EnemigoModelo(7000, 220, Enemigo1);
	}

	if (nivel == 2){
		enemigos[0] = new EnemigoModelo(750, 220, Enemigo3);
		enemigos[1] = new EnemigoModelo(700, 320, Enemigo2);
		enemigos[2] = new EnemigoModelo(2500, 220, Enemigo1);
		enemigos[3] = new EnemigoModelo(-300, 320, Enemigo1);
		enemigos[4] = new EnemigoModelo(4000, 220, Enemigo2);
		enemigos[5] = new EnemigoModelo(5500, 220, Enemigo3);
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

int ControlEnemigosModelo::calcularDistancia(int x1, int y1, int x2, int y2){
    return sqrt((x1-x2)^2+(y1-y2)^2);
}

void ControlEnemigosModelo::realizarMovimientos(){
    enemigos[0]->patrullar();
	enemigos[1]->patrullar();
    enemigos[2]->patrullar();
	enemigos[3]->patrullar();
	enemigos[4]->patrullar();
	enemigos[5]->patrullar();
}

void ControlEnemigosModelo::movimientosIniciales(){
    enemigos[0]->retroceder();
    enemigos[1]->avanzar();
    enemigos[2]->retroceder();
    enemigos[3]->avanzar();
    enemigos[4]->retroceder();
    enemigos[5]->retroceder();
}

void ControlEnemigosModelo::buscarObjetivo(){

}

void ControlEnemigosModelo::generarMensajes(MensajeServidor* mensajes, int* mensajeActual) {
	for(int i = 0; i < enemigosCantidad; i++) {
		enemigos[i]->generarMensaje(mensajes, mensajeActual);
	}
}


ControlEnemigosModelo::~ControlEnemigosModelo() {
	// TODO Auto-generated destructor stub
}

