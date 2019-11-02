#ifndef PROYECTOTALLER_LUMINEGRO_MENSAJECREDENCIALES_H
#define PROYECTOTALLER_LUMINEGRO_MENSAJECREDENCIALES_H

#include "string.h"
#include <string>

class MensajeCredenciales {

private:
    static const int MAX = 10;

    char usuario[MAX];
    char clave[MAX];
    int estado = ESTADO_ESPERANDO_CONEXIONES;
    int nivelInicial;

public:
    static const int ESTADO_ESPERANDO_CONEXIONES = 0;
    static const int ESTADO_NO_MAS_JUGADORES_PERMITIDOS = 1;
    static const int ESTADO_AUTENTICADO = 2;
    static const int ESTADO_USUARIO_O_CLAVE_ERRONEOS = 3;
    static const int ESTADO_USUARIO_YA_CONECTADO = 4;

    static const int UNA_CREDENCIAL_LONGITUD_MAXIMA = MAX;

    void setUsuario(const std::string& valor);
    void setClave(std::string valor);
    void setEstado(int valor);
    void setNivelInicial(int nivel);
    std::string getUsuario();
    std::string getClave();
    int getEstado();
    int getNivelInicial();
};


#endif //PROYECTOTALLER_LUMINEGRO_MENSAJECREDENCIALES_H
