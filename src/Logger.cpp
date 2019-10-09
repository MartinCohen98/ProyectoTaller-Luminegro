//
// Created by nico on 18/9/19.
//

#include <ctime>
#include <iostream>
#include "Logger.h"
#include <chrono>
#include <pthread.h>

using namespace Logger;
using namespace chrono;

Log *Log::instancia = nullptr;
const int MAX_LENGTH_BUFFER_FECHA = 30;
//pthread_mutex_t mutexLogger;

Log *Log::ObtenerInstancia() {
    if(!instancia) {

        instancia = new Log("ERROR", "" );
    }
    return instancia;
}

//Se puede inicializar una sola vez en toda la aplicación, y ya deja creada la instancia.

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
    this->SetSeveridadMinima(severidadMinima);

    //Genera el id de sesión
    this->idSesion = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

    //Abre el archivo (si no hay ruta archivo, crea una con la fecha como nombre de archivo por defecto)
    if(rutaArchivo.empty()){
        time_t hoy = time(nullptr);
        char nombreArchivo[MAX_LENGTH_BUFFER_FECHA];
        strftime (nombreArchivo,MAX_LENGTH_BUFFER_FECHA,"%Y-%m-%d.log",localtime(&hoy));
        rutaArchivo = nombreArchivo;
    }
    this->archivoLog.open(rutaArchivo, ios::app);
    //Inicia el mutex
    pthread_mutex_init(&this->mutexLogger, NULL);
}


void Log::Debug(string mensaje) {
    if(this->severidadMinima == Severidad::DEBUG)
        escribirLog(std::move(mensaje), "DEBUG");
}

void Log::Info(string mensaje) {
    if(this->severidadMinima <= Severidad::INFO)
        escribirLog(std::move(mensaje), "INFO");
}

void Log::Error(std::string mensaje) {
    escribirLog(std::move(mensaje), "ERROR");
}

void Log::escribirLog(const string& mensaje, string severidad) {
    char buffer[MAX_LENGTH_BUFFER_FECHA];

    //Bloqueo el logger para que no haya otro hilo intentando escribir el archivo
    pthread_mutex_lock(&this->mutexLogger);

    //Carga en buffer la fecha y luego los milisegundos, luego la severidad, el id de ejecución y por último el mensaje
    time_t hoy = time(0);
    strftime (buffer,MAX_LENGTH_BUFFER_FECHA,"%Y-%m-%d %R.",localtime(&hoy));
    string milisegundos = to_string(hoy % 1000);
    archivoLog << buffer << string(3 - milisegundos.length(), '0').append(milisegundos);
    archivoLog << this->caracterSeparador<< this->idSesion;
    archivoLog << this->caracterSeparador << severidad;
    archivoLog << this->caracterSeparador << mensaje << endl;
    //Se asegura de enviar al archivo lo que cargó en el buffer
    this->archivoLog.flush();

    //Desbloqueo
    pthread_mutex_unlock(&this->mutexLogger);
}

void Log::SetSeveridadMinima(const string severidad) {
    //Inicializa severidad mínima (si no hay coincidencia, por defecto severidad ERROR)
    if (severidad == "DEBUG") {
        this->severidadMinima = Severidad::DEBUG;

    } else if (severidad == "INFO") {
        this->severidadMinima = Severidad::INFO;

    } else
        this->severidadMinima = Severidad::ERROR;
}




