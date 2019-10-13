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
		}
	}
}

void Servidor::recibirInput(JugadorModelo* jugdor) {
	//TODO
}

void Servidor::enviarEncuadres(JugadorModelo* jugador,
		ControlEnemigosModelo* enemigos, ControlObjetosModelo* objetos) {
	//TODO
}

Servidor::~Servidor() {
	socketAceptador.cerrar();
	for (int i = 0; i < jugadores; i++) {
		socketsDeClientes[i].cerrar();
	}
	delete[] socketsDeClientes;
}

