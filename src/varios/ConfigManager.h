#ifndef PROYECTOTALLER_LUMINEGRO_CONFIGMANAGER_H
#define PROYECTOTALLER_LUMINEGRO_CONFIGMANAGER_H

#include "../../lib/pugixml/pugixml.hpp"
#include "Common.h"

namespace Utiles{

    enum class Modo{
        Servidor,
        Cliente,
        Simple  //para debuggear simplemente
    };

    class ConfigManager {
    public:
        ConfigManager(int argc, char **argv);
        Utiles::EstadoAplicacion CargarArchivoConfiguracion();
        Utiles::EstadoAplicacion ValidarParametros();
        void ConfigurarLogger();
        pugi::xml_document archivoConfig;
        Modo ModoAplicacion();
        std::string PuertoServidor();
        std::string DireccionIpServidor();
    private:
        int argc;
        char **argv;
        Modo modo;
        std::string puerto;
        std::string ip;
    };
}



#endif //PROYECTOTALLER_LUMINEGRO_CONFIGMANAGER_H
