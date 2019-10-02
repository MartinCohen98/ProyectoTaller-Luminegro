
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
        static bool InicializarLog(string severidadMinima, string rutaArchivo, char caracterSeparador = ',');
        void Info(string mensaje);
        void Debug(string mensaje);
        void Error(string mensaje);
        void SetSeveridadMinima(string severidad);
    private:
        Log(string severidadMinima, string rutaArchivo, char caracterSeparador = ',');
        static Log *instancia;
        ofstream archivoLog;
        Severidad severidadMinima;
        uint64_t idSesion;
        void escribirLog(string mensaje, string severidad);
        char caracterSeparador;
        pthread_mutex_t mutexLogger;
    };

}
#endif //LUMINEGRO_LOGGER_H
