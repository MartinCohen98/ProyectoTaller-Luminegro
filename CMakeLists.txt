cmake_minimum_required(VERSION 3.14)
project(ProyectoTaller_Luminegro)

set(CMAKE_CXX_STANDARD 14)

include_directories(lib/pugixml)
include_directories(src)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(ProyectoTaller_Luminegro
        lib/pugixml/pugiconfig.hpp
        lib/pugixml/pugixml.cpp
        lib/pugixml/pugixml.hpp
        src/modelos/BarrilModelo.cpp
        src/modelos/BarrilModelo.h
        src/modelos/CajaModelo.cpp
        src/modelos/CajaModelo.h
        src/Cliente.cpp
        src/Cliente.h
        src/ControlEnemigosModelo.cpp
        src/ControlEnemigosModelo.h
        src/ControlJugadores.cpp
        src/ControlJugadores.h
        src/ControlObjetos.cpp
        src/ControlObjetos.h
        src/modelos/ControlObjetosModelo.cpp
        src/modelos/ControlObjetosModelo.h
        src/modelos/CuchilloModelo.cpp
        src/modelos/CuchilloModelo.h
        src/modelos/ElementoModelo.cpp
        src/modelos/ElementoModelo.h
        src/Encuadre.cpp
        src/Encuadre.h
        src/Enemigo.cpp
        src/Enemigo.h
        src/modelos/EnemigoModelo.cpp
        src/modelos/EnemigoModelo.h
        src/estados/EstadoEnemigoAvanzando.cpp
        src/estados/EstadoEnemigoAvanzando.h
        src/estados/EstadoEnemigoParado.cpp
        src/estados/EstadoEnemigoParado.h
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
        src/modelos/FondoModelo.cpp
        src/modelos/FondoModelo.h
        src/Imagen.cpp
        src/Imagen.h
        src/Jugador.cpp
        src/Jugador.h
        src/modelos/JugadorModelo.cpp
        src/modelos/JugadorModelo.h
        src/Logger.cpp
        src/Logger.h
        src/main.cpp
        src/MensajeCliente.cpp
        src/MensajeCliente.h
        src/MensajeServidor.cpp
        src/MensajeServidor.h
        src/Persona.cpp
        src/Persona.h
        src/modelos/PersonaModelo.cpp
        src/modelos/PersonaModelo.h
        src/Protagonista.cpp
        src/Protagonista.h
        src/Renderizador.cpp
        src/Renderizador.h
        src/Servidor.cpp
        src/Servidor.h
        src/VentanaClienteInicioSesion.cpp
        src/VentanaClienteInicioSesion.h
        src/Socket.cpp
        src/Socket.h
        src/Textura.cpp
        src/Textura.h
        src/modelos/TuboModelo.cpp
        src/modelos/TuboModelo.h
        src/ConfigManager.cpp
        src/ConfigManager.h
        src/VentanaCliente.cpp
        src/VentanaCliente.h
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
        src/vistas/VistaObjeto.h src/Cola.cpp src/Cola.h)
target_link_libraries(ProyectoTaller_Luminegro ${SDL2_LIBRARIES})
target_link_libraries(ProyectoTaller_Luminegro ${SDL2TTF_LIBRARIES})

