#include "varios/Servidor.h"
#include "varios/Cliente.h"
#include "varios/ConfigManager.h"
#include "grafica/VentanaClienteInicioSesion.h"
#include <pthread.h>


using namespace Logger;
using namespace Common;

int main (int argc, char** argv) {

    /** Parámetros de línea de comandos para ejecutar el juego. Los que tienen asterisco son obligatorios.
     *
     * 1*: modo de aplicación: "servidor" o "cliente"
     * 2*: si el modo es del parámetro previo es "servidor", aquí en que puerto escuchará. Si es "cliente", a qué IP y
     *      puerto se conectará.
     * 3: ubicación del archivo de configuración
     * 4: nivel mínimo de logueo (DEBUG, INFO o ERROR)
     *
     * Ejemplos (el puerto a usar debe estar libre):
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

    if (configManager.ModoAplicacion() == Modo::Servidor) {
        // SERVIDOR

        logueador->Info("Se inicia el juego en modo servidor");

        std::string jugadoresCantidad = configManager.archivoConfig.child("configuracion")
                .child_value("jugadoresCantidad");

        int jugadoresCantidadInt = std::stoi(jugadoresCantidad);

        Servidor servidor(jugadoresCantidadInt, argv[2]);

        servidor.correr(&configManager.archivoConfig);

    } else if (configManager.ModoAplicacion() == Modo::Cliente) {
        // CLIENTE
        logueador->Info("Se inicia el juego en modo cliente");

        VentanaClienteInicioSesion ventanaClienteInicioSesion;

        if (ventanaClienteInicioSesion.getEstado() == VentanaClienteInicioSesion::ESTADO_ERROR) {
            // Ya logueado en el objeto
            return EXIT_FAILURE;
        }

        ventanaClienteInicioSesion.pedirCredenciales();

        // INICIO - CODIGO DE EJEMPLO: la siguiente rutina simula cierta espera, da error de contraseña, pide
        // credenciales nuevamente y finalmente hace como que conecta. */
        /*
        ventanaClienteInicioSesion.mostrarMensaje("Conectando...",
                                                  VentanaClienteInicioSesion::MENSAJE_TIPO_INFORMATIVO);

        string usuario = ventanaClienteInicioSesion.getUsuario();
        string clave = ventanaClienteInicioSesion.getClave();

        ventanaClienteInicioSesion.demorar(2000);
        ventanaClienteInicioSesion.mostrarMensaje("Error en clave, es usted hacker?",
                                                  VentanaClienteInicioSesion::MENSAJE_TIPO_ERROR);
        ventanaClienteInicioSesion.demorar(3000);
        ventanaClienteInicioSesion.resetear();
        ventanaClienteInicioSesion.pedirCredenciales();
        ventanaClienteInicioSesion.mostrarMensaje("Conectando...",
                                                   VentanaClienteInicioSesion::MENSAJE_TIPO_INFORMATIVO);

        usuario = ventanaClienteInicioSesion.getUsuario();
        clave = ventanaClienteInicioSesion.getClave();

        ventanaClienteInicioSesion.demorar(2000);
        */
        // FIN - CODIGO DE EJEMPLO

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

        ventanaClienteInicioSesion.cerrar();

        Cliente cliente;
        cliente.inicializar(direccionIP, puerto, &configManager.archivoConfig);

        socketConectado.cerrar();

        return EXIT_SUCCESS;

    } else {
        logueador->Error("Parámetros incorrectos, no se inició ni en modo servidor ni en modo cliente");
        ConfigManager::MostrarError(Estado::ErrorParametrosIncorrectos);
        ConfigManager::MostrarUsoPrograma();
        return EXIT_FAILURE;
    }
}
