#include "Cliente.h"

Cliente::Cliente(char* NumPuerto) {
	puerto = NumPuerto;
}

int Cliente::inicializar(char* direccionIP, char* puerto, pugi::xml_document* archiConfig){

	Logger::Log *logueador = Logger::Log::ObtenerInstancia();

	VentanaCliente ventana;

	int resultado=conectar(direccionIP, puerto);

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
			Fondo fondo(&renderizador, archiConfig, nivel);

			Protagonista protagonista(&renderizador, archiConfig);

			logueador->Debug("Creando enemigos y asignándoles su comportamiento básico");
			ControlEnemigos controlEnemigos(&renderizador, archiConfig, nivel);

			logueador->Debug("Creando controlador de objetos y asignándoles su posición inicial");
			ControlObjetos controlObjetos(&renderizador, archiConfig, fondo.obtenerAncho(), nivel);

	        while (!salir) {
	        	enviarInput(&mensajeCliente);

	            long int datosRecibidos;
	            int maxDatos;
	            bool socketValido;
	            recibir(&datosRecibidos,&maxDatos,&socketValido);

	            int accionRecibida;

	            actualizar(accionRecibida, &protagonista);

	            protagonista.realizarMovimientos(&fondo);
	/*
				controlEnemigos.realizarMovimientos();

				if (fondo.seMovio()) {
					controlEnemigos.movidaDePantalla();
					controlObjetos.movidaDePantalla();
				}

				fondo.actualizar(&renderizador);
				controlEnemigos.actualizarFondo(&renderizador);
				controlObjetos.actualizar(&renderizador);
				protagonista.actualizar(&renderizador);
				controlObjetos.actualizarFrente(&renderizador);
				controlEnemigos.actualizarFrente(&renderizador);
				renderizador.renderizar();

	            salir = protagonista.llegoAlFin(&fondo);
				SDL_Delay(25);*/
			}
	        logueador->Info("Fin de nivel: " +  nivelNodeName);
	    }

	    return 0;


	return retorno;

}

int Cliente::conectar(char* direccionIP, char* puerto){

	int resultado=socket.conectarAUnServidor(direccionIP, puerto);
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

int Cliente::recibir(long int* datos, int* cantMaxDatos, bool* elSocketEsValido){

}

void Cliente::actualizar(int accionRecibida,Protagonista *protagonista){
	 switch (accionRecibida) {
	        case Right:
	            //Avanzar
	            protagonista->avanzar();
	            break;
	        case Left:
	             //Atras
	             protagonista->retroceder();
	             break;
	        case Up:
	             //Arriba
	             protagonista->subir();
	             break;
	        case Down:
	             //Abajo
	             protagonista->bajar();
	             break;
	        case Jump:
	             //Saltar
	             protagonista->saltar();
	             break;
	        case Crouch:
	             //Agacharse
	             protagonista->agacharse();
	             break;
	        case Hit:
	             //Pegar
	             protagonista->pegar();
	             break;
	        case Exit:
	             //Salir
	            // logueador->Info("Se seleccionó salir");
	             break;
	        case StopGoingRight:
	             //Avanzar
	             protagonista->dejarDeAvanzar();
	             break;
	        case StopGoingLeft:
	             //Atras
	             protagonista->dejarDeRetroceder();
	             break;
	        case StopGoingUp:
	             //Arriba
	             protagonista->dejarDeSubir();
	             break;
	        case StopGoingDown:
	             //Abajo
	             protagonista->dejarDeBajar();
	             break;
	        case Rise:
	             protagonista->dejarDeAgacharse();
	             break;
	 }
}

void Cliente::cerrar(){}

Cliente::~Cliente() {}

