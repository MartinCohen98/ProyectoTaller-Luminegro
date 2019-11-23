#include <comunicacion/MensajeServidor.h>
#include "VistaEstado.h"

VistaEstado::VistaEstado(Renderizador *renderizador, pugi::xml_document *archiConfig, int maxVida, std::string nombreJugador, int numeroJugador) {
    this->renderizador = renderizador;
    this->maxVida = maxVida;
    this->nombreJugador = nombreJugador;

    std::string pathIcono;

    switch(numeroJugador){
        case tipoDeSprite::Jugador1:
            pathIcono = archiConfig->child("configuracion").child("escenario")
                    .child("protagonistas").child("protagonista1").child_value("icono");
            encuadreIcono = Encuadre(10, 10, 40, 40);
            encuadreNombre = Encuadre(50, 30, 150, 30);
            break;
        case tipoDeSprite::Jugador2:
            pathIcono = archiConfig->child("configuracion").child("escenario")
                    .child("protagonistas").child("protagonista2").child_value("icono");
            encuadreIcono = Encuadre(210, 10, 40, 40);
            encuadreNombre = Encuadre(250, 30, 150, 30);
            break;
        case tipoDeSprite::Jugador3:
            pathIcono = archiConfig->child("configuracion").child("escenario")
                    .child("protagonistas").child("protagonista3").child_value("icono");
            encuadreIcono = Encuadre(10, 60, 40, 40);
            encuadreNombre = Encuadre(50, 80, 150, 30);
            break;
        case tipoDeSprite::Jugador4:
            archiConfig->child("configuracion").child("escenario")
                    .child("protagonistas").child("protagonista4").child_value("icono");
            encuadreIcono = Encuadre(210, 60, 40, 40);
            encuadreNombre = Encuadre(250, 80, 150, 30);
            break;
        default:
            break;
    }

    //Carga de imágen
    Imagen icono;
    icono.cargar(pathIcono.c_str(),Imagen::TIPO_ICONO);
    texturaIcono.texturizar(renderizador, icono);
}

void VistaEstado::renderizar(InfoJugador estadoJugador) {
    //Renderiza ícono
    texturaIcono.copiarseEn(renderizador, encuadreIcono, Encuadre(0,0,30,30));
}
