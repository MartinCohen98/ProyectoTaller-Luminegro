#include "ControlJugadoresModelo.h"

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

    if (conectado) {
        switch (mensaje->get()) {
            case Right:
                //Avanzar
                jugadores[numeroDeJugador]->avanzar();
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
         }
      }
      else {
            jugadores[numeroDeJugador]->congelar();
        }
}


void ControlJugadoresModelo::realizarMovimientos(FondoModelo* fondo) {
	for (int i = 0; i < cantidad; i++){
		jugadores[i]->realizarMovimientos(fondo);
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


ControlJugadoresModelo::~ControlJugadoresModelo() {
	for (int i = 0; i < cantidad; i++) {
		delete jugadores[i];
	}
	delete[] jugadores;
}

