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
            encuadrePuntaje = Encuadre(265,5,120,25);
            break;
        case 1: //Jugador 2
            pathIcono = archiConfig->child("configuracion").child("escenario")
                    .child("protagonistas").child("protagonista2").child_value("icono");
            encuadreIcono = Encuadre(410, 10, 45, 45);
            encuadreNombre = Encuadre(460, 5, 200, 25);
            encuadreBarraVida = Encuadre(460, 30, 330, 25);
            encuadrePuntaje = Encuadre(665,5,120,25);
            break;
        case 2: //Jugador 3
            pathIcono = archiConfig->child("configuracion").child("escenario")
                    .child("protagonistas").child("protagonista3").child_value("icono");
            encuadreIcono = Encuadre(10, 60, 45, 45);
            encuadreNombre = Encuadre(60, 60, 200, 25);
            encuadreBarraVida = Encuadre(60, 85, 330, 25);
            encuadrePuntaje = Encuadre(265,60,120,25);
            break;
        case 3: //Jugador 4
            pathIcono = archiConfig->child("configuracion").child("escenario")
                    .child("protagonistas").child("protagonista4").child_value("icono");
            encuadreIcono = Encuadre(410, 60, 45, 45);
            encuadreNombre = Encuadre(460, 60, 200, 25);
            encuadreBarraVida = Encuadre(460, 85, 330, 25);
            encuadrePuntaje = Encuadre(665,60,120,25);
            break;
        default:
            break;
    }

    //Carga de imágen
    Imagen icono;
    icono.cargar(pathIcono.c_str(),Imagen::TIPO_ICONO);
    texturaIcono.texturizar(renderizador, icono);
    //Inicializa las fuentes
    TTF_Init();
    //Fuente principal: con contorno
    fuente = TTF_OpenFont("assets/fonts/Ubuntu-M.ttf", 13);
    TTF_SetFontStyle(fuente, TTF_STYLE_BOLD);
    colorLetrasNombre = {0,0,0xFF, 0xFF};
    colorPuntaje = {0xFF,0,0,0xFF};
    colorRellenoLetras = {0xFF,0xFF,0xFF,0xFF};
}

void VistaEstado::renderizar(InfoJugador estadoJugador) {
    //Renderiza ícono
    texturaIcono.copiarseEn(renderizador, encuadreIcono);
    //Cargar barra vida.
    // La base en rojo
    SDL_Rect rectangulo = encuadreBarraVida.get();
    SDL_SetRenderDrawColor(renderizador->get(),0xFF,0,0,255);
    SDL_RenderFillRect(renderizador->get(), &rectangulo);
    //Calcular cuanto en amarillo y dibujarlo
    rectangulo.w = rectangulo.w * estadoJugador.getEnergia() / maxVida;
    SDL_SetRenderDrawColor(renderizador->get(),0xFF,0xFF,0,255);
    SDL_RenderFillRect(renderizador->get(),&rectangulo);
    //Cargar nombre y cantidad de vidas (color azul)
    std::string nombreYVidas = nombreJugador + ":" + std::to_string(estadoJugador.getVidas());
    //Agrega contorno a las letras
    TTF_SetFontOutline(fuente, 1);
    //Pone nombre y vidas
    superficieTxt = TTF_RenderText_Solid(fuente, nombreYVidas.c_str(), colorLetrasNombre);
    texturaNombreJugador.texturizar(renderizador, superficieTxt);
    texturaNombreJugador.copiarseEn(renderizador, encuadreNombre);
    //Pone puntaje
    std::string puntaje = std::to_string(estadoJugador.getPuntaje());
    //superficieTxt = TTF_RenderText_Solid(fuente, std::to_string(estadoJugador.getPuntaje()).c_str(), colorPuntaje);
    superficieTxt = TTF_RenderText_Solid(fuente, puntaje.c_str(), colorPuntaje);
    texturaNombreJugador.texturizar(renderizador, superficieTxt);
    texturaNombreJugador.copiarseEn(renderizador, encuadrePuntaje);
    //Saca contorno, y rellena nombres y puntajes
    TTF_SetFontOutline(fuente, 0);
    superficieTxt = TTF_RenderText_Solid(fuente, nombreYVidas.c_str(), colorRellenoLetras);
    texturaNombreJugador.texturizar(renderizador, superficieTxt);
    texturaNombreJugador.copiarseEn(renderizador, encuadreNombre);

    //superficieTxt = TTF_RenderText_Solid(fuente, nombreYVidas.c_str(), colorRellenoLetras);
    superficieTxt = TTF_RenderText_Solid(fuente, puntaje.c_str(), colorRellenoLetras);
    texturaNombreJugador.texturizar(renderizador, superficieTxt);
    texturaNombreJugador.copiarseEn(renderizador, encuadrePuntaje);
}

VistaEstado::~VistaEstado() {
    SDL_FreeSurface(superficieTxt);
}