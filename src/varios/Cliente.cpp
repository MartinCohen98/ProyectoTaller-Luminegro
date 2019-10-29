#include "Cliente.h"

Cliente::Cliente() {
	cantidadDeReceives = 0;
}

int Cliente::inicializar(char* direccionIP, char* puerto, pugi::xml_document* archiConfig) {

	Logger::Log *logueador = Logger::Log::ObtenerInstancia();

    VentanaClienteInicioSesion ventanaInicioSesion;

    if (ventanaInicioSesion.getEstado() == VentanaClienteInicioSesion::ESTADO_ERROR) {
        // Ya logueado en el objeto
        return EXIT_FAILURE;
    }

    conectar(direccionIP, puerto);

    MensajeCredenciales mensajeCredenciales;

    // Se verifica si hay cupo disponible para que se conecte el jugador
    socket.recibir(&mensajeCredenciales);
    if (mensajeCredenciales.getEstado() == MensajeCredenciales::ESTADO_NO_MAS_JUGADORES_PERMITIDOS) {
        ventanaInicioSesion.mostrarMensaje("ERROR: tope de jugadores alcanzado",
                                           VentanaClienteInicioSesion::MENSAJE_TIPO_ERROR);
        ventanaInicioSesion.demorar(5000);
        return EXIT_SUCCESS;
    }

    // Autenticar usuario
    string mensajeError;

    while (mensajeCredenciales.getEstado() != MensajeCredenciales::ESTADO_AUTENTICADO) {

        ventanaInicioSesion.pedirCredenciales();
        ventanaInicioSesion.mostrarMensaje("Validando...",
                                           VentanaClienteInicioSesion::MENSAJE_TIPO_INFORMATIVO);

        string usuario = ventanaInicioSesion.getUsuario();
        string clave = ventanaInicioSesion.getClave();
        mensajeCredenciales.setUsuario(usuario);
        mensajeCredenciales.setClave(clave);
        socket.enviar(&mensajeCredenciales);
        socket.recibir(&mensajeCredenciales);

        switch (mensajeCredenciales.getEstado()) {
            case MensajeCredenciales::ESTADO_USUARIO_O_CLAVE_ERRONEOS:
                mensajeError = "Error en usuario y/o clave, caballer@.";
                break;

            case MensajeCredenciales::ESTADO_USUARIO_YA_CONECTADO:
                mensajeError = "El usuario ya se encuentra conectado.";
                break;
        }

        if (mensajeCredenciales.getEstado() != MensajeCredenciales::ESTADO_AUTENTICADO) {
            ventanaInicioSesion.mostrarMensaje(mensajeError, VentanaClienteInicioSesion::MENSAJE_TIPO_ERROR);
            ventanaInicioSesion.demorar(2000);
            ventanaInicioSesion.resetear();
        }
    }

    // Fue autenticado
    ventanaInicioSesion.cerrar();

    VentanaCliente ventanaJuego;

    int retorno = ventanaJuego.abrir(archiConfig);
	if (retorno == -1) {
	   logueador->Error("No se pudo crear la ventanaJuego");
	}
	bool salir;

	Renderizador renderizador(ventanaJuego.get());

	GestorThreadsCliente gestorThreads(&socket);

	gestorThreads.comenzar();

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

		recibirCantidadDeReceives(&gestorThreads);

		while (!salir) {
	    	enviarInput(&gestorThreads);

	    	renderizarFondo(&fondo, &gestorThreads);
	    	recibirMensajes(&gestorThreads);

	        while (!listaOrdenada.empty()) {
	        	MensajeServidor mensaje;
	        	mensaje = listaOrdenada.front();
	        	switch(mensaje.obtenerTipoDeSprite()) {
	        		case Jugador1:
	        			jugador1.renderizarConElMensaje(&mensaje);
	        			break;
	        		case Jugador2:
	        			jugador2.renderizarConElMensaje(&mensaje);
	        			break;
	        		case Jugador3:
	        			jugador3.renderizarConElMensaje(&mensaje);
	        			break;
	        		case Jugador4:
	        			jugador4.renderizarConElMensaje(&mensaje);
	        			break;
	        		case Enemigo1:
	        			enemigo1.renderizarConElMensaje(&mensaje);
	        			break;
	        		case Enemigo2:
	        			enemigo2.renderizarConElMensaje(&mensaje);
	        			break;
	        		case Enemigo3:
	        			enemigo3.renderizarConElMensaje(&mensaje);
	        			break;
	        		case Barril:
	        			barril.renderizarConElMensaje(&mensaje);
	        			break;
	        		case Caja:
	        			caja.renderizarConElMensaje(&mensaje);
	        			break;
	        		case Cuchillo:
	        			cuchillo.renderizarConElMensaje(&mensaje);
	        			break;
	        		case Tubo:
	        			tubo.renderizarConElMensaje(&mensaje);
	        			break;
	        	}
	        	listaOrdenada.pop_front();
	        }

	        renderizador.renderizar();

	        if (terminoElNivel(&gestorThreads)) {
	    		salir = true;
	    	}
		}
		logueador->Info("Fin de nivel: " +  nivelNodeName);
	}

	socket.cerrar();

    return 0;
}

int Cliente::conectar(char* direccionIP, char* puerto){
	int resultado = socket.conectarAUnServidor(direccionIP, puerto);
	return resultado;
}

void Cliente::enviarInput(GestorThreadsCliente* gestorThreads){
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
    			    case SDLK_q:
    			        //Desconectado
    			        mensajeCliente.Codificar(Disconnect);
    			        break;
                    case SDLK_w:
                        //Conectado
                        mensajeCliente.Codificar(Connect);
                        break;
    				case SDLK_ESCAPE:
    					//Salir
    					mensajeCliente.Codificar(Exit);
    					break;
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
                  /*  case SDLK_q:
                        mensajeCliente.Codificar(Connect);
                        break;*/

                }
    		}
    		break;

    	case SDL_QUIT:
    		mensajeCliente.Codificar(Exit);
    		break;
	}
	gestorThreads->enviarMensaje(&mensajeCliente);
}


void Cliente::renderizarFondo(VistaFondo* fondo,
								GestorThreadsCliente* gestorThreads) {
	MensajeServidor mensaje1 = gestorThreads->recibirMensaje();
	MensajeServidor mensaje2 = gestorThreads->recibirMensaje();
	MensajeServidor mensaje3 = gestorThreads->recibirMensaje();
	fondo->renderizarConLosMensajes(&mensaje1, &mensaje2, &mensaje3);
}


void Cliente::recibirCantidadDeReceives(GestorThreadsCliente* gestorThreads) {
	mensajeServidor = gestorThreads->recibirMensaje();
	cantidadDeReceives = mensajeServidor.obtenerFrame()->getX();
}


bool Cliente::terminoElNivel(GestorThreadsCliente* gestorThreads) {
	mensajeServidor = gestorThreads->recibirMensaje();
	return (mensajeServidor.estaDadoVuelta());
}


void Cliente::recibirMensajes(GestorThreadsCliente* gestorThreads) {
	for (int i = 0; i < cantidadDeReceives; i++) {
		mensajeServidor = gestorThreads->recibirMensaje();
		listaOrdenada.push_front(mensajeServidor);
	}
	listaOrdenada.sort();
}


Cliente::~Cliente() {
	socket.cerrar();
}

