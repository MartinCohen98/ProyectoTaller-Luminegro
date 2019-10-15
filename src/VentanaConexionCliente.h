#ifndef PROYECTOTALLER_LUMINEGRO_VENTANACONEXIONCLIENTE_H
#define PROYECTOTALLER_LUMINEGRO_VENTANACONEXIONCLIENTE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

#include "Logger.h"


class VentanaConexionCliente {

private:
    static const int ESTADO_INGRESANDO_USUARIO = 1;
    static const int ESTADO_INGRESANDO_CLAVE = 2;
    static const int ESTADO_CONECTANDO = 3;

    SDL_Window* ventana;
    SDL_Renderer *renderizador;
    SDL_Texture *texturaTxtFijo1;
    SDL_Texture *texturaTxtFijo2;
    SDL_Texture *texturaTxtIngre;
    TTF_Font *fuente;
    SDL_Event evento;
    SDL_Rect rectanguloTxtFijoSuperior = { 200, 40, 250, 37 };
    SDL_Rect rectanguloTxtFijoInferior = { 270, 200, 100, 37 };
    SDL_Rect rectanguloTxtFijoMensajes = { 270, 345, 100, 37 };
    SDL_Rect rectanguloTxtIngre = { 0, 100, 250, 30 };
    SDL_Surface *superficieTxt;
    SDL_Color colorTxtIngre = {100, 100, 100};
    SDL_Color colorTxtNeutro = {51, 204, 0};
    SDL_Color colorTxtError = {255, 26, 26};
    SDL_Color colorMensajeInformativo;
    std::string stringSiendoIngresado;
    std::string stringSiendoIngresadoConCursor;
    std::string stringIngresadoUsuario;
    std::string stringIngresadoClave;
    std::string mensajeInformativoString = "";
    int mensajeInformativoTipo;
    unsigned short int i = 0; // para conteos
    bool mostrarCursor = false; // Se muestra siempre, esta variable se usa en unos bucles
    int estado = ESTADO_INGRESANDO_USUARIO;
    bool pasarAEstadoSiguiente = false;

    bool buclearIngresoCredenciales();
    void atenderMostradoDeCursor(); // Se ocupa del cursor destellante que indica donde aparece lo que tecleás
    void refrescarVentana();

public:
    static const int MENSAJE_TIPO_INFORMATIVO = 1;
    static const int MENSAJE_TIPO_ERROR = 2;

    int pedirCredenciales(); // Le ofrece al cliente ingresar sus credenciales para conectarse
    std::string getUsuario();
    std::string getClave();
    void mostrarMensaje(const std::string mensaje, const int tipo);
    void cerrar();
};


#endif //PROYECTOTALLER_LUMINEGRO_VENTANACONEXIONCLIENTE_H
