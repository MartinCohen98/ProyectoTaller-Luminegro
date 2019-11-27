#include <SDL_ttf.h>
#include <grafica/Textura.h>
#include "VistaTransicionJuego.h"


void VistaTransicionJuego::CambioDeNivel(int nivel, Renderizador *renderizador, InfoJugador *infoJugadores,
                                         MensajeInicioPartida mensajeInicio) {

    SDL_Surface *superficieTxt;
    Textura textura;
    Encuadre rectangulo;
    std::string texto;

    //Fondo
    SDL_SetRenderDrawColor(renderizador->get(), colorNegroNoche.r, colorNegroNoche.g, colorNegroNoche.b, colorNegroNoche.a);
    SDL_RenderClear(renderizador->get());

    //Inicializo letras
    TTF_Init();
    TTF_Font *fuente = TTF_OpenFont("assets/fonts/Ubuntu-M.ttf", 40);
    TTF_SetFontStyle(fuente, TTF_STYLE_BOLD);
    //Titulo
    if(nivel == 1)
        texto = "Fin nivel 1";
    else if (nivel == 2)
        texto = "Fin del juego";
    else
        texto = "GAME OVER!!";

    superficieTxt = TTF_RenderText_Solid(fuente, texto.c_str() , colorAmarilloPatito);
    textura.texturizar(renderizador, superficieTxt);
    rectangulo = {320 - (superficieTxt->w / 2), 100, superficieTxt->w, superficieTxt->h};
    textura.copiarseEn(renderizador, rectangulo);

    //Ahora las otras cosas
    fuente = TTF_OpenFont("assets/fonts/Ubuntu-M.ttf", 30);
    Encuadre encuadreRanking = {40, 180, 200, 50};
    Encuadre encuadrePuntaje = {290, 180, 180, 50};
    Encuadre encuadreNombre = {550, 180, 200, 50};

    superficieTxt = TTF_RenderText_Solid(fuente, "Ranking" , colorRojoOscuro);
    textura.texturizar(renderizador, superficieTxt);
    textura.copiarseEn(renderizador, encuadreRanking);

    superficieTxt = TTF_RenderText_Solid(fuente, "Puntaje" , colorRojoOscuro);
    textura.texturizar(renderizador, superficieTxt);
    textura.copiarseEn(renderizador, encuadrePuntaje);

    superficieTxt = TTF_RenderText_Solid(fuente, "Nombre" , colorRojoOscuro);
    textura.texturizar(renderizador, superficieTxt);
    textura.copiarseEn(renderizador, encuadreNombre);

    int distanciaY;
    for(int i = 0; i < mensajeInicio.getCantidadJugadoresPartida(); i++){
        distanciaY = 280 + i * 50;
        texto = "No." + std::to_string(i + 1);

        //superficieTxt = TTF_RenderText_Solid(fuente, mensajeInicio.getNombreJugador(0).c_str(), colorPetroleo);
        superficieTxt = TTF_RenderText_Solid(fuente, texto.c_str(), colorPetroleo);
        encuadreRanking.modificar(encuadreRanking.getX(), distanciaY, superficieTxt->w, superficieTxt->h );
        textura.texturizar(renderizador, superficieTxt);
        textura.copiarseEn(renderizador, encuadreRanking);

        superficieTxt = TTF_RenderText_Solid(fuente, std::to_string(infoJugadores[i].getPuntaje()).c_str(), colorPetroleo);
        encuadrePuntaje.modificar(encuadrePuntaje.getX(), distanciaY, superficieTxt->w, superficieTxt->h );
        textura.texturizar(renderizador, superficieTxt);
        textura.copiarseEn(renderizador, encuadrePuntaje);

        superficieTxt = TTF_RenderText_Solid(fuente, mensajeInicio.getNombreJugador(i).c_str(),  colorPetroleo);
        encuadreNombre.modificar(encuadreNombre.getX(), distanciaY, superficieTxt->w, superficieTxt->h );
        textura.texturizar(renderizador, superficieTxt);
        textura.copiarseEn(renderizador, encuadreNombre);
    }

    renderizador->renderizar();
    //Tiempo de muestra de la pantalla. También poner esto en el servidor
    SDL_Delay(5000);

    //Liberar recursos
    TTF_CloseFont( fuente );
    SDL_FreeSurface(superficieTxt);
}
