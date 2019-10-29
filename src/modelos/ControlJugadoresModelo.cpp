#include "ControlJugadoresModelo.h"
#include <iostream>

ControlJugadoresModelo::ControlJugadoresModelo(pugi::xml_document *archiConfig,
					int cantidadJugadores) {
	jugadores = new JugadorModelo*[cantidadJugadores];
	cantidad = cantidadJugadores;
	for (int i = 0; i < cantidad; i++) {
		jugadores[i] = new JugadorModelo(archiConfig);
	}
}


void ControlJugadoresModelo::procesarInput(MensajeCliente* mensaje,
											int numeroDeJugador, bool conectado) {

   // if (conectado) {
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
                break;
            case Exit:
                //Salir
                // logueador->Info("Se seleccionó salir");
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


        }
    /*  }
      else {
            jugadores[numeroDeJugador]->congelarse();
        }*/
}


void ControlJugadoresModelo::realizarMovimientos(FondoModelo* fondo) {
    bool rezagado = verificarRezagado(fondo);
    bool conectado=true;
	for (int i = 0; i < cantidad; i++){
        if (!jugadores[i]->estaDesconectado())
		  jugadores[i]->realizarMovimientos(fondo, rezagado, conectado);
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
    bool rezagado=false;
    for (int i = 0; i < cantidad; i++) {
        if (jugadores[i]->darPosicion() <= fondo->darInicioTerreno()-600)
            rezagado = true;
       }
    return rezagado;
    }

ControlJugadoresModelo::~ControlJugadoresModelo() {
	for (int i = 0; i < cantidad; i++) {
		delete jugadores[i];
	}
	delete[] jugadores;
}

