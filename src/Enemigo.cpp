#include "Enemigo.h"

Enemigo::Enemigo(Renderizador *renderizador, int posXinicial, int posYinicial, const char* path){
	posicionX = posXinicial;
	posicionY = posYinicial;
	ancho = 120;
	alto = 240;
	estado = new EstadoEnemigoParado(0,0,47,78);
	dadoVuelta = false;
	contactoVisual = false;
	modoBusqueda = false;
	sprite.cargar(path, Imagen::TIPO_PERSONAJE);
	insercion.modificar(posicionX, posicionY, ancho, alto);
	textura.texturizar(renderizador, sprite);
	textura.copiarseEn(renderizador, estado->obtenerSprite(), insercion);
}

void Enemigo::avanzar() {
	dadoVuelta = false;
	estado = estado->avanzar();
	moverEnX(5);
}

void Enemigo::parar() {
	estado = estado->parar();
}

void Enemigo::retroceder() {
	dadoVuelta = true;
	estado = estado->avanzar();
	moverEnX(-5);
}

void Enemigo::subir() {
	if (posicionY > 180) {
		estado = estado->avanzar();
		moverEnY(-5);
	} else {
		estado = estado->parar();
	}
}

void Enemigo::bajar() {
	if (posicionY < 320) {
		estado = estado->avanzar();
		moverEnY(5);
	} else {
		estado = estado->parar();
	}
}

void Enemigo::agacharse() {
	estado = estado->agacharse();
}

int Enemigo::moverEnY(int nuevoY) {
	int error = 0;
	posicionY = posicionY + nuevoY;
	return error;
}

void Enemigo::actualizar(Renderizador *renderizador) {
	insercion.modificar(posicionX, posicionY, ancho, alto);
	if (!dadoVuelta) {
		textura.copiarseEn(renderizador, estado->obtenerSprite(), insercion);
	} else {
		textura.copiarseInvertidoEn(renderizador,
					estado->obtenerSprite(), insercion);
	}
}

void Enemigo::actualizarRetroceso() {
	posicionX = posicionX - 12;
}

void Enemigo::moverEnX(int movimiento) {
	posicionX = posicionX + movimiento;
}

Enemigo::~Enemigo(){
	delete estado;
}
