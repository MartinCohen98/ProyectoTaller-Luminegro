#ifndef PROYECTOTALLER_LUMINEGRO_VISTAESTADO_H
#define PROYECTOTALLER_LUMINEGRO_VISTAESTADO_H


#include "../grafica/Textura.h"
#include "../varios/InfoJugador.h"
#include "../../lib/pugixml/pugixml.hpp"

class VistaEstado {
private:
    Renderizador* renderizador;
    Textura texturaIcono;
    Encuadre encuadreIcono;
    Encuadre encuadreNombre;
    int maxVida;
    std::string nombreJugador;
public:
    VistaEstado(Renderizador *renderizador, pugi::xml_document *archiConfig, int maxVida, std::string nombreJugador, int numeroJugador);
    void renderizar(InfoJugador estadoJugador);

};


#endif //PROYECTOTALLER_LUMINEGRO_VISTAESTADO_H
