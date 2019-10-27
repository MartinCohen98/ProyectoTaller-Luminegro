#ifndef SRC_CLIENTE_H_
#define SRC_CLIENTE_H_

#include "../vistas/VistaEnemigo.h"
#include "../vistas/VistaFondo.h"
#include "../vistas/VistaJugador.h"
#include "../vistas/VistaObjeto.h"
#include "../grafica/VentanaCliente.h"
#include "ConfigManager.h"
#include "../grafica/Renderizador.h"
#include "../comunicacion/MensajeServidor.h"
#include "../comunicacion/MensajeCredenciales.h"
#include "../grafica/VentanaClienteInicioSesion.h"
#include "GestorThreadsCliente.h"
#include <iostream>
#include "Logger.h"
#include <SDL2/SDL.h>
#include <string>
#include <list>

using namespace std;

class Cliente {
private:
	int cantidadDeReceives;
	Socket socket;
	SDL_Event evento;
	MensajeCliente mensajeCliente;
	MensajeServidor* mensajesServidor;
	list<MensajeServidor> listaOrdenada;

public:
	 Cliente();
	 int inicializar(char* direccionIP, char* puerto, pugi::xml_document* archiConfig);
	 int conectar(char* direccionIP, char* puerto);
	 virtual ~Cliente();

private:
	 void renderizarFondo(VistaFondo* fondo);
	 void enviarInput(GestorThreadsCliente* gestorThreads);
	 void recibirCantidadDeReceives();
	 bool terminoElNivel();
	 void recibirMensajes();
	 void agregarMensajesALista();
};

#endif /* SRC_CLIENTE_H_ */
