#include "ConfigManager.h"
#include "Logger.h"
#include "Common.h"
#include <iostream>
#include <cstring>

using namespace std;
using namespace Utiles;
using namespace Logger;

const int CANTIDAD_MINIMA_PARAMETROS = 3; //Programa servidor/cliente puerto/ip:puerto

EstadoAplicacion ConfigManager::ValidarParametros() {
    EstadoAplicacion estado = EstadoAplicacion::OK;

    if(argc < CANTIDAD_MINIMA_PARAMETROS) {
        if(argc == 2 && strcmp(argv[1], "simple") == 0) {
            modo = Modo::Simple;
        }else {
            Log::ObtenerInstancia()->Error("Faltan parámetros de invocación");
            estado = EstadoAplicacion::ErrorFaltanParametros;
        }
    }else {
        if (strcmp(argv[1], "servidor") == 0) {
            //SERVIDOR: Validar que el siguiente parámetro sea el número de puerto
            puerto = argv[2];
            if(Common::EsNumero(puerto)) {
                modo = Modo::Servidor;
            }else{
                Log::ObtenerInstancia()->Error("El puerto ingresado(" + puerto + ") para modo servidor es inválido");
                estado = EstadoAplicacion::ErrorModoServidorPuertoInvalido;
            }
        } else if (strcmp(argv[1], "cliente") == 0) {
            //CLIENTE: Validar que el siguiente parámetro sea la ip:puerto en ese formato (ej: "10.1.4.25:8028")
            auto vectorTemp = Common::Split(argv[2], ':');
            if(vectorTemp.size() == 2 && Common::IpValida(vectorTemp[0]) && Common::EsNumero(vectorTemp[1])){
                ip = vectorTemp[0];
                puerto = vectorTemp[1];
                modo = Modo::Cliente;
            }else{
                string msjError = "La ip:puerto ingresados (";
                msjError += argv[2];
                msjError += ") para modo cliente es inválida";
                Log::ObtenerInstancia()->Error(msjError);
                estado = EstadoAplicacion::ErrorModoClienteIpOPuertoInvalido;
            }
        }
        else if (strcmp(argv[1], "simple") == 0)
            modo = Modo::Simple;
        else {
            Log::ObtenerInstancia()->Error("Parámetros incorrectos, no se inició ni en modo servidor ni en modo cliente");
            estado = EstadoAplicacion::ErrorParametrosIncorrectos;
        }
    }
    return estado;
}

EstadoAplicacion ConfigManager::CargarArchivoConfiguracion() {
    // Archivo de configuración
    pugi::xml_parse_result archiConfigCarga;
    bool cargarArchivoConfigPorDefecto = true;

    // Envió por parámetro la ubicación del archivo?
    if (argc >= 4) {
        // Si
        archiConfigCarga = archivoConfig.load_file(argv[3]);

        if (archiConfigCarga.status == 0) {
            // Cargó bien el config por parámetro, no busca el config default
            cargarArchivoConfigPorDefecto = false;

        } else {
            // No cargó bien el config por parámetro, buscará el config default
            string mensajeError = "No se pudo abrir el archivo de configuración \"";

            mensajeError.append(argv[3]);
            mensajeError.append("\". Se detectó el problema en el byte " + to_string(archiConfigCarga.offset)
                                + ". Mensaje de error: " + archiConfigCarga.description());
            Logger::Log::ObtenerInstancia()->Error(mensajeError);
        }
    }
    // Ve si tiene que buscar el config por defecto
    if (cargarArchivoConfigPorDefecto) {
        string rutaConfig;

        if(Common::ExisteArchivo("config/default.xml"))
            rutaConfig = "config/default.xml";
        else if(Common::ExisteArchivo("../config/default.xml"))
            rutaConfig = "../config/default.xml";
        else
            rutaConfig = "default.xml";
        archiConfigCarga = archivoConfig.load_file(rutaConfig.c_str());

        if (archiConfigCarga.status != 0) {
            // Rompió hasta el config por defecto, más no se puede hacer
            string mensajeError = "No se pudo abrir el archivo de configuración por defecto: \"";
            mensajeError.append(rutaConfig);
            mensajeError.append("\". Se detectó el problema en el byte " + to_string(archiConfigCarga.offset)
                                + ". Mensaje de error: " + archiConfigCarga.description());

            Logger::Log::ObtenerInstancia()->Error(mensajeError);
            return EstadoAplicacion::ErrorArchivoConfiguracion;
        }
    }
    return EstadoAplicacion::OK;
}

ConfigManager::ConfigManager(int argc, char **argv) {
    this->argc = argc;
    this->argv = argv;
    this->archivoConfig.empty();
    this->modo = Modo::Simple;
}

void ConfigManager::ConfigurarLogger() {
    string logLevel;
    string modoInicio;
    // Lo envió por parámetro?
    if (argc >= 5) {
        // Si
        logLevel = argv[4];
    } else {
        // No, leo del XML
        logLevel = archivoConfig.child("configuracion").child("log").child_value("level");
    }
    //Modo inicio del juego
    if(modo == Modo::Cliente)
        modoInicio = "Cliente";
    else if(modo == Modo::Servidor)
        modoInicio = "Servidor";
    else
        modoInicio = "N/A";

    // Se inicializa el Logger acá y así queda para el resto de la aplicación.
    if (!Log::InicializarLog(logLevel, "", modoInicio)) {
        //Si ya se había inicializado el logger (por error en apertura de config) al menos le setea el nivel de log
        Log::ObtenerInstancia()->SetSeveridadMinima(logLevel);
    }
}

Modo ConfigManager::ModoAplicacion() {
    return this->modo;
}

std::string ConfigManager::PuertoServidor() {
    return this->puerto;
}

std::string ConfigManager::DireccionIpServidor() {
    return this->ip;
}
