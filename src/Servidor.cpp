#include "Servidor.h"

using namespace std;

Servidor::Servidor(int cantidadDeJugadores, char* puerto) {
	jugadores = cantidadDeJugadores;
	socketsDeClientes = new Socket[cantidadDeJugadores];
	int resultadoAccion = socketAceptador.servidorInicializar(puerto);
	if (resultadoAccion == 1) {
		// Ya fue logueado en la clase
		return;
	}

	// (INICIO) ESTO SE TIENE QUE LLAMAR CON UNA INSTANCIA NUEVA DE "Socket" POR CADA JUGADOR QUE SE NOS CONECTA
	for (int i = 0; i < jugadores; i++) {
		resultadoAccion = socketAceptador.esperarYAceptarCliente(&socketsDeClientes[i]);
		if (resultadoAccion == EXIT_FAILURE) {
			// Ya fue logueado en la clase
			socketAceptador.cerrar();
			return;
		}
	}
}

void Servidor::correr(pugi::xml_document* archiConfig) {
	Logger::Log *logueador  =  Logger::Log::ObtenerInstancia();

	bool nivelTerminado;


	for (int nivel = 1; nivel <= 2; nivel++) {

        string nivelNodeName = "nivel";
        nivelNodeName.append( to_string(nivel) );

		nivelTerminado = false;

		logueador->Info("Iniciando nivel: "+ nivelNodeName);
		logueador->Debug("Leyendo del XML la ubicación de los BMPs de los fondos y el ancho del terreno");
		FondoModelo fondo(archiConfig, nivel);

		JugadorModelo protagonista(archiConfig);

		logueador->Debug("Creando enemigos y asignándoles su comportamiento básico");
		ControlEnemigosModelo controlEnemigos(nivel);

		logueador->Debug("Creando controlador de objetos y asignándoles su posición inicial");
		ControlObjetosModelo controlObjetos(archiConfig, fondo.obtenerAncho(), nivel);

		enviarCantidadDeRecieves(&controlEnemigos, &controlObjetos);

		while (!nivelTerminado) {
			recibirInput(&protagonista);

			protagonista.realizarMovimientos(&fondo);
			controlEnemigos.realizarMovimientos();

			if (fondo.seMovio()) {
				controlEnemigos.movidaDePantalla();
				controlObjetos.movidaDePantalla();
			}

			enviarEncuadres(&protagonista, &controlEnemigos, &controlObjetos);

			nivelTerminado = protagonista.llegoAlFin(&fondo);

			enviarMensajeDeNivelTerminado(nivelTerminado);

			SDL_Delay(25);
		}
	}
}

void Servidor::recibirInput(JugadorModelo* jugador) {
	socketsDeClientes[0].recibir(&mensajeCliente);

	switch (mensajeCliente.get()) {
        case Right:
            //Avanzar
            jugador->avanzar();
            break;
        case Left:
            //Atras
        	jugador->retroceder();
            break;
        case Up:
            //Arriba
        	jugador->subir();
            break;
        case Down:
            //Abajo
        	jugador->bajar();
            break;
        case Jump:
            //Saltar
        	jugador->saltar();
            break;
        case Crouch:
            //Agacharse
        	jugador->agacharse();
            break;
        case Hit:
            //Pegar
        	jugador->pegar();
            break;
        case Exit:
            //Salir
            // logueador->Info("Se seleccionó salir");
            break;
        case StopGoingRight:
            //Avanzar
        	jugador->dejarDeAvanzar();
            break;
        case StopGoingLeft:
            //Atras
        	jugador->dejarDeRetroceder();
            break;
        case StopGoingUp:
            //Arriba
        	jugador->dejarDeSubir();
            break;
        case StopGoingDown:
            //Abajo
        	jugador->dejarDeBajar();
            break;
        case Rise:
        	jugador->dejarDeAgacharse();
            break;
        case Nothing:
        	break;
		}
}

void Servidor::enviarCantidadDeRecieves(ControlEnemigosModelo* enemigos,
							ControlObjetosModelo* objetos) {
	socketsDeClientes[0].enviar(jugadores + objetos->obtenerCantidad()
								+ enemigos->obtenerCantidad());
}

void Servidor::enviarEncuadres(JugadorModelo* jugador,
		ControlEnemigosModelo* enemigos, ControlObjetosModelo* objetos) {
	jugador->enviarEncuadres(socketsDeClientes, 1);
	enemigos->enviarEncuadres(socketsDeClientes, 1);
	objetos->enviarEncuadres(socketsDeClientes, 1);
}


void Servidor::enviarMensajeDeNivelTerminado(bool nivelTerminado) {
	MensajeServidor mensaje;
	if (nivelTerminado) {
		mensaje.darVuelta();
	}
	socketsDeClientes[0].enviar(&mensaje);
}


Servidor::~Servidor() {
	socketAceptador.cerrar();
	for (int i = 0; i < jugadores; i++) {
		socketsDeClientes[i].cerrar();
	}
	delete[] socketsDeClientes;
}

