#include <stdio.h>
#include "VentanaDeJuego.h"

using namespace Logger;

int main (int argc, char** argv) {

    /** Parámetros de línea de comandos para ejecutar el juego:
     *
     * 1: "servidor" o "cliente" (OBLIGATORIO)
     * 2: ubicación del archivo de configuración
     * 3: modo de logueo
     *
     * Ejemplos:
     *      ./ProyectoTaller-Luminegro servidor config/repiola.xml DEBUG
     *      ./ProyectoTaller-Luminegro servidor
     *
     **/

    // Archivo de configuración
    pugi::xml_document archiConfig;
    pugi::xml_parse_result archiConfigCarga;
    bool cargarArchivoConfigPorDefecto = true;

    // Envió por parámetro la ubicación del archivo?
    if (argc >= 3) {
        // Si
        archiConfigCarga = archiConfig.load_file(argv[2]);

        if (archiConfigCarga.status == 0) {
            // Cargó bien el config por parámetro, no busca el config default
            cargarArchivoConfigPorDefecto = false;

        } else {
            // No cargó bien el config por parámetro, buscará el config default
            string mensajeError = "No se pudo abrir el archivo de configuración \"";

            mensajeError.append(argv[2]);
            mensajeError.append("\". Se detectó el problema en el byte " + to_string(archiConfigCarga.offset)
                                  + ". Mensaje de error: " + archiConfigCarga.description());

            Log::ObtenerInstancia()->Error(mensajeError);
        }
    }

    // Ver si tiene que buscar el config por defecto
    if (cargarArchivoConfigPorDefecto) {
        archiConfigCarga = archiConfig.load_file("config/default.xml");

        if (archiConfigCarga.status != 0) {
            // Rompió hasta el config por defecto, más no se puede hacer
            string mensajeError = "No se pudo abrir el archivo de configuración por defecto: \"";
            mensajeError.append(argv[2]);
            mensajeError.append("\". Se detectó el problema en el byte " + to_string(archiConfigCarga.offset)
                                + ". Mensaje de error: " + archiConfigCarga.description());

            Log::ObtenerInstancia()->Error(mensajeError);
            return EXIT_FAILURE;
        }
    }

    // Nivel de logueo
    string logLevel;

    // Lo envió por parámetro?
    if (argc >= 4) {
        // Si
        logLevel = argv[3];
    } else {
        // No, leo del XML
        logLevel = archiConfig.child("configuracion").child("log").child_value("level");
    }

    //Se inicializa el Logger acá y así queda para el resto de la aplicación.
    if (!Log::InicializarLog(logLevel, "")) {
        //Si ya se había inicializado el logger (por error en apertura de config) al menos le setea el nivel de log
        Log::ObtenerInstancia()->SetSeveridadMinima(logLevel);
    }
    //En cualquier clase que haya que utilizar el logger, se lo instancia así
    Log *logueador  =  Log::ObtenerInstancia();


    // Arrancamos...
    if (strcmp(argv[1], "servidor") == 0) {
        logueador->Info("Se inicia el juego en modo servidor");

    } else if (strcmp(argv[1], "cliente") == 0) {
        logueador->Info("Se inicia el juego en modo cliente");

        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            logueador->Error("No se pudo iniciar SDL2 correctamente");
            return -1;
        }

        logueador->Info("SDL inicio correctamente, ejecutando...");

        VentanaDeJuego ventana;

        int retorno = ventana.abrir(&archiConfig);

        logueador->Info("Fin del juego");

        return retorno;
    }
}
