#ifndef PROYECTOTALLER_LUMINEGRO_COMMON_H
#define PROYECTOTALLER_LUMINEGRO_COMMON_H

#include <string>
#include <vector>

namespace Utiles {

    enum EstadoAplicacion{
        OK,
        ErrorFaltanParametros,
        ErrorParametrosIncorrectos,
        ErrorArchivoConfiguracion,
        ErrorModoServidorPuertoInvalido,
        ErrorModoServidorNoPudoAbrirSesionEnPuerto,
        ErrorModoClienteIpOPuertoInvalido,
        ErrorClienteNoPudoConectarAServidor
    };

    class Common {
    public:
        static bool EsNumero(const std::string &cadena);
        static bool IpValida(const std::string &dirIP);
        static std::vector<std::string> Split(const std::string &cadena, char separador);
        static bool ExisteArchivo(const std::string &ruta);
        static void MostrarUsoPrograma();
        static void MostrarError(Utiles::EstadoAplicacion estado, const std::string& mensajeAux = "");
        static std::string MensajesDeError(Utiles::EstadoAplicacion estado);
    };

}

#endif //PROYECTOTALLER_LUMINEGRO_COMMON_H
