#include "Common.h"
#include <sys/stat.h>
#include <iostream>

using namespace std;

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

void Utiles::Common::MostrarUsoPrograma() {
    cout << "--------------------------------" << endl;
    cout << "Forma de invocación del programa" << endl;
    cout << "--------------------------------" << endl;
    cout << "Para modo Servidor:" << endl;
    cout << "\t./<ejecutable> servidor <puerto> <(opcional)ruta config> <(opcional)nivel log>" << endl;
    cout << "Para modo Cliente:" << endl;
    cout << "\t./<ejecutable> cliente <ipServidor:puerto> <(opcional)ruta config> <(opcional)nivel logl>" << endl;
}

void Utiles::Common::MostrarError(EstadoAplicacion estado, const string& mensajeAux) {
    cout << MensajesDeError(estado) << " " << mensajeAux;
}

string Utiles::Common::MensajesDeError(EstadoAplicacion estado) {
    string mensaje;

    switch (estado) {
        case EstadoAplicacion::ErrorParametrosIncorrectos:
            mensaje = "ERROR: Parámetros de invocación incorrectos";
            break;
        case EstadoAplicacion::ErrorFaltanParametros:
            mensaje = "ERROR: Faltan parámetros de invocación";
            break;
        case EstadoAplicacion::ErrorArchivoConfiguracion:
            mensaje = "ERROR: No se pudo abrir el archivo de configuración";
            break;
        case EstadoAplicacion::ErrorModoServidorPuertoInvalido:
            mensaje = "ERROR: el parámetro ingresado como puerto es inválido";
            break;
        case EstadoAplicacion::ErrorModoClienteIpOPuertoInvalido:
            mensaje = "ERROR: el parámetro ingresado como puerto:ip es inválido";
            break;
        case EstadoAplicacion::ErrorModoServidorNoPudoAbrirSesionEnPuerto:
            mensaje = "ERROR: no se pudo abrir la conexión en el puerto indicado";
            break;
        case EstadoAplicacion::ErrorClienteNoPudoConectarAServidor:
            mensaje = "ERROR: no se pudo conectar al servidor.\n";
            mensaje += "Por favor verifique que el servidor esté corriendo y lo haga en la ip y puerto indicados";
        default:
            break;
    }
    return mensaje;
}
