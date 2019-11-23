#include "../comunicacion/MensajeServidor.h"
#include "VistaEstado.h"

VistaEstado::VistaEstado(Renderizador *renderizador, pugi::xml_document *archiConfig, int maxVida, std::string nombreJugador, int numeroJugador) {
    this->renderizador = renderizador;
    this->maxVida = maxVida;
    this->nombreJugador = nombreJugador;

    std::string pathIcono;

    switch(numeroJugador){
        case 0: //Jugador 1
            pathIcono = archiConfig->child("configuracion").child("escenario")
                    .child("protagonistas").child("protagonista1").child_value("icono");
            encuadreIcono = Encuadre(10, 10, 45, 45);
            encuadreNombre = Encuadre(60, 30, 200, 30);
            break;
        case 1: //Jugador 2
            pathIcono = archiConfig->child("configuracion").child("escenario")
                    .child("protagonistas").child("protagonista2").child_value("icono");
            encuadreIcono = Encuadre(410, 10, 45, 45);
            encuadreNombre = Encuadre(460, 30, 200, 30);
            break;
        case 2: //Jugador 3
            pathIcono = archiConfig->child("configuracion").child("escenario")
                    .child("protagonistas").child("protagonista3").child_value("icono");
            encuadreIcono = Encuadre(10, 60, 45, 45);
            encuadreNombre = Encuadre(60, 80, 200, 30);
            break;
        case 3: //Jugador 4
            pathIcono = archiConfig->child("configuracion").child("escenario")
                    .child("protagonistas").child("protagonista4").child_value("icono");
            encuadreIcono = Encuadre(410, 60, 45, 45);
            encuadreNombre = Encuadre(460, 80, 200, 30);
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
    texturaIcono.copiarseEn(renderizador, encuadreIcono);
}
