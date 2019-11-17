#include "Sonidos.h"


Sonidos::Sonidos(pugi::xml_document* archiConfig, bool *musicaFondoActiva, bool *ejecutarSonidoGolpe,
                 bool *ejecutarSonidoSalto, bool *ejecutarSonidoCaida, bool *ejecutarSonidoDestruccion) {

    this->archiConfig = archiConfig;
    this->musicaFondoActiva = musicaFondoActiva;
    this->ejecutarSonidoGolpe = ejecutarSonidoGolpe;
    this->ejecutarSonidoSalto = ejecutarSonidoSalto;
    this->ejecutarSonidoCaida = ejecutarSonidoCaida;
    this->ejecutarSonidoDestruccion = ejecutarSonidoDestruccion;
    logueador = Logger::Log::ObtenerInstancia();
}

void Sonidos::operator()() {
    // SDL_Init() lo hace VentanaClienteInicioSesion

    int frecuencia = 44100;
    Uint16 audioFormato = AUDIO_S16SYS;
    int canales = 1;
    int buffers = 4096;

    if (Mix_OpenAudio(frecuencia, audioFormato, canales, buffers) != 0) {
        mensajeLog = "No fue posible inicializar el audio: ";
        mensajeLog.append( Mix_GetError() );
        logueador->Error(mensajeLog);
        return;
    }

    std::string sonidoURLFondo = archiConfig->child("configuracion").child("escenario")
            .child("sonidos").child_value("fondo");

    std::string sonidoURLGolpe = archiConfig->child("configuracion").child("escenario")
            .child("sonidos").child_value("golpe");

    std::string sonidoURLSalto = archiConfig->child("configuracion").child("escenario")
            .child("sonidos").child_value("salto");

    std::string sonidoURLCaida = archiConfig->child("configuracion").child("escenario")
            .child("sonidos").child_value("caida");

    std::string sonidoURLDestruccion = archiConfig->child("configuracion").child("escenario")
            .child("sonidos").child_value("destruccion");

    sonidoFondo = Mix_LoadWAV(sonidoURLFondo.data() );
    if (sonidoFondo == NULL) {
        mensajeLog = "No fue posible cargar el archivo de audio: ";
        mensajeLog.append( Mix_GetError() );
        logueador->Error(mensajeLog);
        return;
    }
    
    mensajeLog = "Ubicación de la música de fondo: ";
    mensajeLog.append( sonidoURLFondo.data() );
    logueador->Debug(mensajeLog);
    
    sonidoGolpe = Mix_LoadWAV(sonidoURLGolpe.data() );
    if (sonidoGolpe == NULL) {
        mensajeLog = "No fue posible cargar el archivo de audio: ";
        mensajeLog.append( Mix_GetError() );
        logueador->Error(mensajeLog);
        return;
    }

    sonidoSalto = Mix_LoadWAV(sonidoURLSalto.data() );
    if (sonidoSalto == NULL) {
        mensajeLog = "No fue posible cargar el archivo de audio: ";
        mensajeLog.append( Mix_GetError() );
        logueador->Error(mensajeLog);
        return;
    }

    sonidoCaida = Mix_LoadWAV(sonidoURLCaida.data() );
    if (sonidoCaida == NULL) {
        mensajeLog = "No fue posible cargar el archivo de audio: ";
        mensajeLog.append( Mix_GetError() );
        logueador->Error(mensajeLog);
        return;
    }

    sonidoDestruccion = Mix_LoadWAV(sonidoURLDestruccion.data() );
    if (sonidoDestruccion == NULL) {
        mensajeLog = "No fue posible cargar el archivo de audio: ";
        mensajeLog.append( Mix_GetError() );
        logueador->Error(mensajeLog);
        return;
    }

    logueador->Info("Empieza a sonar la música de fondo.");
    int canal1 = Mix_PlayChannel(-1, sonidoFondo, -1);
    if (canal1 == -1) {
        mensajeLog = "No fue posible reproducir el archivo de audio: ";
        mensajeLog.append( Mix_GetError() );
        logueador->Error(mensajeLog);
        return;
    }

    bool musicaFondoActivaUltimoEstado = *musicaFondoActiva;
    while (Mix_Playing(canal1) != 0) {
        // Si no bucleo acá, la música se corta
        SDL_Delay(100);

        if (musicaFondoActivaUltimoEstado != *musicaFondoActiva) {
            // Se solicitó cambiar el estado del sonido (activo / inactivo)

            if (!*musicaFondoActiva) {
                Mix_Pause(canal1);
                logueador->Info("Se pausa la música de fondo.");
            } else {
                Mix_Resume(canal1);
                logueador->Info("Se reanuda la música de fondo.");
            }
            musicaFondoActivaUltimoEstado = *musicaFondoActiva;
        }

        if (*ejecutarSonidoGolpe) {
            int canal2 = Mix_PlayChannel(-1, sonidoGolpe, 0);
            if (canal2 == -1) {
                mensajeLog = "No fue posible reproducir el archivo de audio: ";
                mensajeLog.append( Mix_GetError() );
                logueador->Error(mensajeLog);
                return;
            }
            *ejecutarSonidoGolpe = false;
        }
    }
}


Sonidos::~Sonidos() {
    Mix_FreeChunk(sonidoFondo);
    Mix_FreeChunk(sonidoGolpe);
    Mix_FreeChunk(sonidoSalto);
    Mix_FreeChunk(sonidoCaida);
    Mix_FreeChunk(sonidoDestruccion);
    Mix_CloseAudio();
    // SDL_Quit() lo hace VentanaCliente
}

