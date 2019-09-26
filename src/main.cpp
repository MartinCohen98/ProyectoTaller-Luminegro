#include <stdio.h>
#include "VentanaDeJuego.h"

using namespace Logger;

int main (int argc, char** argv) {

    // Archivo de configuración
    string archiConfigPath;
    pugi::xml_document archiConfig;
    pugi::xml_parse_result archiConfigCarga;
    bool cargarArchivoConfigPorDefecto = true;

    // Envió por parámetro la ubicación del archivo?
    if (argc >= 2) {
        // Si
        archiConfigPath = argv[1];
        archiConfigCarga = archiConfig.load_file( archiConfigPath.data());
        if (archiConfigCarga.status == 0) {
            //Cargó bien el config por parámetro, no busca el config default
            cargarArchivoConfigPorDefecto = false;
        } else{
            //No cargó bien el config por parámetro, buscará el config default
            Log::ObtenerInstancia()->Error("No se pudo abrir el archivo de configuración \"" + archiConfigPath + "\"."
                                           + " Se detectó el problema en el byte " + to_string(archiConfigCarga.offset)
                                           + ". Mensaje de error: " + archiConfigCarga.description());
        }
    }

    //Ve si tiene que buscar el config por defecto
    if(cargarArchivoConfigPorDefecto) {
        archiConfigPath = "config/default.xml";
        archiConfigCarga = archiConfig.load_file(archiConfigPath.data());
        if (archiConfigCarga.status != 0) {
            //Rompió hasta el config por defecto, más no se puede hacer
            Log::ObtenerInstancia()->Error("No se pudo abrir el archivo de configuración por defecto: \"" + archiConfigPath + "\"."
                                           + " Se detectó el problema en el byte " + to_string(archiConfigCarga.offset)
                                           + ". Mensaje de error: " + archiConfigCarga.description());
            return EXIT_FAILURE;
        }
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
    if(!Log::InicializarLog(logLevel, "")) {
        //Si ya se había inicializado el logger (por error en apertura de config) al menos le setea el nivel de log
        Log::ObtenerInstancia()->SetSeveridadMinima(logLevel);
    }
    //En cualquier clase que haya que utilizar el logger, se lo instancia así
    Log *logueador  =  Log::ObtenerInstancia();

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
