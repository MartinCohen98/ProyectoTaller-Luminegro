//
// Created by nico on 24/10/19.
//

#ifndef PROYECTOTALLER_LUMINEGRO_COMMON_H
#define PROYECTOTALLER_LUMINEGRO_COMMON_H

#include <string>
#include <vector>

namespace Utiles {

    class Common {
    public:
        static bool EsNumero(const std::string &cadena);
        static bool IpValida(const std::string &dirIP);
        static std::vector<std::string> Split(const std::string &cadena, char separador);
    };

}

#endif //PROYECTOTALLER_LUMINEGRO_COMMON_H
