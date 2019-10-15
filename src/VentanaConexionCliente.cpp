#include "VentanaConexionCliente.h"

int VentanaConexionCliente::pedirCredenciales() {

    Logger::Log *logueador  =  Logger::Log::ObtenerInstancia();

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    ventana = SDL_CreateWindow("Luminegro Final Fight - Iniciar sesión",
                                           SDL_WINDOWPOS_UNDEFINED,
                                           SDL_WINDOWPOS_UNDEFINED,
                                           640,
                                           480, 0);

    renderizador = SDL_CreateRenderer(ventana, -1, 0);

    fuente = TTF_OpenFont("assets/fonts/Ubuntu-M.ttf", 30);

    if (!fuente) {
        std::string mensajeError = "TTF_OpenFont: ";
        mensajeError.append( TTF_GetError() );
        logueador->Error(mensajeError);
        return EXIT_FAILURE;
    }

    // Preparo textos fijos
    SDL_Color colorTxtFijo = { 138, 212, 207 };
    superficieTxt = TTF_RenderText_Solid(fuente, "Nombre de usuario:", colorTxtFijo);
    texturaTxtFijo1 = SDL_CreateTextureFromSurface(renderizador, superficieTxt);

    superficieTxt = TTF_RenderText_Solid(fuente, "Clave:", colorTxtFijo);
    texturaTxtFijo2 = SDL_CreateTextureFromSurface(renderizador, superficieTxt);

    // El usuario teclea sus credenciales...
    while (buclearIngresoCredenciales() && estado != ESTADO_CONECTANDO) {
        SDL_Delay(10);
    }

    return EXIT_SUCCESS;
}


bool VentanaConexionCliente::buclearIngresoCredenciales() {
    // Rehago desde cero el renderizador
    SDL_SetRenderDrawColor(renderizador, 44, 60, 74, 255 );
    SDL_RenderClear(renderizador);

    SDL_RenderCopy(renderizador, texturaTxtFijo1, NULL, &rectanguloTxtFijoSuperior);
    SDL_RenderCopy(renderizador, texturaTxtFijo2, NULL, &rectanguloTxtFijoInferior);

    while (SDL_PollEvent(&evento) != 0) {
        switch (evento.type) {
            case SDL_QUIT:
                return false;
            case SDL_TEXTINPUT:
                stringSiendoIngresado += evento.text.text;
                break;
            case SDL_KEYDOWN:
                switch (evento.key.keysym.sym) {
                    case SDLK_BACKSPACE:
                    case SDLK_LEFT:
                        if (stringSiendoIngresado.size() > 0) {
                            stringSiendoIngresado.pop_back();
                        }
                        break;
                    case SDLK_ESCAPE:
                        return false;
                        break;
                    case SDLK_RETURN:
                    case SDLK_RETURN2:
                    case SDLK_KP_ENTER:
                        if (stringSiendoIngresado.size() > 0) {
                            pasarAEstadoSiguiente = true;
                        }
                        break;
                }
                break;
        }
    }

    // Muestro lo que lleva ingresado

    atenderMostradoDeCursor();

    refrescarVentana();

    return true;
}


void VentanaConexionCliente::atenderMostradoDeCursor() {
    stringSiendoIngresadoConCursor = stringSiendoIngresado;

    mostrarCursor = (i < 50);
    if (i == 100) {
        i = 0;
    } else {
        i++;
    }

    if (mostrarCursor) {
        stringSiendoIngresadoConCursor.append("|");
    }
}


