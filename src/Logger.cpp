//
// Created by nico on 18/9/19.
//

#include <ctime>
#include <iostream>
#include "Logger.h"
#include <chrono>

using namespace Logger;
using namespace chrono;

Log *Log::instancia = NULL;
const int MAX_LENGTH_BUFFER_FECHA = 30;


Log *Log::ObtenerInstancia() {
    if(!instancia) {

        instancia = new Log("ERROR", "" );
    }
    return instancia;
}

bool Log::InicializarLog(string severidadMinima, string rutaArchivo, char caracterSeparador) {
    if(instancia)
        return false;

    instancia = new Log(severidadMinima, rutaArchivo, caracterSeparador);
    return true;
}

Log::Log(string severidadMinima, string rutaArchivo, char caracterSeparador) {
    //Carga por defecto como caracter separador la coma
    this->caracterSeparador = caracterSeparador;
    //Inicializa severidad mínima (si no hay coincidencia, por defecto severidad ERROR)
    if (severidadMinima == "DEBUG") {
        this->severidadMinima = Severidad::DEBUG;

    } else if (severidadMinima == "INFO") {
        this->severidadMinima = Severidad::INFO;

    } else
        this->severidadMinima = Severidad::ERROR;

    //Genera el id de sesión
    this->idSesion = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

    //Abre el archivo (si no hay ruta archivo, crea una con la fecha como nombre de archivo por defecto)
    if(rutaArchivo.empty()){
        time_t hoy = time(0);
        char nombreArchivo[MAX_LENGTH_BUFFER_FECHA];
        strftime (nombreArchivo,MAX_LENGTH_BUFFER_FECHA,"%Y-%m-%d.log",localtime(&hoy));
        rutaArchivo = nombreArchivo;
    }
    this->archivoLog.open(rutaArchivo, ios::app);
}


void Log::Debug(string mensaje) {
    if(this->severidadMinima == Severidad::DEBUG)
        escribirLog(mensaje, "DEBUG");
}

void Log::Info(string mensaje) {
    if(this->severidadMinima <= Severidad::INFO)
        escribirLog(mensaje, "INFO");
}

void Log::Error(std::string mensaje) {
    escribirLog(mensaje, "ERROR");
}

void Log::escribirLog(string mensaje, string severidad) {
    char buffer[MAX_LENGTH_BUFFER_FECHA];
    time_t hoy = time(0);
    //Carga en buffer la fecha y luego los milisegundos, luego la severidad, el id de ejecución y por último el mensaje
    strftime (buffer,MAX_LENGTH_BUFFER_FECHA,"%Y-%m-%d %R.",localtime(&hoy));
    archivoLog << buffer << hoy % 1000;
    archivoLog << this->caracterSeparador << severidad;
    archivoLog << this->caracterSeparador<< this->idSesion;
    archivoLog << this->caracterSeparador << mensaje << endl;
    //Se asegura de enviar al archivo lo que cargó en el buffer
    this->archivoLog.flush();
}




