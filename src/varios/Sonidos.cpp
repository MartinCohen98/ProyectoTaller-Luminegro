#include "Sonidos.h"


Sonidos::Sonidos(pugi::xml_document* archiConfig, bool *musicaFondoActiva, bool *ejecutarSonidoGolpeTiro,
                 bool *ejecutarSonidoGolpeImpacto,
                 bool *ejecutarSonidoSalto, bool *ejecutarSonidoCaida, bool *ejecutarSonidoDestruccion) {

    this->archiConfig = archiConfig;
    this->musicaFondoActiva = musicaFondoActiva;
    this->ejecutarSonidoGolpeTiro = ejecutarSonidoGolpeTiro;
    this->ejecutarSonidoGolpeImpacto = ejecutarSonidoGolpeImpacto;
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

    std::string sonidoURLGolpeTiro = archiConfig->child("configuracion").child("escenario")
            .child("sonidos").child_value("golpeTiro");

    std::string sonidoURLGolpeImpacto = archiConfig->child("configuracion").child("escenario")
            .child("sonidos").child_value("golpeImpacto");

    std::string sonidoURLSalto = archiConfig->child("configuracion").child("escenario")
            .child("sonidos").child_value("salto");

    std::string sonidoURLCaida = archiConfig->child("configuracion").child("escenario")
            .child("sonidos").child_value("caida");

    std::string sonidoURLDestruccion = archiConfig->child("configuracion").child("escenario")
            .child("sonidos").child_value("destruccion");

    sonidoFondo = cargarSonido(sonidoURLFondo.data() );

    mensajeLog = "Ubicación de la música de fondo: ";
    mensajeLog.append( sonidoURLFondo.data() );
    logueador->Debug(mensajeLog);
    
    sonidoGolpeTiro = cargarSonido( sonidoURLGolpeTiro.data() );
    sonidoGolpeImpacto = cargarSonido( sonidoURLGolpeImpacto.data() );
    sonidoSalto = cargarSonido( sonidoURLSalto.data() );
    sonidoCaida = cargarSonido( sonidoURLCaida.data() );
    sonidoDestruccion = cargarSonido( sonidoURLDestruccion.data() );

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

        if (*ejecutarSonidoGolpeTiro) {
            int canal2 = Mix_PlayChannel(-1, sonidoGolpeTiro, 0);
            if (canal2 == -1) {
                mensajeLog = "No fue posible reproducir el archivo de audio: ";
                mensajeLog.append( Mix_GetError() );
                logueador->Error(mensajeLog);
                return;
            }
            *ejecutarSonidoGolpeTiro = false;
        }
    }
}


Mix_Chunk *Sonidos::cargarSonido(const char* archivo) {
    Mix_Chunk *sonido  = Mix_LoadWAV(archivo);
    if (sonido == NULL) {
        mensajeLog = "No fue posible cargar el archivo de audio: ";
        mensajeLog.append( Mix_GetError() );
        logueador->Error(mensajeLog);
        return NULL;
    }

    return sonido;
}


Sonidos::~Sonidos() {
    Mix_FreeChunk(sonidoFondo);
    Mix_FreeChunk(sonidoGolpeTiro);
    Mix_FreeChunk(sonidoGolpeImpacto);
    Mix_FreeChunk(sonidoSalto);
    Mix_FreeChunk(sonidoCaida);
    Mix_FreeChunk(sonidoDestruccion);
    Mix_CloseAudio();
    // SDL_Quit() lo hace VentanaCliente
}
