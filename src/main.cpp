#include <stdio.h>
#include "VentanaDeJuego.h"

using namespace Logger;

int main (int argc, char** argv) {

    // Archivo de configuración
    string archiConfigPath;
    pugi::xml_document archiConfig;
    pugi::xml_parse_result archiConfigCarga;

    // Envió por parámetro la ubicación del archivo?
    if (argc >= 2) {
        // Si
        archiConfigPath = argv[1];
    }else{
        // Si no pudo cargar el archivo solicitado, cargar el predeterminado
        archiConfigPath = "config/default.xml";
    }
    //Trata de cargar el archivo de configuración. Si no puede, loguea el error, indicando el byte donde lo detectó
    archiConfigCarga = archiConfig.load_file( archiConfigPath.data());
    if (archiConfigCarga.status != 0) {
        Log::ObtenerInstancia()->Error("No se pudo abrir el archivo de configuración \"" +  archiConfigPath + "\"."
                                    + " Se detectó el problema en el byte " + to_string(archiConfigCarga.offset)
                                    + ". Mensaje de error: "+ archiConfigCarga.description());
        exit(EXIT_FAILURE);
    }

    // Nivel de logueo
    string logLevel;

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

    logueador->Info("SDL inicio correctamente, ejecutando...");

	VentanaDeJuego ventana;

	int retorno = ventana.abrir(&archiConfig);

    logueador->Info("Fin del juego");

	return retorno;
}
