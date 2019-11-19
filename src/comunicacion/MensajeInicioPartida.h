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
    void setNombreJugador(int numeroJugador, std::string nombre);
    void setNivelInicial(int nivel);
    void setVidaMax(int vidaMaxima);
    std::string getNombreJugador(int numeroJugador);
    int getNivelInicial();
    int getVidaMax();
};


#endif //PROYECTOTALLER_LUMINEGRO_MENSAJEINICIOPARTIDA_H
