#include "Cliente.h"

Cliente::Cliente(char* NumPuerto) {
	puerto = NumPuerto;
}

int Cliente::inicializar(char* direccionIP, char* puerto, pugi::xml_document* archiConfig){

	Logger::Log *logueador = Logger::Log::ObtenerInstancia();

	VentanaCliente ventana;

	int resultado = conectar(direccionIP, puerto);

	int retorno = ventana.abrir(archiConfig);
	if (retorno == -1){
	   logueador->Error("No se pudo crear la ventana");
	}
	bool salir;

	Renderizador renderizador(ventana.get());

	for (int nivel = 1; nivel <= 2; nivel++) {

		string nivelNodeName = "nivel";
		nivelNodeName.append( to_string(nivel) );

		salir = false;

		logueador->Info("Iniciando nivel: "+ nivelNodeName);
		logueador->Debug("Leyendo del XML la ubicación de los BMPs de los fondos y el ancho del terreno");
		VistaFondo fondo(&renderizador, archiConfig, nivelNodeName);

		VistaJugador jugador1(&renderizador, archiConfig, Jugador1);
		VistaJugador jugador2(&renderizador, archiConfig, Jugador2);
		VistaJugador jugador3(&renderizador, archiConfig, Jugador3);
		VistaJugador jugador4(&renderizador, archiConfig, Jugador4);

		logueador->Debug("Creando enemigos y asignándoles su comportamiento básico");
		VistaEnemigo enemigo1(&renderizador, archiConfig, Enemigo1);
		VistaEnemigo enemigo2(&renderizador, archiConfig, Enemigo2);
		VistaEnemigo enemigo3(&renderizador, archiConfig, Enemigo3);

		logueador->Debug("Creando controlador de objetos y asignándoles su posición inicial");
		VistaObjeto barril(&renderizador, archiConfig, Barril);
		VistaObjeto caja(&renderizador, archiConfig, Caja);
		VistaObjeto cuchillo(&renderizador, archiConfig, Cuchillo);
		VistaObjeto tubo(&renderizador, archiConfig, Tubo);

		while (!salir) {
	    	enviarInput(&mensajeCliente);

	    	recibirFondo(&fondo);

	        for (int i = 0; i < cantidadDeRecieves; i++) {
	        	switch(recibirMensaje()) {
	        		case Jugador1:
	        			jugador1.renderizarConElMensaje(&mensajeServidor);
	        			break;
	        		case Jugador2:
	        			jugador2.renderizarConElMensaje(&mensajeServidor);
	        			break;
	        		case Jugador3:
	        			jugador3.renderizarConElMensaje(&mensajeServidor);
	        			break;
	        		case Jugador4:
	        			jugador4.renderizarConElMensaje(&mensajeServidor);
	        			break;
	        		case Enemigo1:
	        			enemigo1.renderizarConElMensaje(&mensajeServidor);
	        			break;
	        		case Enemigo2:
	        			enemigo2.renderizarConElMensaje(&mensajeServidor);
	        			break;
	        		case Enemigo3:
	        			enemigo3.renderizarConElMensaje(&mensajeServidor);
	        			break;
	        		case Barril:
	        			barril.renderizarConElMensaje(&mensajeServidor);
	        			break;
	        		case Caja:
	        			caja.renderizarConElMensaje(&mensajeServidor);
	        			break;
	        		case Cuchillo:
	        			cuchillo.renderizarConElMensaje(&mensajeServidor);
	        			break;
	        		case Tubo:
	        			tubo.renderizarConElMensaje(&mensajeServidor);
	        			break;
	        	}
	        }

	        renderizador.renderizar();

	        if (terminoElNivel()) {
	    		salir = true;
	    	}
		}
		logueador->Info("Fin de nivel: " +  nivelNodeName);
	}
	return 0;
}

int Cliente::conectar(char* direccionIP, char* puerto){
	int resultado = socket.conectarAUnServidor(direccionIP, puerto);
	return resultado;
}

void Cliente::enviarInput(MensajeCliente* mensaje){
	mensajeCliente.Codificar(Nothing);

    SDL_PollEvent(&evento);

    switch (evento.type) {
    	case SDL_KEYDOWN:
    		if (evento.key.repeat == 0) {
    			switch (evento.key.keysym.sym) {
    				case SDLK_RIGHT:
    					//Avanzar
    					mensajeCliente.Codificar(Right);
    					break;
    				case SDLK_LEFT:
    					//Atras
    					mensajeCliente.Codificar(Left);
    					break;
    				case SDLK_UP:
    					//Arriba
    					mensajeCliente.Codificar(Up);
    					break;
    				case SDLK_DOWN:
    					//Abajo
    					mensajeCliente.Codificar(Down);
    					break;
    				case SDLK_z:
    					//Saltar
    					mensajeCliente.Codificar(Jump);
    					break;
    				case SDLK_x:
    					//Agacharse
    					mensajeCliente.Codificar(Crouch);
    					break;
    				case SDLK_c:
    					//Pegar
    					mensajeCliente.Codificar(Hit);
    					break;
    				case SDLK_ESCAPE:
    					//Salir
    					mensajeCliente.Codificar(Exit);
    			}
    		}
    		break;

    	case SDL_KEYUP:
    		if (evento.key.repeat == 0) {
    			switch (evento.key.keysym.sym) {
    				case SDLK_RIGHT:
    					//Avanzar
    					mensajeCliente.Codificar(StopGoingRight);
    					break;
    				case SDLK_LEFT:
    					//Atras
    					mensajeCliente.Codificar(StopGoingLeft);
    					break;
    				case SDLK_UP:
    					//Arriba
    					mensajeCliente.Codificar(StopGoingUp);
    					break;
    				case SDLK_DOWN:
    					//Abajo
    					mensajeCliente.Codificar(StopGoingDown);
    					break;
    				case SDLK_x:
    					mensajeCliente.Codificar(Rise);
    					break;
    			}
    		}
    		break;

    	case SDL_QUIT:
    		mensajeCliente.Codificar(Exit);
    		break;
	}
	socket.enviar(mensaje);
}


void Cliente::recibirFondo(VistaFondo* fondo) {
	MensajeServidor cielo;
	MensajeServidor edificios;
	MensajeServidor terreno;
	socket.recibir(&cielo);
	socket.recibir(&edificios);
	socket.recibir(&terreno);
	fondo->renderizarConLosMensajes(&cielo, &edificios, &terreno);
}


void Cliente::recibirCantidadDeRecieves() {
	socket.recibir(&cantidadDeRecieves);
}


bool Cliente::terminoElNivel() {
	recibirMensaje();
	return (mensajeServidor.estaDadoVuelta());
}


tipoDeSprite Cliente::recibirMensaje() {
	socket.recibir(&mensajeServidor);
	return (mensajeServidor.obtenerTipoDeSprite());
}


Cliente::~Cliente() {
	socket.cerrar();
}

