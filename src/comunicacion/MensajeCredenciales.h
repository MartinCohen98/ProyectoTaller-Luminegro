#ifndef PROYECTOTALLER_LUMINEGRO_MENSAJECREDENCIALES_H
#define PROYECTOTALLER_LUMINEGRO_MENSAJECREDENCIALES_H

#include <string>

class MensajeCredenciales {

private:
    std::string usuario;
    std::string clave;
    int estado;

    void completarCredencialCaracteres(std::string *valor);

public:
    static const int ESTADO_AUTENTICADO = 1;
    static const int ESTADO_NO_AUTENTICADO = 2;

    static const int UNA_CREDENCIAL_LONGITUD_MAXIMA = 10;

    void setUsuario(std::string valor);
    void setClave(std::string valor);
    void setEstado(int valor);
    std::string getUsuario();
    std::string getClave();
    int getEstado();
};


#endif //PROYECTOTALLER_LUMINEGRO_MENSAJECREDENCIALES_H
