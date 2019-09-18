#include "logger.h"

#include <fstream>
#include <ctime>
#include <sstream>
#include <iostream>

namespace Logger{
	const int MAX_LENGTH_BUFFER_FECHA = 30;

	Log::Log(const string severidadMin) {

	    // Convierto el string que lee del XML a el enum correspondiente
	    if (severidadMin == "DEBUG") {
            this->severidadMinima = Severidad::DEBUG;

        } else if (severidadMin == "INFO") {
            this->severidadMinima = Severidad::INFO;

        } else if (severidadMin == "ERROR") {
            this->severidadMinima = Severidad::ERROR;
        }

		//Obtención del día para crear el archivo
		//TO DO: Que se elija donde generar el archivo y qué formato
		time_t now = time(0);
	    char nombreArchivo[MAX_LENGTH_BUFFER_FECHA];
	    strftime (nombreArchivo,MAX_LENGTH_BUFFER_FECHA,"%Y-%m-%d.log",localtime(&now));
	    this->pathLoggeo = nombreArchivo;
	}

	void Log::Debug(string mensaje){
		if(this->severidadMinima == Severidad::DEBUG)
			this->loggear(mensaje, "DEBUG");
	}

	void Log::Info(string mensaje){
		if(this->severidadMinima <= Severidad::INFO)
			this->loggear(mensaje, "INFO");
	}

	void Log::Error(string mensaje){
		if(this->severidadMinima <= Severidad::ERROR)
			this->loggear(mensaje, "ERROR");
	}

	void Log::loggear(string mensaje, string severidad){
		ofstream archivoLog;
		char buffer[MAX_LENGTH_BUFFER_FECHA];
		time_t now = time(0);

		archivoLog.open(this->pathLoggeo, ios::app);
		//Carga en buffer la fecha pero le faltan los milisegundos
		strftime (buffer,MAX_LENGTH_BUFFER_FECHA,"%Y-%m-%d %R.",localtime(&now));
		archivoLog << buffer << now %1000;
		archivoLog << ", " << severidad;
		archivoLog << ", " << mensaje << endl;
		archivoLog.close();
	}
}

