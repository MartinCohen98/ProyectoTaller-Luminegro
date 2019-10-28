#ifndef PROYECTOTALLER_LUMINEGRO_CONFIGMANAGER_H
#define PROYECTOTALLER_LUMINEGRO_CONFIGMANAGER_H

#include "../../lib/pugixml/pugixml.hpp"
namespace Utiles{

    enum Estado{
        OK,
        ErrorFaltanParametros,
        ErrorParametrosIncorrectos,
        ErrorArchivoConfiguracion,
        ErrorModoServidorPuertoInvalido,
        ErrorModoClienteIpOPuertoInvalido,
        ErrorModoServidorNoPudoAbrirSesionEnPuerto
    };

    enum class Modo{
        Servidor,
        Cliente,
        Simple  //para debuggear simplemente
    };

    class ConfigManager {
    public:
        ConfigManager(int argc, char **argv);
        Estado CargarArchivoConfiguracion();
        Estado ValidarParametros();
        void ConfigurarLogger();
        static void MostrarUsoPrograma();
        static void MostrarError(Estado estado, std::string mensajeAux = "");
        pugi::xml_document archivoConfig;
        Modo ModoAplicacion();
        std::string PuertoServidor();
        std::string DireccionIpServidor();
        static std::string MensajesDeError(Estado estado);
    private:
        int argc;
        char **argv;
        Modo modo;
        std::string puerto;
        std::string ip;
    };
}



#endif //PROYECTOTALLER_LUMINEGRO_CONFIGMANAGER_H
