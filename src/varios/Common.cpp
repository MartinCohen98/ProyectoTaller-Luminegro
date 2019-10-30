#include "Common.h"
#include <sys/stat.h>

bool Utiles::Common::EsNumero(const std::string &cadena) {
    for (char c: cadena)
        if (!isdigit(c))
            return false;
    return true;
}

bool Utiles::Common::IpValida(const std::string &dirIP) {
    auto elementos = Split(dirIP,'.');
    if(elementos.size() != 4)
        return false;
    for(const std::string& e: elementos)
        if(!EsNumero(e) || stoi(e) > 255)
            return false;
    return true;
}

std::vector<std::string> Utiles::Common::Split(const std::string &cadena, char separador) {
    std::vector<std::string> salida;
    auto indice = 0;
    auto posicionEncontrada = cadena.find(separador);

    while(posicionEncontrada != std::string::npos){
        salida.push_back(cadena.substr(indice, posicionEncontrada - indice));
        indice = ++posicionEncontrada;
        posicionEncontrada = cadena.find(separador, posicionEncontrada);
    }
    salida.push_back(cadena.substr(indice, cadena.length()));
    return salida;
}

bool Utiles::Common::ExisteArchivo(const std::string &ruta) {
    struct stat buffer;
    return stat(ruta.c_str(), &buffer) == 0;
}

