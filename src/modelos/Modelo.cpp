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


void Modelo::procesarInputDeJugador(MensajeCliente* mensaje, int jugador) {
	protagonistas->procesarInput(mensaje, jugador);
}


void Modelo::realzarMovimientos() {
	if (protagonistas->consultarMatar()) {
		enemigos->matar();
	}

	protagonistas->realizarMovimientos(fondo);
	enemigos->realizarMovimientos(atacante, protagonistas);

	if (fondo->seMovio()) {
		protagonistas->movidaDePantalla(fondo);
		enemigos->movidaDePantalla();
		objetos->movidaDePantalla();
	}
}


void Modelo::generarMensajesServidor(MensajeServidor* mensajes) {

	int mensajeActual = 0;

	fondo->generarMensajes(mensajes, &mensajeActual);
	protagonistas->generarMensajes(mensajes, &mensajeActual);
	enemigos->generarMensajes(mensajes, &mensajeActual);
	objetos->generarMensajes(mensajes, &mensajeActual);
}


bool Modelo::nivelTerminado() {
	return (protagonistas->llegaronAlFin(fondo));
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


void Modelo::desaparecerJugador(int jugador) {
	protagonistas->desaparecer(jugador);
}


void Modelo::desconectarJugador(int jugador) {
	protagonistas->desconectar(jugador);
}


void Modelo::conectarJugador(int jugador) {
	protagonistas->conectar(jugador);
}


Modelo::~Modelo() {}

