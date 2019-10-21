#ifndef PROYECTOTALLER_LUMINEGRO_CONFIGMANAGER_H
#define PROYECTOTALLER_LUMINEGRO_CONFIGMANAGER_H

#include "../../lib/pugixml/pugixml.hpp"
namespace Common{

    enum Estado{
        OK,
        ErrorFaltanParametros,
        ErrorParametrosIncorrectos,
        ErrorArchivoConfiguracion
    };

    class ConfigManager {
    public:
        ConfigManager(int argc, char **argv);
        Estado CargarArchivoConfiguracion();
        Estado ValidarParametros();
        void ConfigurarLogger();
        static void MostrarUsoPrograma();
        static void MostrarError(Estado estado);
        pugi::xml_document archivoConfig;
    private:
        int argc;
        char **argv;
        //char *puerto;
        //string ip;
    };
}



#endif //PROYECTOTALLER_LUMINEGRO_CONFIGMANAGER_H
