#include "../vistas/VistaTransicionJuego.h"
#include "../vistas/VistaEstado.h"
#include "Cliente.h"
#include "../comunicacion/MensajeInicioPartida.h"

Cliente::Cliente() {
	cantidadDeReceives = 0;
	archiConfig = NULL;
	sonidos = NULL;
	perdieron = false;
}

int Cliente::inicializar(char* direccionIP, char* puerto, pugi::xml_document* archiConfig) {

	Logger::Log *logueador = Logger::Log::ObtenerInstancia();
    string mensajeError;
    this->archiConfig = archiConfig;

    VentanaClienteInicioSesion ventanaInicioSesion;

    if (ventanaInicioSesion.getEstado() == VentanaClienteInicioSesion::ESTADO_ERROR) {
        // Ya logueado en el objeto
        return EXIT_FAILURE;
    }

    if (conectar(direccionIP, puerto) != 0) {
        ventanaInicioSesion.mostrarMensaje("ERROR: No se pudo acceder al servidor",
                                           VentanaClienteInicioSesion::MENSAJE_TIPO_ERROR);
        ventanaInicioSesion.demorar(5000);
        return EXIT_FAILURE;
    }

    MensajeCredenciales mensajeCredenciales;

    ventanaInicioSesion.mostrarMensaje("Conectando con el servidor, aguarde...",
                                       VentanaClienteInicioSesion::MENSAJE_TIPO_INFORMATIVO);

    // Se verifica si hay cupo disponible para que se conecte el jugador
    socket.recibir(&mensajeCredenciales);
    if (mensajeCredenciales.getEstado() == MensajeCredenciales::ESTADO_NO_MAS_JUGADORES_PERMITIDOS) {
        ventanaInicioSesion.mostrarMensaje("ERROR: tope de jugadores alcanzado",
                                           VentanaClienteInicioSesion::MENSAJE_TIPO_ERROR);
        ventanaInicioSesion.demorar(5000);
        return EXIT_FAILURE;
    } else {
        ventanaInicioSesion.mostrarMensaje("",
                                           VentanaClienteInicioSesion::MENSAJE_TIPO_INFORMATIVO);
    }

    // Autenticar usuario
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

    int retorno = ventanaJuego.abrir();
	if (retorno == -1) {
	   logueador->Error("No se pudo crear la ventanaJuego");
	}

	Renderizador renderizador(ventanaJuego.get());

    imagenEspera.cargar("assets/images/general/esperaPostAutenticacion.bmp",2);
    Encuadre encuadreEspera={0,0,800,600};
    Encuadre encuadreFijoEspera={0,0,800,600};
    texturaTransiciones.texturizar(&renderizador,imagenEspera);
    texturaTransiciones.copiarseEn(&renderizador, encuadreEspera, encuadreFijoEspera);
    renderizador.renderizar();


    GestorThreadsCliente gestorThreads(&socket);

    //Esperar mensaje con datos de inicio de partida
    //TODO cargar datos de los usuarios conectados en pantalla
    MensajeInicioPartida mensajeInicio = gestorThreads.recibirMensajeDeInicio();
    //Dejo preparados los vectores donde se cargará la info a mostrar de cada jugador
    InfoJugador infoJugadorees[mensajeInicio.getCantidadJugadoresPartida()];
    VistaEstado *vistasEstado[mensajeInicio.getCantidadJugadoresPartida()];

	gestorThreads.comenzar();

	bool terminoElNivel;

    for (int nivel = mensajeInicio.getNivelInicial(); nivel <= 2; nivel++) {

    	if (!perdieron) {
			string nivelNodeName = "nivel";
			nivelNodeName.append(to_string(nivel));

			logueador->Info("Iniciando nivel: " + nivelNodeName);
			logueador->Debug(
					"Leyendo del XML la ubicación de los BMPs de los fondos y el ancho del terreno");

			VistaFondo fondo(&renderizador, archiConfig, nivelNodeName);

			VistaJugador jugador1(&renderizador, archiConfig, Jugador1,
					&ejecutarSonidoGolpeTiro, &ejecutarSonidoGolpeImpacto,
					&ejecutarSonidoSalto, &ejecutarSonidoCaida);

			VistaJugador jugador2(&renderizador, archiConfig, Jugador2,
					&ejecutarSonidoGolpeTiro, &ejecutarSonidoGolpeImpacto,
					&ejecutarSonidoSalto, &ejecutarSonidoCaida);

			VistaJugador jugador3(&renderizador, archiConfig, Jugador3,
					&ejecutarSonidoGolpeTiro, &ejecutarSonidoGolpeImpacto,
					&ejecutarSonidoSalto, &ejecutarSonidoCaida);
			;
			VistaJugador jugador4(&renderizador, archiConfig, Jugador4,
					&ejecutarSonidoGolpeTiro, &ejecutarSonidoGolpeImpacto,
					&ejecutarSonidoSalto, &ejecutarSonidoCaida);

			logueador->Debug(
					"Creando enemigos y asignándoles su comportamiento básico");
			VistaEnemigo enemigo1(&renderizador, archiConfig, Enemigo1,
					&ejecutarSonidoGolpeTiro, &ejecutarSonidoGolpeImpacto,
					&ejecutarSonidoSalto, &ejecutarSonidoCaida);

			VistaEnemigo enemigo2(&renderizador, archiConfig, Enemigo2,
					&ejecutarSonidoGolpeTiro, &ejecutarSonidoGolpeImpacto,
					&ejecutarSonidoSalto, &ejecutarSonidoCaida);

			VistaEnemigo enemigo3(&renderizador, archiConfig, Enemigo3,
					&ejecutarSonidoGolpeTiro, &ejecutarSonidoGolpeImpacto,
					&ejecutarSonidoSalto, &ejecutarSonidoCaida);

			VistaEnemigo enemigo4(&renderizador, archiConfig, EnemigoJefe,
					&ejecutarSonidoGolpeTiro, &ejecutarSonidoGolpeImpacto,
					&ejecutarSonidoSalto, &ejecutarSonidoCaida);

			logueador->Debug(
					"Creando controlador de objetos y asignándoles su posición inicial");

			VistaObjeto barril(&renderizador, archiConfig, Barril,
					&ejecutarSonidoGolpeImpacto, &ejecutarSonidoDestruccion);
			VistaObjeto caja(&renderizador, archiConfig, Caja,
					&ejecutarSonidoGolpeImpacto, &ejecutarSonidoDestruccion);
			VistaObjeto cuchillo(&renderizador, archiConfig, Cuchillo,
					&ejecutarSonidoGolpeImpacto, &ejecutarSonidoDestruccion);
			VistaObjeto tubo(&renderizador, archiConfig, Tubo,
					&ejecutarSonidoGolpeImpacto, &ejecutarSonidoDestruccion);

			for (int i = 0; i < mensajeInicio.getCantidadJugadoresPartida();
					i++) {
				vistasEstado[i] = new VistaEstado(&renderizador, archiConfig,
						mensajeInicio.getVidaMax(),
						mensajeInicio.getNombreJugador(i), i);
			}

			recibirCantidadDeReceives(&gestorThreads);

			if (sonidos == NULL) {
				sonidos = new std::thread(
						Sonidos(archiConfig, &musicaFondoActiva,
								&ejecutarSonidoGolpeTiro,
								&ejecutarSonidoGolpeImpacto,
								&ejecutarSonidoSalto, &ejecutarSonidoCaida,
								&ejecutarSonidoDestruccion));
			}

			terminoElNivel = false;

			while (!terminoElNivel) {
				enviarInput(&gestorThreads);
				if (mensajeCliente.get() == Exit) {
					SDL_Delay(200);
					return 0;
				}
				if (gestorThreads.seDesconecto()) {
					Logger::Log::ObtenerInstancia()->Error(
							"Se desconectó el servidor. Cerrando cliente.");

					imagenDesconectado.cargar(
							"assets/images/general/cerrandoJuego.bmp", 4);
					Encuadre encuadreDesconectado = { 0, 0, 800, 600 };
					Encuadre encuadreFijoDesconectado = { 0, 0, 800, 600 };
					texturaTransiciones.texturizar(&renderizador,
							imagenDesconectado);
					texturaTransiciones.copiarseEn(&renderizador,
							encuadreDesconectado, encuadreFijoDesconectado);
					renderizador.renderizar();
					SDL_Delay(5000);
					return 0;
				}
				renderizarFondo(&fondo, &gestorThreads);
				recibirMensajes(&gestorThreads);

				while (!listaOrdenada.empty()) {

					MensajeServidor mensaje;
					mensaje = listaOrdenada.front();

					switch (mensaje.obtenerTipoDeSprite()) {
					case Jugador1:
						infoJugadorees[0] = mensaje.getInfoJugador();
						jugador1.renderizarConElMensaje(&mensaje);
						break;
					case Jugador2:
						infoJugadorees[1] = mensaje.getInfoJugador();
						jugador2.renderizarConElMensaje(&mensaje);
						break;
					case Jugador3:
						infoJugadorees[2] = mensaje.getInfoJugador();
						jugador3.renderizarConElMensaje(&mensaje);
						break;
					case Jugador4:
						infoJugadorees[3] = mensaje.getInfoJugador();
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
					case EnemigoJefe:
						enemigo4.renderizarConElMensaje(&mensaje);
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
				for (auto i = 0;
						i < mensajeInicio.getCantidadJugadoresPartida(); i++) {
					vistasEstado[i]->renderizar(infoJugadorees[i]);
				}
				renderizador.renderizar();

				terminoElNivel = getTerminoElNivel(&gestorThreads);
			}
			if (!perdieron) {
				VistaTransicionJuego::CambioDeNivel(nivel, &renderizador,
						infoJugadorees, mensajeInicio);
			} else {
				VistaTransicionJuego::CambioDeNivel(0, &renderizador,
						infoJugadorees, mensajeInicio);
			}
			logueador->Info("Fin de nivel: " + nivelNodeName);
			//TODO Loguear como corresponde
			logueador->Debug(
					"puntajes: " + to_string(infoJugadorees[0].getPuntaje()));
		}
	}

	socket.cerrar();
    //libero memoria de vistas de estado
    for(auto i = 0; i < mensajeInicio.getCantidadJugadoresPartida(); i++)
        delete vistasEstado[i];
    return 0;
}

int Cliente::conectar(char* direccionIP, char* puerto){
	return socket.conectarAUnServidor(direccionIP, puerto);
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
                    case SDLK_t:
                        //Modo test
                        mensajeCliente.Codificar(Test);
                        break;
                    case SDLK_s:
                        // Activar / desactivar música de fondo
                        musicaFondoActiva = !musicaFondoActiva;
                        break;
    			    case SDLK_k:
    			        //Prueba de matar
                        mensajeCliente.Codificar(Kill);
                        break;
    			    case SDLK_p:
    			        //Prueba de pegar
    			        mensajeCliente.Codificar(Punch);
    			        break;
    					//Para probar grisado sin red
    					//---------------------------
    			    case SDLK_q:
    			        //Desconectado
    			        mensajeCliente.Codificar(Disconnect);
                        Logger::Log::ObtenerInstancia()->Info("Selccionó desconectar (q)");
    			        break;
                    case SDLK_w:
                        //Conectado
                        mensajeCliente.Codificar(Connect);
                        break;
                        //----------------------------
                        //
    				case SDLK_ESCAPE:
    					//Salir
                        Logger::Log::ObtenerInstancia()->Info("Seleccionó salir (Escape)");
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

                }
    		}
    		break;

    	case SDL_QUIT:
    		mensajeCliente.Codificar(Exit);
    		Logger::Log::ObtenerInstancia()->Info("Seleccionó salir (cerró ventana)");
    		return;
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


bool Cliente::getTerminoElNivel(GestorThreadsCliente* gestorThreads) {
	mensajeServidor = gestorThreads->recibirMensaje();
	if (mensajeServidor.obtenerPosicionY() == 1)
		perdieron = true;
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


