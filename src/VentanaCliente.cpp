/*
 * VentanaCliente.cpp
 *
 *  Created on: 9 oct. 2019
 *      Author: julio
 */

#include "VentanaCliente.h"

using namespace std;

VentanaCliente::VentanaCliente() {
	ventana = SDL_CreateWindow("Final Luminegro Fight",
								SDL_WINDOWPOS_CENTERED,
								SDL_WINDOWPOS_CENTERED,
								800, 600,
								0);
}

int VentanaCliente::abrir(pugi::xml_document* archiConfig) {

	Logger::Log *logueador  =  Logger::Log::ObtenerInstancia();

	if(!ventana) {
		logueador->Error("No se pudo crear la ventana");
		return -1;
	}

    bool salir;
	SDL_Event evento;
	Renderizador renderizador(ventana);
	MensajeCliente mensajeCliente;

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
            }
/*
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
			SDL_Delay(25);*/
		}
        logueador->Info("Fin de nivel: " +  nivelNodeName);
    }

    return 0;
}

SDL_Window* VentanaCliente::get(){
	return ventana;
}

VentanaCliente::~VentanaCliente() {
	if (ventana)
		SDL_DestroyWindow(ventana);
	SDL_Quit();
}


