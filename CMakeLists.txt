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
        src/Barril.cpp
        src/Barril.h
        src/Caja.cpp
        src/Caja.h
        src/ControlEnemigos.cpp
        src/ControlEnemigos.h
        src/ControlObjetos.cpp
        src/ControlObjetos.h
        src/Cuchillo.cpp
        src/Cuchillo.h
        src/Encuadre.cpp
        src/Encuadre.h
        src/Enemigo.cpp
        src/Enemigo.h
        src/EstadoEnemigoAvanzando.cpp
        src/EstadoEnemigoAvanzando.h
        src/EstadoEnemigoParado.cpp
        src/EstadoEnemigoParado.h
        src/EstadoJugador.cpp
        src/EstadoJugador.h
        src/EstadoJugadorAgachado.cpp
        src/EstadoJugadorAgachado.h
        src/EstadoJugadorAvanzando.cpp
        src/EstadoJugadorAvanzando.h
        src/EstadoJugadorParado.cpp
        src/EstadoJugadorParado.h
        src/EstadoJugadorPateando.cpp
        src/EstadoJugadorPateando.h
        src/EstadoJugadorPegando.cpp
        src/EstadoJugadorPegando.h
        src/EstadoJugadorSaltando.cpp
        src/EstadoJugadorSaltando.h
        src/Fondo.cpp
        src/Fondo.h
        src/Imagen.cpp
        src/Imagen.h
        src/Logger.cpp
        src/Logger.h
        src/main.cpp
        src/Protagonista.cpp
        src/Protagonista.h
        src/Renderizador.cpp
        src/Renderizador.h
        src/Socket.cpp
        src/Socket.h
        src/Textura.cpp
        src/Textura.h
        src/Tubo.cpp
        src/Tubo.h
        src/VentanaDeJuego.cpp
        src/VentanaDeJuego.h
        src/Socket.cpp
        src/Socket.h)

target_link_libraries(ProyectoTaller_Luminegro ${SDL2_LIBRARIES})