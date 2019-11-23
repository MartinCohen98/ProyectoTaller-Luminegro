#ifndef PROYECTOTALLER_LUMINEGRO_MENSAJEINICIOPARTIDA_H
#define PROYECTOTALLER_LUMINEGRO_MENSAJEINICIOPARTIDA_H


#include <string>
const int MAX_CARACTERES = 10;
int const MAX_JUGADORES = 4;

class MensajeInicioPartida {
private:
    char jugadores[MAX_JUGADORES][MAX_CARACTERES];
    int nivelInicio;
    int vidaMax;
    int8_t cantidadJugadores;
public:
    MensajeInicioPartida();
    void setNombreJugador(int numeroJugador, std::string nombre);
    void setNivelInicial(int nivel);
    void setVidaMax(int vidaMaxima);
    void setCantidadJugadoresPartida(int8_t cantidad);
    std::string getNombreJugador(int numeroJugador);
    int getNivelInicial();
    int getVidaMax();
    int8_t getCantidadJugadoresPartida();

};


#endif //PROYECTOTALLER_LUMINEGRO_MENSAJEINICIOPARTIDA_H
