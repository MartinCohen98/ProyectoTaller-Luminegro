//
// Created by nico on 27/11/19.
//

#ifndef PROYECTOTALLER_LUMINEGRO_VISTATRANSICIONJUEGO_H
#define PROYECTOTALLER_LUMINEGRO_VISTATRANSICIONJUEGO_H


#include <grafica/Renderizador.h>
#include <varios/InfoJugador.h>
#include <comunicacion/MensajeInicioPartida.h>

const SDL_Color colorRojoOscuro = {0x80,0,0,0xFF};
const SDL_Color colorAmarilloPatito = {0xFF, 0xFF, 0x00, 0xFF};
const SDL_Color colorNegroNoche = {0x00,0x00,0x00,0xFF};
const SDL_Color colorPetroleo = {0x00, 0x80, 0x80, 0xFF};

class VistaTransicionJuego {
public:
    static void CambioDeNivel(int nivel, Renderizador *renderizador, InfoJugador *infoJugadores,
                  MensajeInicioPartida mensajeInicio);
};


#endif //PROYECTOTALLER_LUMINEGRO_VISTATRANSICIONJUEGO_H
