#include "ControlJugadoresModelo.h"
#include <iostream>

ControlJugadoresModelo::ControlJugadoresModelo(pugi::xml_document *archiConfig,
					int cantidadJugadores) {
	jugadores = new JugadorModelo*[cantidadJugadores];
	cantidad = cantidadJugadores;
	int posXinic[4] = {100,100,0,200};
	int posYinic[4] = {175,275,225,225};

	for (int i = 0; i < cantidad; i++) {
		jugadores[i] = new JugadorModelo(archiConfig, posXinic[i], posYinic[i]);
	}
}


void ControlJugadoresModelo::procesarInput(MensajeCliente* mensaje,
											int numeroDeJugador) {

        switch (mensaje->get()) {
            case Right:{
                //Avanzar
                if (!jugadores[numeroDeJugador]->estaDesconectado())
                   jugadores[numeroDeJugador]->avanzar();}
                break;
            case Left:
                //Atras
                jugadores[numeroDeJugador]->retroceder();
                break;
            case Up:
                //Arriba
                jugadores[numeroDeJugador]->subir();
                break;
            case Down:
                //Abajo
                jugadores[numeroDeJugador]->bajar();
                break;
            case Jump:
                //Saltar
                jugadores[numeroDeJugador]->saltar();
                break;
            case Crouch:
                //Agacharse
                jugadores[numeroDeJugador]->agacharse();
                break;
            case Hit:
                //Pegar
                jugadores[numeroDeJugador]->pegar();
                break;
            case Disconnect:
                //Desconectado
                jugadores[numeroDeJugador]->congelarse();
                Logger::Log::ObtenerInstancia()->Info(std::string("Se desconetó el jugador " + numeroDeJugador));
                break;
            case Exit:
                //Salir
            	jugadores[numeroDeJugador]->desaparecer();
                Logger::Log::ObtenerInstancia()->Info(std::string("Salió el jugador " + numeroDeJugador));
                break;
            case StopGoingRight:
                //Avanzar
                jugadores[numeroDeJugador]->dejarDeAvanzar();
                break;
            case StopGoingLeft:
                //Atras
                jugadores[numeroDeJugador]->dejarDeRetroceder();
                break;
            case StopGoingUp:
                //Arriba
                jugadores[numeroDeJugador]->dejarDeSubir();
                break;
            case StopGoingDown:
                //Abajo
                jugadores[numeroDeJugador]->dejarDeBajar();
                break;
            case Rise:
                jugadores[numeroDeJugador]->dejarDeAgacharse();
                break;
            case Nothing:
                break;
            case Connect:
                //Conectado
                jugadores[numeroDeJugador]->descongelarse();
                Logger::Log::ObtenerInstancia()->Info(std::string("Se reconectó el jugador " + numeroDeJugador ));

        }
}


void ControlJugadoresModelo::realizarMovimientos(FondoModelo* fondo) {
    bool rezagado = verificarRezagado(fondo);
	for (int i = 0; i < cantidad; i++){
		jugadores[i]->realizarMovimientos(fondo, rezagado);
	}
}


void ControlJugadoresModelo::movidaDePantalla(FondoModelo* fondo) {

    for (int i = 0; i < cantidad; i++) {
		jugadores[i]->movidaDePantalla(fondo);
	}
}


void ControlJugadoresModelo::generarMensajes(MensajeServidor* mensajes,
		int* mensajeActual) {
	for (int i = 0; i < cantidad; i++) {
		jugadores[i]->generarMensaje(mensajes, mensajeActual, i + 1);
	}
}


bool ControlJugadoresModelo::llegaronAlFin(FondoModelo* fondo) {
	bool retorno = false;
	for (int i = 0; i < cantidad; i++) {
		if (jugadores[i]->llegoAlFin(fondo))
			retorno = true;
	}
	return retorno;
}


bool ControlJugadoresModelo::verificarRezagado(FondoModelo* fondo){
    bool rezagado = false;
    for (int i = 0; i < cantidad; i++) {
        if ((jugadores[i]->darPosicionX() <= fondo->darInicioTerreno() - 600)
        		&& !jugadores[i]->estaDesconectado())
            rezagado = true;
       }
    return rezagado;
}


void ControlJugadoresModelo::desconectar(int jugador) {
	jugadores[jugador]->congelarse();
}


void ControlJugadoresModelo::conectar(int jugador) {
	jugadores[jugador]->descongelarse();
}


void ControlJugadoresModelo::desaparecer(int jugador) {
	jugadores[jugador]->desaparecer();
}


ControlJugadoresModelo::~ControlJugadoresModelo() {
	for (int i = 0; i < cantidad; i++) {
		delete jugadores[i];
	}
	delete[] jugadores;
}

