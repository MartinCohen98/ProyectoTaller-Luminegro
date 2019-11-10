#include "MusicaFondo.h"

int MusicaFondo::dalePlay() {
    Logger::Log *logueador = Logger::Log::ObtenerInstancia();
    std::string mensajeError;

    int audio_rate = 22050;
    Uint16 audio_format = AUDIO_S16SYS;
    int audio_channels = 2;
    int audio_buffers = 4096;

    if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0) {
        mensajeError = "Unable to initialize audio: ";
        mensajeError.append( Mix_GetError() );
        logueador->Error(mensajeError);
        return EXIT_FAILURE;
    }

    Mix_Chunk *sound = NULL;

    sound = Mix_LoadWAV("assets/sounds/background.mp3");
    if (sound == NULL) {
        mensajeError = "Unable to load WAV file:";
        mensajeError.append( Mix_GetError() );
        logueador->Error(mensajeError);
        return EXIT_FAILURE;
    }
    int channel;

    channel = Mix_PlayChannel(-1, sound, 0);
    if (channel == -1) {
        mensajeError = "Unable to play WAV file:";
        mensajeError.append( Mix_GetError() );
        logueador->Error(mensajeError);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
    // while (Mix_Playing(channel) != 0);
/*
    Mix_FreeChunk(sound);
    Mix_CloseAudio();
    SDL_Quit();*/

}
