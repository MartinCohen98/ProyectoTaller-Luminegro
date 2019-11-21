cmake_minimum_required(VERSION 3.14)
project(ProyectoTaller_Luminegro)

set(CMAKE_CXX_STANDARD 14)
set(THREADS_PREFER_PTHREAD_FLAG ON)

include_directories(lib/pugixml)
include_directories(src)

find_package(SDL2 REQUIRED)
find_package(Threads REQUIRED)
find_library(SDL2TTF_LIBRARIES SDL_ttf)
find_library(SDL2_MIXER REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(ProyectoTaller_Luminegro

        lib/pugixml/pugiconfig.hpp
        lib/pugixml/pugixml.cpp
        lib/pugixml/pugixml.hpp

        src/main.cpp

        src/comunicacion/MensajeCliente.cpp
        src/comunicacion/MensajeCliente.h
        src/comunicacion/MensajeServidor.cpp
        src/comunicacion/MensajeServidor.h
        src/comunicacion/Socket.cpp
        src/comunicacion/Socket.h
        src/comunicacion/RecibidorMensajesCliente.cpp
        src/comunicacion/RecibidorMensajesCliente.h
        src/comunicacion/MensajeCredenciales.cpp
        src/comunicacion/MensajeCredenciales.h
        src/comunicacion/EnviadorMensajesCliente.cpp
        src/comunicacion/EnviadorMensajesCliente.h
        src/comunicacion/RecibidorMensajesServidor.cpp
        src/comunicacion/RecibidorMensajesServidor.h
        src/comunicacion/EnviadorMensajesServidor.cpp
        src/comunicacion/EnviadorMensajesServidor.h
        src/comunicacion/AceptadorConexiones.cpp
        src/comunicacion/AceptadorConexiones.h
        src/comunicacion/UsuarioYClave.cpp
        src/comunicacion/UsuarioYClave.h

        src/estados/EstadoEnemigoAvanzando.cpp
        src/estados/EstadoEnemigoAvanzando.h
        src/estados/EstadoEnemigoParado.cpp
        src/estados/EstadoEnemigoParado.h
        src/estados/EstadoEnemigoPegando.cpp
        src/estados/EstadoEnemigoPegando.h
        src/estados/EstadoEnemigoMuriendo.cpp
        src/estados/EstadoEnemigoMuriendo.h
        src/estados/EstadoEnemigoGolpeado.cpp
        src/estados/EstadoEnemigoGolpeado.h
        src/estados/EstadoJugador.cpp
        src/estados/EstadoJugador.h
        src/estados/EstadoJugadorAgachado.cpp
        src/estados/EstadoJugadorAgachado.h
        src/estados/EstadoJugadorAvanzando.cpp
        src/estados/EstadoJugadorAvanzando.h
        src/estados/EstadoJugadorParado.cpp
        src/estados/EstadoJugadorParado.h
        src/estados/EstadoJugadorPateando.cpp
        src/estados/EstadoJugadorPateando.h
        src/estados/EstadoJugadorPegando.cpp
        src/estados/EstadoJugadorPegando.h
        src/estados/EstadoJugadorSaltando.cpp
        src/estados/EstadoJugadorSaltando.h
        src/estados/EstadoJugadorCongelado.cpp
        src/estados/EstadoJugadorCongelado.h
        src/estados/EstadoJugadorMuriendo.h
        src/estados/EstadoJugadorMuriendo.cpp
		src/estados/EstadoJugadorApaleando.h
		src/estados/EstadoJugadorApaleando.cpp
		src/estados/EstadoJugadorAcuchillando.h
		src/estados/EstadoJugadorGolpeado.cpp
		src/estados/EstadoJugadorGolpeado.h
		src/estados/EstadoObjetoEntero.cpp
		src/estados/EstadoObjetoEntero.h
		src/estados/EstadoObjetoRoto.cpp
		src/estados/EstadoObjetoRoto.h


        src/grafica/Encuadre.cpp
        src/grafica/Encuadre.h
        src/grafica/Imagen.cpp
        src/grafica/Imagen.h
        src/grafica/Renderizador.cpp
        src/grafica/Renderizador.h
        src/grafica/VentanaClienteInicioSesion.cpp
        src/grafica/VentanaClienteInicioSesion.h
        src/grafica/Textura.cpp
        src/grafica/Textura.h
        src/grafica/VentanaCliente.cpp
        src/grafica/VentanaCliente.h

		src/modelos/Modelo.cpp
		src/modelos/Modelo.h
        src/modelos/BarrilModelo.cpp
        src/modelos/BarrilModelo.h
        src/modelos/CajaModelo.cpp
        src/modelos/CajaModelo.h
        src/modelos/ControlEnemigosModelo.cpp
        src/modelos/ControlEnemigosModelo.h
        src/modelos/ControlJugadoresModelo.cpp
        src/modelos/ControlJugadoresModelo.h
        src/modelos/ControlObjetosModelo.cpp
        src/modelos/ControlObjetosModelo.h
        src/modelos/CuchilloModelo.cpp
        src/modelos/CuchilloModelo.h
        src/modelos/ElementoModelo.cpp
        src/modelos/ElementoModelo.h
        src/modelos/EnemigoModelo.cpp
        src/modelos/EnemigoModelo.h
        src/modelos/EnemigoJefeModelo.cpp
		src/modelos/EnemigoJefeModelo.h
        src/modelos/FondoModelo.cpp
        src/modelos/FondoModelo.h
        src/modelos/JugadorModelo.cpp
        src/modelos/JugadorModelo.h
        src/modelos/TuboModelo.cpp
        src/modelos/TuboModelo.h
        src/modelos/PersonaModelo.cpp
        src/modelos/PersonaModelo.h
        src/modelos/Colisionador.cpp
        src/modelos/Colisionador.h
        src/modelos/Colisionable.cpp
        src/modelos/Colisionable.h
        src/modelos/TipoDeArma.h

		src/varios/Cliente.cpp
        src/varios/Cliente.h
        src/varios/Logger.cpp
        src/varios/Logger.h
        src/varios/Servidor.cpp
        src/varios/Servidor.h
        src/varios/ConfigManager.cpp
        src/varios/ConfigManager.h
        src/varios/ColaMensajesCliente.cpp
        src/varios/ColaMensajesCliente.h
        src/varios/GestorThreadsServidor.cpp
        src/varios/GestorThreadsServidor.h
        src/varios/GestorThreadsCliente.cpp
        src/varios/GestorThreadsCliente.h
        src/varios/ColaMensajesServidor.cpp
        src/varios/ColaMensajesServidor.h
        src/varios/Common.cpp
        src/varios/Common.h
        src/varios/ContadorDeJugadores.cpp
        src/varios/ContadorDeJugadores.h
        src/varios/InformacionJugador.cpp
        src/varios/InformacionJugador.h
		src/varios/Sonidos.cpp
		src/varios/Sonidos.h

		src/vistas/VistaEnemigo.cpp
        src/vistas/VistaEnemigo.h
        src/vistas/VistaFondo.cpp
        src/vistas/VistaFondo.h
        src/vistas/VistaFondoCielo.cpp
        src/vistas/VistaFondoCielo.h
        src/vistas/VistaFondoEdificios.cpp
        src/vistas/VistaFondoEdificios.h
        src/vistas/VistaFondoTerreno.cpp
        src/vistas/VistaFondoTerreno.h
        src/vistas/VistaGeneral.cpp
        src/vistas/VistaGeneral.h
        src/vistas/VistaJugador.cpp
        src/vistas/VistaJugador.h
        src/vistas/VistaObjeto.cpp
        src/vistas/VistaObjeto.h
        src/estados/EstadoJugadorMuriendo.cpp src/estados/EstadoJugadorMuriendo.h src/estados/EstadoEnemigoMuriendo.cpp src/estados/EstadoEnemigoMuriendo.h src/estados/EstadoJugadorApaleando.cpp src/estados/EstadoJugadorApaleando.h src/estados/EstadoJugadorAcuchillando.cpp src/estados/EstadoJugadorAcuchillando.h src/comunicacion/MensajeInicioPartida.cpp src/comunicacion/MensajeInicioPartida.h)

target_link_libraries(ProyectoTaller_Luminegro ${SDL2_LIBRARIES})
target_link_libraries(ProyectoTaller_Luminegro ${SDL2TTF_LIBRARIES})
target_link_libraries(ProyectoTaller_Luminegro Threads::Threads)
target_link_libraries(ProyectoTaller_Luminegro ${CMAKE_THREAD_LIBES_INIT})
target_link_libraries(ProyectoTaller_Luminegro ${SDL2_MIXER_LIBRARY})
target_link_libraries(ProyectoTaller_Luminegro ${SDL2_MIXER_LIBRARIES})

