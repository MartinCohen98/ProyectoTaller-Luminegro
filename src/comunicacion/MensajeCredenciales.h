#ifndef PROYECTOTALLER_LUMINEGRO_MENSAJECREDENCIALES_H
#define PROYECTOTALLER_LUMINEGRO_MENSAJECREDENCIALES_H

#include "string.h"
#include <string>

class MensajeCredenciales {

private:
    static const int MAX = 10;

    char usuario[MAX];
    char clave[MAX];
    int estado;

public:
    static const int ESTADO_NULO = 0;
    static const int ESTADO_AUTENTICADO = 1;
    static const int ESTADO_USUARIO_O_CLAVE_ERRONEOS = 2;
    static const int ESTADO_USUARIO_YA_CONECTADO = 3;

    static const int UNA_CREDENCIAL_LONGITUD_MAXIMA = MAX;

    void setUsuario(std::string valor);
    void setClave(std::string valor);
    void setEstado(int valor);
    std::string getUsuario();
    std::string getClave();
    int getEstado();
};


#endif //PROYECTOTALLER_LUMINEGRO_MENSAJECREDENCIALES_H