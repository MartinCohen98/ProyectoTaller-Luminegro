#include "MusicaFondo.h"

MusicaFondo::MusicaFondo(pugi::xml_document *archiConfig) {
    this->archiConfig = archiConfig;
}


void MusicaFondo::operator()() {
    logueador = Logger::Log::ObtenerInstancia();

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

    while (Mix_Playing(canal) != 0) {
        // Si no lo demoro acá, la música se corta
        SDL_Delay(3000);
    }
}


MusicaFondo::~MusicaFondo() {
    Mix_FreeChunk(sonido);
    Mix_CloseAudio();
    // SDL_Quit() lo hace VentanaCliente
}

