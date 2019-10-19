#include "ControlEnemigosModelo.h"

ControlEnemigosModelo::ControlEnemigosModelo(int nivel) {
	enemigosCantidad = 6;

	enemigos = new EnemigoModelo*[enemigosCantidad];

	if (nivel == 1){
		enemigos[0] = new EnemigoModelo(1000, 220);
		enemigos[1] = new EnemigoModelo(500, 350);
		enemigos[2] = new EnemigoModelo(3000, 220);
		enemigos[3] = new EnemigoModelo(-500, 350);
		enemigos[4] = new EnemigoModelo(5000, 220);
		enemigos[5] = new EnemigoModelo(7000, 220);
	}

	if (nivel == 2){
		enemigos[0] = new EnemigoModelo(750, 220);
		enemigos[1] = new EnemigoModelo(700, 350);
		enemigos[2] = new EnemigoModelo(2500, 220);
		enemigos[3] = new EnemigoModelo(-300, 350);
		enemigos[4] = new EnemigoModelo(4000, 220);
		enemigos[5] = new EnemigoModelo(5500, 220);
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

void ControlEnemigosModelo::realizarMovimientos(){
	enemigos[0]->retroceder();
	enemigos[1]->avanzar();
	enemigos[2]->retroceder();
	enemigos[3]->avanzar();
	enemigos[4]->retroceder();
	enemigos[5]->retroceder();
}

ControlEnemigosModelo::~ControlEnemigosModelo() {
	// TODO Auto-generated destructor stub
}

