#include "Modelo.h"

Modelo::Modelo(pugi::xml_document* archiConfig, int cantidadDeJugadores) {
	Logger::Log *logueador  =  Logger::Log::ObtenerInstancia();

	nivelActual = 1;
	archivoConfiguracion = archiConfig;
	cantidadJugadores = cantidadDeJugadores;

	fondo = new FondoModelo(archivoConfiguracion, nivelActual);

	protagonistas = new ControlJugadoresModelo(archivoConfiguracion, cantidadJugadores);

	logueador->Debug("Creando enemigos y asignándoles su comportamiento básico");
	enemigos = new ControlEnemigosModelo(nivelActual);

	logueador->Debug("Creando controlador de objetos y asignándoles su posición inicial");
	objetos = new ControlObjetosModelo(archivoConfiguracion, fondo->obtenerAncho(), nivelActual);

	enemigos->movimientosIniciales();

	atacante = enemigos->buscarObjetivo(protagonistas);
}


int Modelo::obtenerCantidadDeEntidades() {
	return (cantidadJugadores + enemigos->obtenerCantidad() + objetos->obtenerCantidad());
}


void Modelo::realzarMovimientos() {
	protagonistas->realizarMovimientos(fondo);
	enemigos->realizarMovimientos(atacante, protagonistas);

	if (fondo->seMovio()) {
		protagonistas->movidaDePantalla(fondo);
		enemigos->movidaDePantalla();
		objetos->movidaDePantalla();
	}
}


void Modelo::pasarNivel() {
	Logger::Log *logueador  =  Logger::Log::ObtenerInstancia();

	delete fondo;
	delete protagonistas;
	delete enemigos;
	delete objetos;

	nivelActual++;
	fondo = new FondoModelo(archivoConfiguracion, nivelActual);

	protagonistas = new ControlJugadoresModelo(archivoConfiguracion, cantidadJugadores);

	logueador->Debug("Creando enemigos y asignándoles su comportamiento básico");
	enemigos = new ControlEnemigosModelo(nivelActual);

	logueador->Debug("Creando controlador de objetos y asignándoles su posición inicial");
	objetos = new ControlObjetosModelo(archivoConfiguracion, fondo->obtenerAncho(), nivelActual);

	enemigos->movimientosIniciales();

	atacante = enemigos->buscarObjetivo(protagonistas);
}


Modelo::~Modelo() {}

