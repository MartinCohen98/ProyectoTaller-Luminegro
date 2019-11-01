#ifndef PROYECTOTALLER_LUMINEGRO_USUARIOYCLAVE_H
#define PROYECTOTALLER_LUMINEGRO_USUARIOYCLAVE_H

#include <string>

class UsuarioYClave {
private:
    std::string nombre;
    std::string clave;
    bool fueAutenticado = false;

public:
    UsuarioYClave();
    void setValores(std::string nombre, std::string clave);
    bool validar(std::string nombre, std::string clave);
};


#endif //PROYECTOTALLER_LUMINEGRO_USUARIOYCLAVE_H
