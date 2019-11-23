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
            encuadreNombre = Encuadre(60, 5, 200, 25);
            encuadreBarraVida = Encuadre(60, 30, 330, 25);
            break;
        case 1: //Jugador 2
            pathIcono = archiConfig->child("configuracion").child("escenario")
                    .child("protagonistas").child("protagonista2").child_value("icono");
            encuadreIcono = Encuadre(410, 10, 45, 45);
            encuadreNombre = Encuadre(460, 5, 200, 30);
            encuadreBarraVida = Encuadre(460, 30, 330, 25);
            break;
        case 2: //Jugador 3
            pathIcono = archiConfig->child("configuracion").child("escenario")
                    .child("protagonistas").child("protagonista3").child_value("icono");
            encuadreIcono = Encuadre(10, 60, 45, 45);
            encuadreNombre = Encuadre(60, 60, 200, 30);
            encuadreBarraVida = Encuadre(60, 85, 330, 25);
            break;
        case 3: //Jugador 4
            pathIcono = archiConfig->child("configuracion").child("escenario")
                    .child("protagonistas").child("protagonista4").child_value("icono");
            encuadreIcono = Encuadre(410, 60, 45, 45);
            encuadreNombre = Encuadre(460, 60, 200, 30);
            encuadreBarraVida = Encuadre(460, 85, 330, 25);
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
    //Cargar barra vida.
    // Parte 1: La base en rojo
    SDL_Rect rectangulo = encuadreBarraVida.get();
    SDL_SetRenderDrawColor(renderizador->get(),0xFF,0,0,255);
    SDL_RenderFillRect(renderizador->get(), &rectangulo);
    //Parte 2: calcular cuanto en amarillo y dibujarlo
    rectangulo.w = rectangulo.w * estadoJugador.getEnergia() / maxVida;
    SDL_SetRenderDrawColor(renderizador->get(),0xFF,0xFF,0,255);
    SDL_RenderFillRect(renderizador->get(),&rectangulo);

}
