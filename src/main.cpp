#include <stdio.h>
#include "VentanaDeJuego.h"
#include "Renderizador.h"
#include "Protagonista.h"
#include "ControlObjetos.h"
#include "ControlEnemigos.h"
#include <SDL2/SDL.h>
#include "../lib/pugixml/pugixml.hpp"
#include <iostream>
#include "Logger.h"

using namespace Logger;

int main (int argc, char** argv) {

    // Archivo de configuración
    std::string archiConfigPath;
    pugi::xml_document archiConfig;
    pugi::xml_parse_result archiConfigCarga;

    // Envió por parámetro la ubicación del archivo?
    if (argc >= 2) {
        // Si
        archiConfigPath = argv[1];
        archiConfigCarga = archiConfig.load_file( archiConfigPath.data() );
    }

    // Si no pudo cargar el archivo solicitado, cargar el predeterminado
    if (archiConfigCarga.status != 0) {
        archiConfigCarga = archiConfig.load_file("config/default.xml");
        if (archiConfigCarga.status != 0) {
            Log::ObtenerInstancia()->Error("No se puede encontrar ningún archivo de configuración.");
            exit(EXIT_FAILURE);
        }
    }

    // Nivel de logueo
    std::string logLevel;

    // Lo envió por parámetro?
    if (argc >= 3) {
        // Si
        logLevel = argv[2];
    } else {
        // No, leo del XML
        logLevel = archiConfig.child("configuracion").child("log").child_value("level");
    }

    //Se inicializa el Logger acá y así queda para el resto de la aplicación.
    Log::InicializarLog(logLevel, "");
    //En cualquier clase que haya que utilizar el logger, se lo instancia así
    Log *logueador  =  Logger::Log::ObtenerInstancia();

    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        logueador->Error("No se pudo iniciar SDL2 correctamente");
        return -1;
    }

    logueador->Debug("SDL inicio correctamente, ejecutando...");

    bool salir;
	SDL_Event evento;
	int retorno;
	VentanaDeJuego ventana;
	Renderizador renderizador(ventana.Get());

	for (int nivel = 1; nivel <= 2; nivel++) {

        std::string nivelNodeName = "nivel";
        nivelNodeName.append( std::to_string(nivel) );

        salir = false;
		Parallax parallax(&renderizador);
		Protagonista protagonista(&renderizador, &archiConfig);

        logueador->Debug("Creando enemigos y asignándoles su comportamiento básico");

        ControlEnemigos controlEnemigos(&renderizador, &archiConfig);

        logueador->Debug("Creando controlador de objetos y asignándoles su posición inicial");

		retorno = ventana.Abrir(&renderizador);

        logueador->Debug("Nivel: "+ nivelNodeName);
        logueador->Debug("Leyendo del XML la ubicación de los BMPs de los fondos y el ancho del terreno");

        std::string nubesBMPPath = archiConfig.child("configuracion").child("escenario")
                .child("niveles").child( nivelNodeName.data() ).child_value("nubes");

        std::string edificiosBMPPath = archiConfig.child("configuracion").child("escenario")
                .child("niveles").child( nivelNodeName.data() ).child_value("edificios");

        std::string terrenoBMPPath = archiConfig.child("configuracion").child("escenario")
                .child("niveles").child( nivelNodeName.data() ).child_value("terreno");

        std::string terrenoWidthString = archiConfig.child("configuracion").child("escenario")
                .child("niveles").child( nivelNodeName.data() ).child_value("terrenoWidth");

        logueador->Debug("nubesBMPPath: " + nubesBMPPath);
        logueador->Debug("edificiosBMPPath: " + edificiosBMPPath);
        logueador->Debug("terrenoBMPPath: " + terrenoBMPPath + " terrenoBMPPath: " + terrenoBMPPath);

        int terrenoWidth = std::stoi(terrenoWidthString);

        ControlObjetos controlObjetos(&renderizador,&archiConfig, terrenoWidth);

        logueador->Debug("Carga capas en el Parallax");

        parallax.cargarCapas(nubesBMPPath.data(),
                             edificiosBMPPath.data(),
                             terrenoBMPPath.data(),
                             &renderizador);

        parallax.cambiarLimite(terrenoWidth);
		parallax.actualizar(&renderizador);

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
                                salir = true;
                                break;
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
					salir = true;
					break;
			}

			parallax.actualizar(&renderizador);

		    int avance = parallax.consultarAvance();
			bool aux = controlObjetos.Actualizar(&renderizador,avance);

            if (aux) {
            	controlEnemigos.movidaDePantalla();
            }

            controlEnemigos.realizarMovimientos();
            controlEnemigos.actualizarFondo(&renderizador);
			protagonista.actualizar(&renderizador, &parallax);
			controlEnemigos.actualizarFrente(&renderizador);
			renderizador.renderizar();

			if (!salir) {
                salir = protagonista.llegoAlFin(&parallax);
            }
			SDL_Delay(25);
		}

        logueador->Debug("Fin de nivel " +  nivelNodeName);

		if (nivel == 2) {
            salir = true;
        }
	}

    logueador->Debug("Fin del juego");

	return retorno;
}
