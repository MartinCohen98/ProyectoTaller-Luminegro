#include <SDL2/SDL_ttf.h>
#include "../grafica/Textura.h"
#include "VistaTransicionJuego.h"
#include <list>

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
    SDL_FreeSurface(superficieTxt);
    //Ahora las otras cosas
    fuente = TTF_OpenFont("assets/fonts/Ubuntu-M.ttf", 30);
    Encuadre encuadreRanking = {40, 180, 200, 50};
    Encuadre encuadrePuntaje = {290, 180, 180, 50};
    Encuadre encuadreNombre = {550, 180, 200, 50};

    superficieTxt = TTF_RenderText_Solid(fuente, "Ranking" , colorRojoOscuro);
    textura.texturizar(renderizador, superficieTxt);
    textura.copiarseEn(renderizador, encuadreRanking);
    SDL_FreeSurface(superficieTxt);

    superficieTxt = TTF_RenderText_Solid(fuente, "Puntaje" , colorRojoOscuro);
    textura.texturizar(renderizador, superficieTxt);
    textura.copiarseEn(renderizador, encuadrePuntaje);
    SDL_FreeSurface(superficieTxt);

    superficieTxt = TTF_RenderText_Solid(fuente, "Nombre" , colorRojoOscuro);
    textura.texturizar(renderizador, superficieTxt);
    textura.copiarseEn(renderizador, encuadreNombre);
    SDL_FreeSurface(superficieTxt);

    std::list<PuntajeJugador> listaPuntajes;

    for(int i = 0; i < mensajeInicio.getCantidadJugadoresPartida(); i++){
        listaPuntajes.push_front({infoJugadores[i].getPuntaje(),mensajeInicio.getNombreJugador(i)});
    }
    listaPuntajes.sort([] (PuntajeJugador a, PuntajeJugador b){ return a.puntaje > b.puntaje;} );

    PuntajeJugador puntajeJugador;
    int distanciaY;
    for(int i = 0; i < mensajeInicio.getCantidadJugadoresPartida(); i++){
        puntajeJugador = listaPuntajes.front();
        listaPuntajes.pop_front();
        distanciaY = 280 + i * 50;
        texto = "No." + std::to_string(i + 1);

        superficieTxt = TTF_RenderText_Solid(fuente, texto.c_str(), colorPetroleo);
        encuadreRanking.modificar(encuadreRanking.getX(), distanciaY, superficieTxt->w, superficieTxt->h );
        textura.texturizar(renderizador, superficieTxt);
        textura.copiarseEn(renderizador, encuadreRanking);
        SDL_FreeSurface(superficieTxt);

        superficieTxt = TTF_RenderText_Solid(fuente, std::to_string(puntajeJugador.puntaje).c_str(), colorPetroleo);
        encuadrePuntaje.modificar(encuadrePuntaje.getX(), distanciaY, superficieTxt->w, superficieTxt->h );
        textura.texturizar(renderizador, superficieTxt);
        textura.copiarseEn(renderizador, encuadrePuntaje);
        SDL_FreeSurface(superficieTxt);

        superficieTxt = TTF_RenderText_Solid(fuente, puntajeJugador.nombre.c_str(),  colorPetroleo);
        encuadreNombre.modificar(encuadreNombre.getX(), distanciaY, superficieTxt->w, superficieTxt->h );
        textura.texturizar(renderizador, superficieTxt);
        textura.copiarseEn(renderizador, encuadreNombre);
        SDL_FreeSurface(superficieTxt);
    }

    renderizador->renderizar();
    //Tiempo de muestra de la pantalla. También poner esto en el servidor
    SDL_Delay(3000);

    //Liberar recursos
    TTF_CloseFont( fuente );
}
