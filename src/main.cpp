#include <cstdio>
#include "VentanaDeJuego.h"
#include "Socket.h"

using namespace Logger;

#define CANTIDAD_MINIMA_PARAMETROS 3

int main (int argc, char** argv) {

    /** Parámetros de línea de comandos para ejecutar el juego. Los que tienen asterisco son obligatorios.
     *
     * 1*: modo de aplicación: "servidor", "cliente" o "simple" (este último es temporario, para jugar de a uno sin red).
     * 2*: si el modo es del parámetro previo es "servidor", aquí en que puerto escuchará. Si es "cliente", a qué IP y
     *      puerto se conectará.
     * 3: ubicación del archivo de configuración
     * 4: nivel mínimo de logueo (DEBUG, INFO o ERROR)
     *
     * Ejemplos (todavía no se si los puertos que están abajo no hacen conflicto con otra cosa):
     *      ./ProyectoTaller-Luminegro simple 2100 config/repiola.xml    <---- el modo "simple" es temporario
     *      ./ProyectoTaller-Luminegro servidor 2100 config/repiola.xml DEBUG
     *      ./ProyectoTaller-Luminegro servidor 2101
     *      ./ProyectoTaller-Luminegro cliente 192.168.0.3:200
     *      ./ProyectoTaller-Luminegro cliente 192.168.0.3:200 config/repiola.xml
     *
     **/

    // Valida que tenga la cantidad mínima de parámetros
    // TODO Separar toda la validación de parámetros de entrada del main
    if (argc < CANTIDAD_MINIMA_PARAMETROS) {
        Log::ObtenerInstancia()->Error("Faltan parámetros de invocación");
        cerr << "ERROR: Faltan parámetros de invocación." << endl;
        cerr << "Para modo Servidor:" << endl;
        cerr << "\t./<ejecutable> servidor <puerto> <(opcional)ruta config> <(opcional)nivel log>" << endl;
        cerr << "Para modo Cliente:" << endl;
        cerr << "\t./<ejecutable> cliente <ipServidor:puerto> <(opcional)ruta config> <(opcional)nivel logl>" << endl;
        //cerr <<
        return EXIT_FAILURE;
    }

    // Archivo de configuración
    pugi::xml_document archiConfig;
    pugi::xml_parse_result archiConfigCarga;
    bool cargarArchivoConfigPorDefecto = true;

    // Envió por parámetro la ubicación del archivo?
    if (argc >= 4) {
        // Si
        archiConfigCarga = archiConfig.load_file(argv[3]);

        if (archiConfigCarga.status == 0) {
            // Cargó bien el config por parámetro, no busca el config default
            cargarArchivoConfigPorDefecto = false;

        } else {
            // No cargó bien el config por parámetro, buscará el config default
            string mensajeError = "No se pudo abrir el archivo de configuración \"";

            mensajeError.append(argv[3]);
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
            mensajeError.append(argv[3]);
            mensajeError.append("\". Se detectó el problema en el byte " + to_string(archiConfigCarga.offset)
                                + ". Mensaje de error: " + archiConfigCarga.description());

            Log::ObtenerInstancia()->Error(mensajeError);
            return EXIT_FAILURE;
        }
    }

    // Nivel de logueo
    string logLevel;

    // Lo envió por parámetro?
    if (argc >= 5) {
        // Si
        logLevel = argv[4];
    } else {
        // No, leo del XML
        logLevel = archiConfig.child("configuracion").child("log").child_value("level");
    }

    // Se inicializa el Logger acá y así queda para el resto de la aplicación.
    if (!Log::InicializarLog(logLevel, "")) {
        //Si ya se había inicializado el logger (por error en apertura de config) al menos le setea el nivel de log
        Log::ObtenerInstancia()->SetSeveridadMinima(logLevel);
    }
    // En cualquier clase que haya que utilizar el logger, se lo instancia así
    Log *logueador  =  Log::ObtenerInstancia();



    if (strcmp(argv[1], "servidor") == 0) {
        // SERVIDOR

        logueador->Info("Se inicia el juego en modo servidor");

        Socket socketEsperando;

        int resultadoAccion = socketEsperando.servidorInicializar(argv[2]);
        if (resultadoAccion == 1) {
            // Ya fue logueado en la clase
            return EXIT_FAILURE;
        }

        // (INICIO) ESTO SE TIENE QUE LLAMAR CON UNA INSTANCIA NUEVA DE "Socket" POR CADA JUGADOR QUE SE NOS CONECTA
        Socket socketConectado;

        resultadoAccion = socketEsperando.esperarYAceptarCliente(&socketConectado);
        if (resultadoAccion == EXIT_FAILURE) {
            // Ya fue logueado en la clase
            return EXIT_FAILURE;
        }
        socketConectado.cerrar();
        // (FIN) ESTO SE TIENE QUE LLAMAR CON UNA INSTANCIA NUEVA DE "Socket" POR CADA JUGADOR QUE SE NOS CONECTA

        socketEsperando.cerrar();

    } else if (strcmp(argv[1], "cliente") == 0) {
        // CLIENTE

        logueador->Info("Se inicia el juego en modo cliente");

        Socket socketConectado;

        // (INICIO) Desgloso IP y puerto del parámetro de entrada
        // TODO Englobar en una función
        unsigned int i;

        for (i = 0; i <= strlen(argv[2]); i++) {
            if (argv[2][i] == ':') {
                break;
            }
        }

        unsigned int j = strlen(argv[2]);
        char direccionIP[i + 1];
        char puerto[j - i];
        memcpy(direccionIP, &argv[2][0], i);
        direccionIP[i] = '\0';
        memcpy(puerto, &argv[2][i + 1], j);
        puerto[j - i] = '\0';
        // (FIN) Desgloso IP y puerto del parámetro de entrada

        int resultado = socketConectado.conectarAUnServidor(direccionIP, puerto);
        if (resultado == 1) {
            // Ya fue logueado en la clase
            return EXIT_FAILURE;
        }

        socketConectado.cerrar();

        return EXIT_SUCCESS;

    } else if (strcmp(argv[1], "simple") == 0) {
        // MODO SIMPLE, TEMPORARIO

        logueador->Info("Se inicia el juego en modo simple (temporario)");

        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            logueador->Error("No se pudo iniciar SDL2 correctamente");
            return EXIT_FAILURE;
        }

        logueador->Info("SDL inicio correctamente, ejecutando...");

        VentanaDeJuego ventana;

        int retorno = ventana.abrir(&archiConfig);

        logueador->Info("Fin del juego");

        return retorno;

    } else {

        logueador->Error("Paránetros incorrectos, no se inició ni en modo servidor ni en modo cliente");
        cerr << "ERROR: Parámetros de invocación incorrectos" << endl;
        cerr << "Para modo Servidor:" << endl;
        cerr << "\t./<ejecutable> servidor <puerto> <(opcional)ruta config> <(opcional)nivel log>" << endl;
        cerr << "Para modo Cliente:" << endl;
        cerr << "\t./<ejecutable> cliente <ipServidor:puerto> <(opcional)ruta config> <(opcional)nivel logl>" << endl;
        //cerr <<
        return EXIT_FAILURE;
    }
}
