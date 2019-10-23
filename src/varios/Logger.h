
#ifndef LUMINEGRO_LOGGER_H
#define LUMINEGRO_LOGGER_H

#include <string>
#include <fstream>
#include <pthread.h>

namespace Logger {

using namespace std;
    enum class Severidad {
        DEBUG,
        INFO,
        ERROR
    };

    class Log{
    public:
        static Log *ObtenerInstancia();
        static bool InicializarLog(string severidadMinima, string rutaArchivo, string modoInicio = "N/A", char caracterSeparador = ',');
        void Info(string mensaje);
        void Debug(string mensaje);
        void Error(string mensaje);
        void SetSeveridadMinima(string severidad);
    private:
        Log(string severidadMinima, string rutaArchivo, string modoInicio = "N/A", char caracterSeparador = ',');
        static Log *instancia;
        ofstream archivoLog;
        Severidad severidadMinima;
        uint64_t idSesion;
        void escribirLog(const string& mensaje, string severidad);
        char caracterSeparador;
        pthread_mutex_t mutexLogger;
        string modoInicio;          //Cliente/Servidor
    };

}
#endif //LUMINEGRO_LOGGER_H
