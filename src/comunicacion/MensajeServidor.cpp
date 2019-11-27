#include "MensajeServidor.h"

using namespace std;

MensajeServidor::MensajeServidor() {
	sprite = Jugador1;
	dadoVuelta = false;
	posicionY = 0;
}

void MensajeServidor::generarMensaje(Encuadre* unFrame, Encuadre* unaInsercion, tipoDeSprite tipo) {
	if (unFrame != NULL)
		frame = *unFrame;
	if (unaInsercion != NULL) {
		insercion = *unaInsercion;
	}

	posicionY = insercion.getY() + insercion.getAlto();
	sprite = tipo;
	dadoVuelta = false;
}


void MensajeServidor::darVuelta() {
	dadoVuelta = true;
}


void MensajeServidor::agregarPosicionY(int posicion) {
	posicionY = posicion;
}


Encuadre* MensajeServidor::obtenerFrame() {
	return &frame;
}


Encuadre* MensajeServidor::obtenerInsercion() {
	return &insercion;
}


tipoDeSprite MensajeServidor::obtenerTipoDeSprite() {
	return sprite;
}


int MensajeServidor::obtenerPosicionY() {
	return posicionY;
}


bool MensajeServidor::estaDadoVuelta() {
	return dadoVuelta;
}


bool MensajeServidor::operator <(const MensajeServidor & mensaje) const {
	return (posicionY < mensaje.posicionY);
}


void MensajeServidor::setSonidoEjecutarGolpeTiro(bool valor) {
    ejecutarSonidoGolpeTiro = valor;
}


bool MensajeServidor::getSonidoEjecutarGolpeTiro() {
    return ejecutarSonidoGolpeTiro;
}


void MensajeServidor::setSonidoEjecutarGolpeImpacto(bool valor) {
    ejecutarSonidoGolpeImpacto = valor;
}


bool MensajeServidor::getSonidoEjecutarGolpeImpacto() {
    return ejecutarSonidoGolpeImpacto;
}


void MensajeServidor::setSonidoEjecutarSalto(bool valor) {
    ejecutarSonidoSalto = valor;
}


bool MensajeServidor::getSonidoEjecutarSalto() {
    return ejecutarSonidoSalto;
}


void MensajeServidor::setSonidoEjecutarCaida(bool valor) {
    ejecutarSonidoCaida = valor;
}


bool MensajeServidor::getSonidoEjecutarCaida() {
    return ejecutarSonidoCaida;
}


void MensajeServidor::setSonidoEjecutarDestruccion(bool valor) {
    ejecutarSonidoDestruccion = valor;
}

bool MensajeServidor::getSonidoEjecutarDestruccion() {
    return ejecutarSonidoDestruccion;
}


MensajeServidor::~MensajeServidor() {}

InfoJugador MensajeServidor::getInfoJugador() {
    return infoJugador;
}

void MensajeServidor::setInfoJugador(InfoJugador info) {
    infoJugador = info;
}


