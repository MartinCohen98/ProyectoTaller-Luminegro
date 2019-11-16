#include "../comunicacion/MensajeCredenciales.h"
#include "VentanaClienteInicioSesion.h"

VentanaClienteInicioSesion::VentanaClienteInicioSesion() {
    estado = ESTADO_INICIALIZACION;

    Logger::Log *logueador  =  Logger::Log::ObtenerInstancia();
    std::string mensajeError;
    mensajeInformativoTipo = 0;
    texturaTxtIngre = NULL;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        mensajeError = "Unable to initialize SDL: ";
        mensajeError.append( SDL_GetError() );
        logueador->Error(mensajeError);
    }
    TTF_Init();

    ventana = SDL_CreateWindow("Luminegro Final Fight - Iniciar sesión",
                               SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED,
                               640,
                               480, 0);

    renderizador = SDL_CreateRenderer(ventana, -1, 0);

    fuente = TTF_OpenFont("assets/fonts/Ubuntu-M.ttf", 30);

    if (!fuente) {
        mensajeError = "TTF_OpenFont: ";
        mensajeError.append( TTF_GetError() );
        logueador->Error(mensajeError);
        estado = ESTADO_ERROR;
    }

    // Preparo textos fijos
    SDL_Color colorTxtFijo = { 138, 212, 207 };
    superficieTxt = TTF_RenderText_Solid(fuente, "Nombre de usuario:", colorTxtFijo);
    texturaTxtFijo1 = SDL_CreateTextureFromSurface(renderizador, superficieTxt);

    superficieTxt = TTF_RenderText_Solid(fuente, "Clave:", colorTxtFijo);
    texturaTxtFijo2 = SDL_CreateTextureFromSurface(renderizador, superficieTxt);
}


int VentanaClienteInicioSesion::getEstado() {
    return estado;
}


int VentanaClienteInicioSesion::pedirCredenciales() {
    estado = ESTADO_INGRESANDO_USUARIO;

    // BUCLE: el usuario teclea sus credenciales...
    while (leerTeclado() && estado != ESTADO_CONECTANDO) {
        SDL_Delay(40);
        actualizarVentana();
    };

    return EXIT_SUCCESS;
}


bool VentanaClienteInicioSesion::leerTeclado() {
    while (SDL_PollEvent(&evento) != 0) {
        switch (evento.type) {
            case SDL_QUIT:
                return false;
            case SDL_TEXTINPUT:
                if (stringSiendoIngresado.size() < MensajeCredenciales::UNA_CREDENCIAL_LONGITUD_MAXIMA) {
                    stringSiendoIngresado += evento.text.text;
                    if (estado == ESTADO_INGRESANDO_CLAVE) {
                        stringIngresadoClaveConMascara += "*";
                    }
                }
                break;
            case SDL_KEYDOWN:
                switch (evento.key.keysym.sym) {
                    case SDLK_BACKSPACE:
                    case SDLK_LEFT:
                        if (stringSiendoIngresado.size() > 0) {
                            stringSiendoIngresado.pop_back();
                        }
                        if (estado == ESTADO_INGRESANDO_CLAVE && stringIngresadoClaveConMascara.size() > 0) {
                            stringIngresadoClaveConMascara.pop_back();
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

    return true;
}


void VentanaClienteInicioSesion::actualizarVentana() {
    // Muestro lo que lleva ingresado
    // Rehago desde cero el renderizador
    SDL_SetRenderDrawColor(renderizador, 44, 60, 74, 255 );
    SDL_RenderClear(renderizador);

    SDL_RenderCopy(renderizador, texturaTxtFijo1, NULL, &rectanguloTxtFijoSuperior);
    SDL_RenderCopy(renderizador, texturaTxtFijo2, NULL, &rectanguloTxtFijoInferior);

    atenderMostradoDeCursor();

    switch (estado) {

        case ESTADO_INGRESANDO_CLAVE:
            if (pasarAEstadoSiguiente) {
                pasarAEstadoSiguiente = false;
                stringIngresadoClave = stringSiendoIngresado;
                estado = ESTADO_CONECTANDO;
            } else {
                stringIngresadoClaveConMascaraYCursor = stringIngresadoClaveConMascara;
                if (mostrarCursor) {
                    stringIngresadoClaveConMascaraYCursor.append("|");
                }
            }
            break;

        case ESTADO_INGRESANDO_USUARIO:
            stringIngresadoUsuario = stringSiendoIngresado;
            if (pasarAEstadoSiguiente) {
                estado = ESTADO_INGRESANDO_CLAVE;
                pasarAEstadoSiguiente = false;
                stringSiendoIngresado = "";
            } else {
                if (mostrarCursor) {
                    stringIngresadoUsuario.append("|");
                }
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
    }

    if (stringIngresadoClaveConMascaraYCursor.size() > 0) {
        superficieTxt = TTF_RenderText_Solid(fuente, stringIngresadoClaveConMascaraYCursor.c_str(),
                colorTxtIngre);
        rectanguloTxtIngre.x = 320 - (superficieTxt->w / 2.0f);
        if (estado == ESTADO_INGRESANDO_CLAVE && mostrarCursor) rectanguloTxtIngre.x += 5;
        rectanguloTxtIngre.w = superficieTxt->w;
        rectanguloTxtIngre.y = 260;

        texturaTxtIngre = SDL_CreateTextureFromSurface(renderizador, superficieTxt);

        SDL_RenderCopy(renderizador, texturaTxtIngre, NULL, &rectanguloTxtIngre);
        SDL_DestroyTexture(texturaTxtIngre);
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


void VentanaClienteInicioSesion::atenderMostradoDeCursor() {
    mostrarCursor = (i < 13);
    if (i == 25) {
        i = 0;
    } else {
        i++;
    }
}


std::string VentanaClienteInicioSesion::getUsuario() {
    return stringIngresadoUsuario;
}


std::string VentanaClienteInicioSesion::getClave() {
    return stringIngresadoClave;
}


void VentanaClienteInicioSesion::mostrarMensaje(const std::string mensaje, const int tipo) {
    mensajeInformativoString = mensaje;
    mensajeInformativoTipo = tipo;
    actualizarVentana();
}


void VentanaClienteInicioSesion::demorar(Uint32 milisegundos) {
    SDL_Delay(milisegundos);
}


void VentanaClienteInicioSesion::resetear() {
    estado = ESTADO_INGRESANDO_USUARIO;
    stringSiendoIngresado = "";
    stringIngresadoUsuario = "";
    stringIngresadoClave = "";
    stringIngresadoClaveConMascara = "";
    stringIngresadoClaveConMascaraYCursor = "";
    mensajeInformativoString = "";
    actualizarVentana();
}


void VentanaClienteInicioSesion::cerrar() {
    TTF_CloseFont(fuente);
    TTF_Quit();
    SDL_FreeSurface(superficieTxt);
    SDL_DestroyRenderer(renderizador);
    SDL_DestroyWindow(ventana);
    SDL_DestroyTexture(texturaTxtFijo1);
    SDL_DestroyTexture(texturaTxtFijo2);
    SDL_Quit();
}
