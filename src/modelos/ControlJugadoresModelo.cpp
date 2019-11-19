#include "ControlJugadoresModelo.h"
#include <iostream>

ControlJugadoresModelo::ControlJugadoresModelo(pugi::xml_document *archiConfig,
					int cantidad) {
	cantidadJugadores = cantidad;
	jugadores = new JugadorModelo*[cantidadJugadores];
	int posXinic[4] = {100,100,0,200};
	int posYinic[4] = {175,275,225,225};

	for (int i = 0; i < cantidadJugadores; i++) {
		jugadores[i] = new JugadorModelo(archiConfig, posXinic[i], posYinic[i]);
	}
	matar=false;
	golpear=false;
}


void ControlJugadoresModelo::procesarInput(MensajeCliente* mensaje,
											int numeroDeJugador){
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
            case Hit:{
            	//Atacar
            	tipoDeArma arma=jugadores[numeroDeJugador]->consultarArma();
                switch(arma){
                    case (desarmado):
		                jugadores[numeroDeJugador]->pegar();
                        break;
                    case (cuchillo):
                        jugadores[numeroDeJugador]->acuchillar();
                        break;
                    case (tubo):
	                	jugadores[numeroDeJugador]->apalear();
                    	break;
                    }
                break;
               }
            case Disconnect:
                // Desconectado
                jugadores[numeroDeJugador]->congelarse();
                {
                    std::string mensajeInfo = "Se desconectó el jugador ";
                    mensajeInfo.append(std::to_string(numeroDeJugador));
                    Logger::Log::ObtenerInstancia()->Info(mensajeInfo);
                }
                break;
            case Test:
                // Modo test
                if(jugadores[numeroDeJugador]->consultarModoTest())
                    jugadores[numeroDeJugador]->desactivarModoTest();
                else
                    jugadores[numeroDeJugador]->activarModoTest();
                break;
            case Kill:
                // Matar a todos los enemigos
                matar=true;
            	//golpear=true;
                break;
            case Exit:
                // Salir
            	jugadores[numeroDeJugador]->desaparecer();
                {
                    std::string mensajeInfo = "Salió el jugador ";
                    mensajeInfo.append( std::to_string(numeroDeJugador) );
                    Logger::Log::ObtenerInstancia()->Info(mensajeInfo);
                }
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
	for (int i = 0; i < cantidadJugadores; i++){
		jugadores[i]->realizarMovimientos(fondo, rezagado);
	}
}


void ControlJugadoresModelo::movidaDePantalla(FondoModelo* fondo) {

    for (int i = 0; i < cantidadJugadores; i++) {
		jugadores[i]->movidaDePantalla(fondo);
	}
}


void ControlJugadoresModelo::generarMensajes(MensajeServidor* mensajes,
		int* mensajeActual) {
	for (int i = 0; i < cantidadJugadores; i++) {
		jugadores[i]->generarMensaje(mensajes, mensajeActual, i + 1);
	}
}


bool ControlJugadoresModelo::llegaronAlFin(FondoModelo* fondo) {
	bool retorno = false;
	int i,j=0;
	for (i = 0; i < cantidadJugadores; i++) {
		if (jugadores[i]->estaDesconectado() || jugadores[i]->llegoAlFin(fondo))
		    j++;
	}
	if (j==cantidadJugadores)
        retorno = true;
	return retorno;
}


bool ControlJugadoresModelo::verificarRezagado(FondoModelo* fondo){
    bool rezagado = false;
    for (int i = 0; i < cantidadJugadores; i++) {
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

bool ControlJugadoresModelo::consultarMatar(){
    return matar;
}

bool ControlJugadoresModelo::consultarGolpear(){
    return golpear;
}

void ControlJugadoresModelo::dejarDeMatar(){
	matar = false;
}

void ControlJugadoresModelo::dejarDeGolpear(){
	golpear = false;
}

int ControlJugadoresModelo::consultarCantidadJugadores(){
	return cantidadJugadores;
}

JugadorModelo* ControlJugadoresModelo::darJugador(int i){
	return jugadores[i];
}


void ControlJugadoresModelo::agregarJugadoresEnColisionador(Colisionador* colisionador) {
	for (int i = 0; i < cantidadJugadores; i++) {
		jugadores[i]->agregarEnColisionador(colisionador);
	}
}


ControlJugadoresModelo::~ControlJugadoresModelo() {
	for (int i = 0; i < cantidadJugadores; i++) {
		delete jugadores[i];
	}
	delete[] jugadores;
}

