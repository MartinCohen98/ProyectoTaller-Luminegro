#include "MusicaFondo.h"

int MusicaFondo::inicializar() {
    logueador = Logger::Log::ObtenerInstancia();

    // SDL_Init() lo hace VentanaClienteInicioSesion

    int frecuencia = 44100;
    Uint16 audioFormato = AUDIO_S16SYS;
    int canales = 2;
    int buffers = 4096;

    if (Mix_OpenAudio(frecuencia, audioFormato, canales, buffers) != 0) {
        mensajeError = "Unable to initialize audio: ";
        mensajeError.append( Mix_GetError() );
        logueador->Error(mensajeError);
        return EXIT_FAILURE;
    }

    sonido = Mix_LoadWAV("assets/sounds/background.mp3");
    if (sonido == NULL) {
        mensajeError = "Unable to load WAV file:";
        mensajeError.append( Mix_GetError() );
        logueador->Error(mensajeError);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}


int MusicaFondo::dalePlay() {
    logueador->Info("Empieza a sonar la música de fondo.");
    int canal = Mix_PlayChannel(-1, sonido, -1);
    if (canal == -1) {
        mensajeError = "Unable to play WAV file:";
        mensajeError.append( Mix_GetError() );
        logueador->Error(mensajeError);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}


MusicaFondo::~MusicaFondo() {
    Mix_FreeChunk(sonido);
    Mix_CloseAudio();
    // SDL_Quit() lo hace VentanaCliente
}

