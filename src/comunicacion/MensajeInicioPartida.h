#ifndef PROYECTOTALLER_LUMINEGRO_MENSAJEINICIOPARTIDA_H
#define PROYECTOTALLER_LUMINEGRO_MENSAJEINICIOPARTIDA_H


#include <string>

class MensajeInicioPartida {
private:
    static const int MAX_CARACTERES = 10;
    static const int MAX_JUGADORES = 4;
    char jugadores[MAX_JUGADORES][MAX_CARACTERES];
    int nivelInicio;
    int vidaMax;
public:
    MensajeInicioPartida();
    MensajeInicioPartida( int nivelInicio, int vidaMax);
    void setNombreJugador(int numeroJugador, std::string nombre);
    std::string getNombreJugador(int numeroJugador);
    int getNivelInicio();
    int getVidaMax();
};


#endif //PROYECTOTALLER_LUMINEGRO_MENSAJEINICIOPARTIDA_H
