#include "VentanaDeJuego.h"

using namespace std;

VentanaDeJuego::VentanaDeJuego() {
	ventana = SDL_CreateWindow("Final Luminegro Fight",
								SDL_WINDOWPOS_CENTERED,
								SDL_WINDOWPOS_CENTERED,
								800, 600,
								0);
}

int VentanaDeJuego::abrir(pugi::xml_document* archiConfig) {

	Logger::Log *logueador  =  Logger::Log::ObtenerInstancia();

	if(!ventana) {
		logueador->Error("No se pudo crear la ventana");
		return -1;
	}

    bool salir;
	SDL_Event evento;
	Renderizador renderizador(ventana);

	for (int nivel = 1; nivel <= 2; nivel++) {

        string nivelNodeName = "nivel";
        nivelNodeName.append( to_string(nivel) );

		salir = false;

		logueador->Info("Iniciando nivel: "+ nivelNodeName);
		logueador->Debug("Leyendo del XML la ubicación de los BMPs de los fondos y el ancho del terreno");
		Fondo fondo(&renderizador, archiConfig, nivel);

		Protagonista protagonista(&renderizador, archiConfig);

		logueador->Debug("Creando enemigos y asignándoles su comportamiento básico");
		ControlEnemigos controlEnemigos(&renderizador, archiConfig);

		logueador->Debug("Creando controlador de objetos y asignándoles su posición inicial");
		ControlObjetos controlObjetos(&renderizador, archiConfig, fondo.obtenerAncho());

        while (!salir) {
            SDL_PollEvent(&evento);

            switch (evento.type) {
                case SDL_KEYDOWN:
                    if (evento.key.repeat == 0) {
                        switch (evento.key.keysym.sym) {
                            case SDLK_RIGHT:
                                //Avanzar
                                protagonista.avanzar();
                                break;
                            case SDLK_LEFT:
                                //Atras
                                protagonista.retroceder();
                                break;
                            case SDLK_UP:
                                //Arriba
                                protagonista.subir();
                                break;
                            case SDLK_DOWN:
                                //Abajo
                                protagonista.bajar();
                                break;
                            case SDLK_z:
                                //Saltar
                                protagonista.saltar();
                                break;
                            case SDLK_x:
                                //Agacharse
                                protagonista.agacharse();
                                break;
                            case SDLK_c:
                                //Pegar
                                protagonista.pegar();
                                break;
                            case SDLK_ESCAPE:
                                //Salir
                                logueador->Info("Se seleccionó salir");
                                return 0;
                        }
                    }
                    break;

                case SDL_KEYUP:
                    if (evento.key.repeat == 0) {
                        switch (evento.key.keysym.sym) {
                            case SDLK_RIGHT:
                                //Avanzar
                                protagonista.dejarDeAvanzar();
                                break;
                            case SDLK_LEFT:
                                //Atras
                                protagonista.dejarDeRetroceder();
                                break;
                            case SDLK_UP:
                                //Arriba
                                protagonista.dejarDeSubir();
                                break;
                            case SDLK_DOWN:
                                //Abajo
                                protagonista.dejarDeBajar();
                                break;
                            case SDLK_x:
                                protagonista.dejarDeAgacharse();
                                break;
                        }
                    }
                    break;

                case SDL_QUIT:
                    logueador->Info("Se seleccionó salir");
                    return 0;
            }

			protagonista.realizarMovimientos(&fondo);
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
			SDL_Delay(25);
		}
        logueador->Info("Fin de nivel: " +  nivelNodeName);
    }

    return 0;
}

VentanaDeJuego::~VentanaDeJuego() {
	if (ventana)
		SDL_DestroyWindow(ventana);
	SDL_Quit();
}

