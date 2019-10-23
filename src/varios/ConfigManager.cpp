//
// Created by nico on 6/10/19.
//
#include "ConfigManager.h"
#include "Logger.h"
#include <iostream>
#include <cstring>

using namespace std;
using namespace Common;
using namespace Logger;

const int CANTIDAD_MINIMA_PARAMETROS = 3; //Programa servidor/cliente puerto/ip:puerto

Estado ConfigManager::ValidarParametros() {
    if(this->argc < CANTIDAD_MINIMA_PARAMETROS) {
        if(argc == 2 && strcmp(argv[1], "simple") == 0) {
            this->modo = Modo::Simple;
            return Estado::OK;
        }
        Log::ObtenerInstancia()->Error("Faltan parámetros de invocación");
        return Estado::ErrorFaltanParametros;
    }
    //Validar acá que si viene en modo servidor o cliente, debe indicar para el primero el puerto y para el otro ip y puerto
    if(strcmp(argv[1], "servidor") == 0)
        this->modo = Modo::Servidor;
    else if(strcmp(argv[1], "cliente") == 0)
        this->modo = Modo::Cliente;
    else if (strcmp(argv[1], "simple") == 0)
        this->modo = Modo::Simple;
    else{
        Log::ObtenerInstancia()->Error("Parámetros incorrectos, no se inició ni en modo servidor ni en modo cliente");
        return Estado::ErrorParametrosIncorrectos;
    }
    return Estado::OK;
}


Estado ConfigManager::CargarArchivoConfiguracion() {
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
        archiConfigCarga = archivoConfig.load_file("config/default.xml");

        if (archiConfigCarga.status != 0) {
            // Rompió hasta el config por defecto, más no se puede hacer
            string mensajeError = "No se pudo abrir el archivo de configuración por defecto: \"";
            mensajeError.append(argv[3]);
            mensajeError.append("\". Se detectó el problema en el byte " + to_string(archiConfigCarga.offset)
                                + ". Mensaje de error: " + archiConfigCarga.description());

            Logger::Log::ObtenerInstancia()->Error(mensajeError);
            return Estado::ErrorArchivoConfiguracion;
        }
    }
    return Estado::OK;
}

ConfigManager::ConfigManager(int argc, char **argv) {
    this->argc = argc;
    this->argv = argv;
    this->archivoConfig.empty();
}



void ConfigManager::MostrarUsoPrograma() {
    cout << "--------------------------------" << endl;
    cout << "Forma de invocación del programa" << endl;
    cout << "--------------------------------" << endl;
    cout << "Para modo Servidor:" << endl;
    cout << "\t./<ejecutable> servidor <puerto> <(opcional)ruta config> <(opcional)nivel log>" << endl;
    cout << "Para modo Cliente:" << endl;
    cout << "\t./<ejecutable> cliente <ipServidor:puerto> <(opcional)ruta config> <(opcional)nivel logl>" << endl;
}

void ConfigManager::MostrarError(Estado estado) {
    switch(estado){
        case Estado::ErrorParametrosIncorrectos:
            cout << "ERROR: Parámetros de invocación incorrectos" << endl;
            break;
        case Estado::ErrorFaltanParametros:
            cout << "ERROR: Faltan parámetros de invocación" << endl;
            break;
        case Estado::ErrorArchivoConfiguracion:
            cout << "ERROR: No se pudo abrir el archivo de configuración" << endl;
            break;
        default:
            break;
    }
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
