#include <stdio.h>
#include "VentanaDeJuego.h"
#include "Renderizador.h"
#include "Protagonista.h"
#include <SDL2/SDL.h>
#include "../lib/pugixml/pugixml.hpp"
#include <iostream>
#include "logger.h"


int main () {
    // Cargar un archivo de configuración específico
    pugi::xml_document archiConfig;
    pugi::xml_parse_result archiConfigCarga = archiConfig.load_file("config/repiola.xml");

    // Si no pudo cargar el archivo específico, cargar el predeterminado
    if (archiConfigCarga.status != 0) {
        archiConfigCarga = archiConfig.load_file("config/default.xml");
    }

    // Leer el nivel de logueo
    std::string logLevel = archiConfig.child("configuracion").child("log").child_value("level");

    Logger::Log logueador(logLevel);

    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        logueador.Error("No se pudo iniciar SDL2 correctamente");
        return -1;
    }

    logueador.Info("Ejecutando el main.cpp");

    bool salir;
	SDL_Event evento;
	int retorno;
	VentanaDeJuego ventana;
	Renderizador renderizador(ventana.Get());

	for (int i = 1; i <= 2; i++){
		salir = false;
		Parallax parallax(&renderizador);
		Protagonista protagonista(&renderizador, &archiConfig);
		retorno = ventana.Abrir(&renderizador);

        std::string nivelNodeName = "nivel";
        nivelNodeName.append( std::to_string(i) );

        // Leo del XML la ubicación de los BMPs de los fondos y el ancho del terreno
        std::string nubesBMPPath = archiConfig.child("configuracion").child("escenario")
                .child("niveles").child( nivelNodeName.data() ).child_value("nubes");

        std::string edificiosBMPPath = archiConfig.child("configuracion").child("escenario")
                .child("niveles").child( nivelNodeName.data() ).child_value("edificios");

        std::string terrenoBMPPath = archiConfig.child("configuracion").child("escenario")
                .child("niveles").child( nivelNodeName.data() ).child_value("terreno");

        std::string terrenoWidthString = archiConfig.child("configuracion").child("escenario")
                .child("niveles").child( nivelNodeName.data() ).child_value("terrenoWidth");

        int terrenoWidth = std::stoi(terrenoWidthString);

        parallax.cargarCapas(nubesBMPPath.data(),
                             edificiosBMPPath.data(),
                             terrenoBMPPath.data(),
                             &renderizador);

        parallax.cambiarLimite(terrenoWidth);

		parallax.actualizar(&renderizador);

		while (!salir) {
			SDL_PollEvent(&evento);
			switch (evento.type){
				case SDL_KEYDOWN:
					switch (evento.key.keysym.sym){
						case SDLK_RIGHT:
							//Avanzar
							protagonista.avanzar(&parallax);
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
							break;
						case SDLK_x:
							//Agacharse
							protagonista.agacharse();
							break;
						case SDLK_c:
							//Pegar
							break;
						case SDLK_ESCAPE:
							//Salir
							salir = true;
							break;
					}
					break;
				case SDL_KEYUP:
					protagonista.parar();
					break;
				case SDL_QUIT:
					salir = true;
					break;
			}
			parallax.actualizar(&renderizador);
			protagonista.actualizar(&renderizador);
			renderizador.renderizar();
			if (!salir)
				salir = protagonista.llegoAlFin(&parallax);
			SDL_Delay(16);
		}
	}
	return retorno;
}


