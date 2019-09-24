
#include <stdio.h>
#include "VentanaDeJuego.h"
#include "Renderizador.h"
#include "Protagonista.h"
#include "Enemigo.h"
#include "Barril.h"
#include "Caja.h"
#include "Cuchillo.h"
#include "Tubo.h"
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
    Log  *logueador  =  Logger::Log::ObtenerInstancia();

    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        logueador->Error("No se pudo iniciar SDL2 correctamente");
        return -1;
    }

    logueador->Debug("Ejecutando el main.cpp");

    bool salir;
	SDL_Event evento;
	int retorno;
	VentanaDeJuego ventana;
	Renderizador renderizador(ventana.Get());

	for (int i = 1; i <= 2; i++) {
		salir = false;
		Parallax parallax(&renderizador);
		Protagonista protagonista(&renderizador, &archiConfig);

        const char* enemigoBredBMPPath = archiConfig.child("configuracion").child("escenario")
                .child("enemigos").child("bred").child("imagen").attribute("url").value();

        const char* enemigoDugBMPPath = archiConfig.child("configuracion").child("escenario")
                .child("enemigos").child("dug").child("imagen").attribute("url").value();

        const char* enemigoJakeBMPPath = archiConfig.child("configuracion").child("escenario")
                .child("enemigos").child("jake").child("imagen").attribute("url").value();

        logueador->Debug("Creando enemigos y asignándoles su comportamiento básico");

        /* ControlEnemigos controlEnemigos(&renderizador, &archiConfig);*/

        Enemigo enemigo1(&renderizador, 650, 220, enemigoBredBMPPath);
		Enemigo enemigo2(&renderizador, 300, 350, enemigoDugBMPPath);
		Enemigo enemigo3(&renderizador, 1700, 220, enemigoJakeBMPPath);
		Enemigo enemigo4(&renderizador, -500, 350, enemigoJakeBMPPath);
 		Enemigo enemigo5(&renderizador, 2500, 220, enemigoDugBMPPath);

		enemigo1.retroceder();
		enemigo2.avanzar();
		enemigo3.retroceder();
		enemigo4.avanzar();
		enemigo5.retroceder();

        logueador->Debug("Creando controlador de objetos y asignándoles su posición inicial");

        ControlObjetos controlObjetos(&renderizador,&archiConfig);

		int barrilesCantidad;
	    int cajasCantidad;
	    int cuchillosCantidad;
		int tubosMetalicosCantidad;

		std::string barrilesCantidadString = archiConfig.child("configuracion").child("escenario")
			            .child("niveles").child("nivel1").child("barril").child_value("cantidad");

	    std::string cajasCantidadString = archiConfig.child("configuracion").child("escenario")
			            .child("niveles").child("nivel1").child("caja").child_value("cantidad");

	    std::string cuchillosCantidadString = archiConfig.child("configuracion").child("escenario")
			            .child("niveles").child("nivel1").child("cuchillo").child_value("cantidad");

	    std::string tubosMetalicosCantidadString = archiConfig.child("configuracion").child("escenario")
			            .child("niveles").child("nivel1").child("tuboMetalico").child_value("cantidad");

		barrilesCantidad = std::stoi(barrilesCantidadString);
		cajasCantidad = std::stoi(cajasCantidadString);
		cuchillosCantidad = std::stoi(cuchillosCantidadString);
		tubosMetalicosCantidad = std::stoi(tubosMetalicosCantidadString);

		Barril *barriles[barrilesCantidad];
		Caja *cajas[cajasCantidad];
		Cuchillo *cuchillos[cuchillosCantidad];
		Tubo *tubos[tubosMetalicosCantidad];

        for (i = 0; i < barrilesCantidad; i++) {
            int distrX = i * 700 + 100;
            int distrY = i * 5 + 400;
            barriles[i] = new Barril(&renderizador, distrX, distrY, &archiConfig);
        }

        for (i = 0; i < cajasCantidad; i++) {
			int distrX = i * 700 + 400;
			int distrY = i * 5 + 400;
			cajas[i] = new Caja(&renderizador, distrX, distrY, &archiConfig);
        }

        for (i = 0; i < cuchillosCantidad; i++) {
            int distrX = i * 700 + 700;
            int distrY = i * 5 + 500;
            cuchillos[i] = new Cuchillo(&renderizador, distrX, distrY, &archiConfig);
        }

		for (i = 0; i < tubosMetalicosCantidad; i++) {
			int distrX = i * 700 + 1000;
			int distrY = i * 5 + 500;
			tubos[i] = new Tubo(&renderizador, distrX, distrY, &archiConfig);
		}

		retorno = ventana.Abrir(&renderizador);

        std::string nivelNodeName = "nivel";
        nivelNodeName.append( std::to_string(i) );

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
                for (i = 0; i < barrilesCantidad; i++) {
            		barriles[i]->actualizar(&renderizador);
            	}

            	for (i = 0; i < cajasCantidad; i++) {
            		cajas[i]->actualizar(&renderizador);
            	}

            	for (i = 0; i < cuchillosCantidad; i++) {
            		cuchillos[i]->actualizar(&renderizador);
            	}

            	for (i = 0; i < tubosMetalicosCantidad; i++) {
                    tubos[i]->actualizar(&renderizador);
                }

            } else {

                for (i = 0; i < barrilesCantidad; i++) {
            	    barriles[i]->refrescar(&renderizador);
            	}

                for (i = 0; i < cajasCantidad; i++) {
                   cajas[i]->refrescar(&renderizador);
                }

                for (i = 0; i < cuchillosCantidad; i++) {
                   cuchillos[i]->refrescar(&renderizador);
                }

                for (i = 0; i < tubosMetalicosCantidad; i++) {
                   tubos[i]->refrescar(&renderizador);
                }

            }

            enemigo1.retroceder();
			enemigo1.actualizar(&renderizador);
			enemigo3.retroceder();
			enemigo3.actualizar(&renderizador);
			enemigo5.retroceder();
			enemigo5.actualizar(&renderizador);

			protagonista.actualizar(&renderizador, &parallax);

			enemigo2.avanzar();
			enemigo2.actualizar(&renderizador);
			enemigo4.avanzar();
			enemigo4.actualizar(&renderizador);
			renderizador.renderizar();

			if (!salir) {
                salir = protagonista.llegoAlFin(&parallax);
            }
			SDL_Delay(25);
		}

        logueador->Debug("Fin de nivel " +  nivelNodeName);

		if (i=2) {
            salir = true;
        }
	}

    logueador->Debug("Fin del juego");

	return retorno;
}
