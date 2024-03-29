#include "Modelo.h"

Modelo::Modelo(pugi::xml_document* archiConfig, int cantidadDeJugadores) {
	Logger::Log *logueador  =  Logger::Log::ObtenerInstancia();

	nivelActual = 1;
	archivoConfiguracion = archiConfig;
	cantidadJugadores = cantidadDeJugadores;

	colisionador = new Colisionador();

	fondo = new FondoModelo(archivoConfiguracion, nivelActual);

	protagonistas = new ControlJugadoresModelo(archivoConfiguracion, cantidadJugadores);

	logueador->Debug("Creando enemigos y asignándoles su comportamiento básico");
	enemigos = new ControlEnemigosModelo(nivelActual, fondo);

	logueador->Debug("Creando controlador de objetos y asignándoles su posición inicial");
	objetos = new ControlObjetosModelo(archivoConfiguracion, fondo->obtenerAncho(), nivelActual);

	llenarColisionador();

	enemigos->movimientosIniciales();

	enemigos->buscarObjetivos(protagonistas);
}


int Modelo::obtenerCantidadDeEntidades() {
	return (cantidadJugadores + enemigos->obtenerCantidad() + objetos->obtenerCantidad());
}


void Modelo::procesarInputDeJugador(MensajeCliente* mensaje, int jugador) {
	protagonistas->procesarInput(mensaje, jugador);
}


void Modelo::realzarMovimientos() {

	if(protagonistas->consultarMatar()){
		protagonistas->matados();
		protagonistas->dejarDeMatar();
	}
	if(protagonistas->consultarGolpear()){
		enemigos->golpear();
		protagonistas->dejarDeGolpear();
	}
	protagonistas->realizarMovimientos(fondo, colisionador);
	enemigos->buscarObjetivos(protagonistas);
	enemigos->realizarMovimientos(protagonistas, colisionador);
	objetos->actualizarPosiciones();
	objetos->actualizar();

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

	delete colisionador;
	delete fondo;
	delete enemigos;
	delete objetos;

	colisionador = new Colisionador();

	nivelActual++;
	fondo = new FondoModelo(archivoConfiguracion, nivelActual);

	//protagonistas = new ControlJugadoresModelo(archivoConfiguracion, cantidadJugadores);
    protagonistas->asignarPosicionesInicioNivel();
	logueador->Debug("Creando enemigos y asignándoles su comportamiento básico");
	enemigos = new ControlEnemigosModelo(nivelActual, fondo);

	logueador->Debug("Creando controlador de objetos y asignándoles su posición inicial");
	objetos = new ControlObjetosModelo(archivoConfiguracion, fondo->obtenerAncho(), nivelActual);

	llenarColisionador();

	enemigos->movimientosIniciales();

	enemigos->buscarObjetivos(protagonistas);
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


bool Modelo::estanTodosMuertos() {
	return protagonistas->consultarTodosMuertos();
}


void Modelo::llenarColisionador() {
	protagonistas->agregarJugadoresEnColisionador(colisionador);
	enemigos->agregarEnemigosEnColisionador(colisionador);
	objetos->agregarObjetosEnColisionador(colisionador);
}


Modelo::~Modelo() {
	if (fondo != NULL)
		delete fondo;
	if (protagonistas != NULL)
		delete protagonistas;
	if (enemigos != NULL)
		delete enemigos;
	if (objetos != NULL)
		delete objetos;
	if (colisionador != NULL)
		delete colisionador;
}

