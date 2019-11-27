#include "../comunicacion/MensajeServidor.h"
#include "VistaEstado.h"

VistaEstado::VistaEstado(Renderizador *renderizador, pugi::xml_document *archiConfig, int maxVida, std::string nombreJugador, int numeroJugador) {
    this->renderizador = renderizador;
    this->maxVida = maxVida;
    superficieTxt = NULL;
    cantidadDeVidas = 0;
    this->nombreJugador = nombreJugador;
    //nombreYVidas = nombreJugador.append(1,':').append(std::to_string(cantidadDeVidas));


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
    colorLetrasNombre = {0,0,0x80, 0xFF};
    colorPuntaje = {0xFF,0,0,0xFF};
    colorRellenoLetras = {0xFF,0xFF,0xFF,0xFF};
    colorDesconexion = {0xC0, 0xC0, 0xC0, 0x80};
}

void VistaEstado::renderizar(InfoJugador estadoJugador) {
    //Renderiza ícono
    texturaIcono.copiarseEn(renderizador, encuadreIcono);
    //Carga barra de vida
    CargarBarraDeVida(&estadoJugador);
    //Cargar nombre y vidas
    CargarNombreYVidas(&estadoJugador);
    //Cargar puntaje
    CargarPuntaje(&estadoJugador);

    if(!estadoJugador.getVidas() && !estadoJugador.getEnergia()){
        //Le mando el gameover sobre la barra de vida
        if(!texturaBarraVida.estaInicializada()) {
            superficieTxt = TTF_RenderText_Solid(fuente, "GAME OVER", colorRellenoLetras);
            texturaBarraVida.texturizar(renderizador, superficieTxt);
        }
        texturaBarraVida.copiarseEn(renderizador, encuadreBarraVida);
    }

}

void VistaEstado::CargarBarraDeVida(InfoJugador *estadoJugador){
    SDL_Color color = (estadoJugador->estaConectado())? SDL_Color{0xFF,0,0,0xFF}: colorDesconexion;
    // La base en rojo
    SDL_Rect rectangulo = encuadreBarraVida.get();
    SDL_SetRenderDrawColor(renderizador->get(),color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderizador->get(), &rectangulo);
    //Calcular cuanto en amarillo y dibujarlo
    color = (estadoJugador->estaConectado())? SDL_Color{0xFF,0xFF,0,0xFF}: colorDesconexion;
    if (estadoJugador->getEnergia() < 0) {
        rectangulo.w = 0;
    } else {
        rectangulo.w = rectangulo.w * estadoJugador->getEnergia() / maxVida;
    }
    SDL_SetRenderDrawColor(renderizador->get(),color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderizador->get(),&rectangulo);
}

void VistaEstado::CargarNombreYVidas(InfoJugador *estadoJugador){
    //std::string nombreYVidas = nombreJugador + ":" + std::to_string(estadoJugador->getVidas());
    if(this->cantidadDeVidas != estadoJugador->getVidas()) {
        cantidadDeVidas = estadoJugador->getVidas();
        nombreYVidas = nombreJugador + ":" + std::to_string(cantidadDeVidas);
        if(nombreYVidas.length() < 12)
            nombreYVidas = nombreYVidas.append(12 - nombreYVidas.length(), ' ');
        //Agrega contorno a las letras
        TTF_SetFontOutline(fuente, 1);
        //Pone nombre y vidas
        superficieTxt = TTF_RenderText_Solid(fuente, nombreYVidas.c_str(), colorLetrasNombre);
        texturaNombreJugador.texturizar(renderizador, superficieTxt);
        //Saca contorno, y rellena nombres y puntajes
        TTF_SetFontOutline(fuente, 0);
        //Rellena nombre y vidas
        superficieTxt = TTF_RenderText_Solid(fuente, nombreYVidas.c_str(), colorRellenoLetras);
        texturaNombreRelleno.texturizar(renderizador, superficieTxt);
    }
    texturaNombreJugador.copiarseEn(renderizador, encuadreNombre);
    texturaNombreRelleno.copiarseEn(renderizador, encuadreNombre);
}


void VistaEstado::CargarPuntaje(InfoJugador *estadoJugador){
    std::string puntaje = std::to_string(estadoJugador->getPuntaje());
    if(6 > puntaje.size())
        puntaje.insert(0, 6 - puntaje.size(), ' ');
    //Agrega contorno a las letras
    TTF_SetFontOutline(fuente, 1);
    superficieTxt = TTF_RenderText_Solid(fuente, puntaje.c_str(), colorPuntaje);
    texturaPuntaje.texturizar(renderizador, superficieTxt);
    texturaPuntaje.copiarseEn(renderizador, encuadrePuntaje);
    //Rellena puntajes
    TTF_SetFontOutline(fuente, 0);
    superficieTxt = TTF_RenderText_Solid(fuente, puntaje.c_str(), colorRellenoLetras);
    texturaPuntaje.texturizar(renderizador, superficieTxt);
    texturaPuntaje.copiarseEn(renderizador, encuadrePuntaje);
}

VistaEstado::~VistaEstado() {
    SDL_FreeSurface(superficieTxt);
    TTF_CloseFont( fuente );
}
