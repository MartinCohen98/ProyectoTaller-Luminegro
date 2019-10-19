#include "VentanaDeJuego.h"
#include "Servidor.h"
#include "Cliente.h"
#include "ConfigManager.h"
#include "VentanaClienteInicioSesion.h"


using namespace Logger;
using namespace Common;

int main (int argc, char** argv) {

    /** Parámetros de línea de comandos para ejecutar el juego. Los que tienen asterisco son obligatorios.
     *
     * 1*: modo de aplicación: "servidor", "cliente" o "simple" (este último es temporario, para jugar de a uno sin red)
     * 2*: si el modo es del parámetro previo es "servidor", aquí en que puerto escuchará. Si es "cliente", a qué IP y
     *      puerto se conectará.
     * 3: ubicación del archivo de configuración
     * 4: nivel mínimo de logueo (DEBUG, INFO o ERROR)
     *
     * Ejemplos (todavía no se si los puertos que están abajo no hacen conflicto con otra cosa):
     *      ./ProyectoTaller-Luminegro simple 2100 config/repiola.xml    <---- puerto acá no se lee pero debe estar
     *      ./ProyectoTaller-Luminegro servidor 2100 config/repiola.xml DEBUG
     *      ./ProyectoTaller-Luminegro servidor 2101
     *      ./ProyectoTaller-Luminegro cliente 192.168.0.3:2100
     *      ./ProyectoTaller-Luminegro cliente 192.168.0.3:2100 config/repiola.xml
     *
     **/

    //Inicializo el controlador de parámetros
    ConfigManager configManager = ConfigManager(argc, argv);
    Estado estado;

    // Valida que tenga la cantidad mínima de parámetros
    estado = configManager.ValidarParametros();
    if (estado != Estado::OK) {
        ConfigManager::MostrarError(estado);
        ConfigManager::MostrarUsoPrograma();
        return EXIT_FAILURE;
    }

    // Carga archivo de configuración
    estado = configManager.CargarArchivoConfiguracion();
    if (estado != Estado::OK) {
        ConfigManager::MostrarError(estado);
        ConfigManager::MostrarUsoPrograma();
        return EXIT_FAILURE;
    }

    // Carga el nivel de logueo
    configManager.ConfigurarLogger();
    // En cualquier clase que haya que utilizar el logger, se lo instancia así (aunque no es necesario instanciarlo)
    Log *logueador  =  Log::ObtenerInstancia();

    if (strcmp(argv[1], "servidor") == 0) {
        // SERVIDOR

        logueador->Info("Se inicia el juego en modo servidor");

        Servidor servidor(1, argv[2]);

        servidor.correr(&configManager.archivoConfig);

    } else if (strcmp(argv[1], "cliente") == 0) {
        // CLIENTE
        logueador->Info("Se inicia el juego en modo cliente");

        VentanaClienteInicioSesion ventanaClienteInicioSesion;

        if (ventanaClienteInicioSesion.getEstado() == VentanaClienteInicioSesion::ESTADO_ERROR) {
            // Ya logueado en el objeto
            return EXIT_FAILURE;
        }

        ventanaClienteInicioSesion.pedirCredenciales();

        /* INICIO - La siguiente rutina simula cierta espera, da error de contraseña, pide credenciales nuevamente
         * y finalmente conecta. */
        ventanaClienteInicioSesion.mostrarMensaje("Conectando...",
                VentanaClienteInicioSesion::MENSAJE_TIPO_INFORMATIVO);

        ventanaClienteInicioSesion.demorar(2000);
        ventanaClienteInicioSesion.mostrarMensaje("Error en clave, es usted hacker?",
                                                  VentanaClienteInicioSesion::MENSAJE_TIPO_ERROR);
        ventanaClienteInicioSesion.demorar(3000);
        ventanaClienteInicioSesion.resetear();
        ventanaClienteInicioSesion.pedirCredenciales();
        ventanaClienteInicioSesion.mostrarMensaje("Conectando...",
                VentanaClienteInicioSesion::MENSAJE_TIPO_INFORMATIVO);

        ventanaClienteInicioSesion.demorar(2000);
        /* FIN */

        string usuario = ventanaClienteInicioSesion.getUsuario();
        string clave = ventanaClienteInicioSesion.getClave();

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

        Cliente cliente;
        cliente.inicializar(direccionIP, puerto, &configManager.archivoConfig);

        ventanaClienteInicioSesion.cerrar();
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

        int retorno = ventana.abrir(&configManager.archivoConfig);

        logueador->Info("Fin del juego");

        return retorno;

    } else {

        logueador->Error("Parámetros incorrectos, no se inició ni en modo servidor ni en modo cliente");
        cerr << "ERROR: Parámetros de invocación incorrectos" << endl;
        cerr << "Para modo Servidor:" << endl;
        cerr << "\t./<ejecutable> servidor <puerto> <(opcional)ruta config> <(opcional)nivel log>" << endl;
        cerr << "Para modo Cliente:" << endl;
        cerr << "\t./<ejecutable> cliente <ipServidor:puerto> <(opcional)ruta config> <(opcional)nivel log>" << endl;
        //cerr <<
        return EXIT_FAILURE;
    }
}