void VentanaConexionCliente::refrescarVentana() {
    switch (estado) {
        case ESTADO_INGRESANDO_CLAVE:
            if (pasarAEstadoSiguiente) {
                stringIngresadoClave = stringSiendoIngresado;
                pasarAEstadoSiguiente = false;
                estado = ESTADO_CONECTANDO;
            } else {
                stringIngresadoClave = stringSiendoIngresadoConCursor;
            }
            break;
        case ESTADO_INGRESANDO_USUARIO:
            if (pasarAEstadoSiguiente) {
                stringIngresadoUsuario = stringSiendoIngresado;
                estado = ESTADO_INGRESANDO_CLAVE;
                pasarAEstadoSiguiente = false;
                stringSiendoIngresado = "";
            } else {
                stringIngresadoUsuario = stringSiendoIngresadoConCursor;
            }
            break;
    }

    if (stringIngresadoUsuario.size() > 0) {
        superficieTxt = TTF_RenderText_Solid(fuente, stringIngresadoUsuario.c_str(), colorTxtIngre);
        rectanguloTxtIngre.x = 320 - (superficieTxt->w / 2.0f);
        if (estado == ESTADO_INGRESANDO_USUARIO && mostrarCursor) rectanguloTxtIngre.x += 5;
        rectanguloTxtIngre.w = superficieTxt->w;
        rectanguloTxtIngre.y = 100;

        texturaTxtIngre = SDL_CreateTextureFromSurface(renderizador, superficieTxt);

        SDL_RenderCopy(renderizador, texturaTxtIngre, NULL, &rectanguloTxtIngre);
        SDL_DestroyTexture(texturaTxtIngre);
        SDL_FreeSurface(superficieTxt);
    }

    if (stringIngresadoClave.size() > 0) {
        superficieTxt = TTF_RenderText_Solid(fuente, stringIngresadoClave.c_str(), colorTxtIngre);
        rectanguloTxtIngre.x = 320 - (superficieTxt->w / 2.0f);
        if (estado == ESTADO_INGRESANDO_CLAVE && mostrarCursor) rectanguloTxtIngre.x += 5;
        rectanguloTxtIngre.w = superficieTxt->w;
        rectanguloTxtIngre.y = 260;

        texturaTxtIngre = SDL_CreateTextureFromSurface(renderizador, superficieTxt);

        SDL_RenderCopy(renderizador, texturaTxtIngre, NULL, &rectanguloTxtIngre);
        SDL_DestroyTexture(texturaTxtIngre);
        SDL_FreeSurface(superficieTxt);
    }

    if (mensajeInformativoString.size() > 0) {
        switch (mensajeInformativoTipo) {
            case MENSAJE_TIPO_INFORMATIVO:
                colorMensajeInformativo = colorTxtNeutro;
                break;
            case MENSAJE_TIPO_ERROR:
                colorMensajeInformativo = colorTxtError;
                break;
        }

        superficieTxt = TTF_RenderText_Solid(fuente, mensajeInformativoString.c_str(),
                colorMensajeInformativo);
        rectanguloTxtFijoMensajes.x = 320 - (superficieTxt->w / 2.0f);
        rectanguloTxtFijoMensajes.w = superficieTxt->w;

        texturaTxtIngre = SDL_CreateTextureFromSurface(renderizador, superficieTxt);

        SDL_RenderCopy(renderizador, texturaTxtIngre, NULL, &rectanguloTxtFijoMensajes);
        SDL_DestroyTexture(texturaTxtIngre);
    }

    // Actualizo ventana
    SDL_RenderPresent(renderizador);
}


std::string VentanaConexionCliente::getUsuario() {
    return stringIngresadoUsuario;
}


std::string VentanaConexionCliente::getClave() {
    return stringIngresadoClave;
}


void VentanaConexionCliente::mostrarMensaje(const std::string mensaje, const int tipo) {
    mensajeInformativoString = mensaje;
    mensajeInformativoTipo = tipo;
    refrescarVentana();
}

void VentanaConexionCliente::cerrar() {
    TTF_CloseFont(fuente);
    TTF_Quit();
    SDL_DestroyRenderer(renderizador);
    SDL_DestroyWindow(ventana);
    SDL_DestroyTexture(texturaTxtFijo1);
    SDL_DestroyTexture(texturaTxtFijo2);
    SDL_FreeSurface(superficieTxt);
    SDL_Quit();
}
