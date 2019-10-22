#ifndef PROYECTOTALLER_LUMINEGRO_MENSAJECREDENCIALES_H
#define PROYECTOTALLER_LUMINEGRO_MENSAJECREDENCIALES_H

#include <string>

class MensajeCredenciales {

private:
    std::string usuario;
    std::string clave;
    int estado;

public:
    static const int ESTADO_AUTENTICADO = 1;
    static const int ESTADO_NO_AUTENTICADO = 2;

    void setUsuario(std::string valor);
    void setClave(std::string valor);
    void setEstado(int valor);
    std::string getUsuario();
    std::string getClave();
    int getEstado();
};


#endif //PROYECTOTALLER_LUMINEGRO_MENSAJECREDENCIALES_H
