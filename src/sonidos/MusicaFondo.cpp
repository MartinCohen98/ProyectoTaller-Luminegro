#include "MusicaFondo.h"

MusicaFondo::MusicaFondo(pugi::xml_document *archiConfig, bool *sonidoEstaActivo) {
    this->archiConfig = archiConfig;
    this->sonidoEstaActivo = sonidoEstaActivo;
    logueador = Logger::Log::ObtenerInstancia();
}


void MusicaFondo::operator()() {
    // SDL_Init() lo hace VentanaClienteInicioSesion

    int frecuencia = 44100;
    Uint16 audioFormato = AUDIO_S16SYS;
    int canales = 2;
    int buffers = 4096;

    if (Mix_OpenAudio(frecuencia, audioFormato, canales, buffers) != 0) {
        mensajeError = "No fue posible inicializar el audio: ";
        mensajeError.append( Mix_GetError() );
        logueador->Error(mensajeError);
        return;
    }

    std::string sonidoURL = archiConfig->child("configuracion").child("escenario")
            .child("sonidos").child_value("fondo");

    sonido = Mix_LoadWAV(sonidoURL.data() );
    if (sonido == NULL) {
        mensajeError = "No fue posible cargar el archivo de audio: ";
        mensajeError.append( Mix_GetError() );
        logueador->Error(mensajeError);
        return;
    }

    logueador->Info("Empieza a sonar la música de fondo.");
    int canal = Mix_PlayChannel(-1, sonido, -1);
    if (canal == -1) {
        mensajeError = "No fue posible reproducir el archivo de audio: ";
        mensajeError.append( Mix_GetError() );
        logueador->Error(mensajeError);
        return;
    }

    bool sonidoEstaActivoUltimoEstado = *sonidoEstaActivo;
    while (Mix_Playing(canal) != 0) {
        // Si no bucleo acá, la música se corta
        SDL_Delay(500);

        if (sonidoEstaActivoUltimoEstado != *sonidoEstaActivo) {
            // Se solicitó cambiar el estado del sonido (activo / inactivo)

            if (!*sonidoEstaActivo) {
                Mix_Pause(canal);
                logueador->Info("Se pausa la música de fondo.");
            } else {
                Mix_Resume(canal);
                logueador->Info("Se reanuda la música de fondo.");
            }
            sonidoEstaActivoUltimoEstado = *sonidoEstaActivo;
        }
    }
}


MusicaFondo::~MusicaFondo() {
    Mix_FreeChunk(sonido);
    Mix_CloseAudio();
    // SDL_Quit() lo hace VentanaCliente
}

