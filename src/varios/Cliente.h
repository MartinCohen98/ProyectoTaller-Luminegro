#ifndef SRC_CLIENTE_H_
#define SRC_CLIENTE_H_

#include "Socket.h"
#include "vistas/VistaEnemigo.h"
#include "vistas/VistaFondo.h"
#include "vistas/VistaJugador.h"
#include "vistas/VistaObjeto.h"
#include "grafica/VentanaCliente.h"
#include "ConfigManager.h"
#include "grafica/Renderizador.h"
#include "MensajeCliente.h"
#include "MensajeServidor.h"
#include <pthread.h>
#include <iostream>
#include "Logger.h"
#include <SDL2/SDL.h>
#include <string>

using namespace std;

class Cliente {
private:
	int cantMaxDatos;
	int cantidadDeReceives;
	Socket socket;
	SDL_Event evento;
	MensajeCliente mensajeCliente;
	MensajeServidor mensajeServidor;

public:
	 Cliente();
	 int inicializar(char* direccionIP, char* puerto, pugi::xml_document* archiConfig);
	 int conectar(char* direccionIP, char* puerto);
	 virtual ~Cliente();

private:
	 void recibirFondo(VistaFondo* fondo);
	 void enviarInput(MensajeCliente* mensaje);
	 void recibirCantidadDeReceives();
	 bool terminoElNivel();
	 tipoDeSprite recibirMensaje();
};

#endif /* SRC_CLIENTE_H_ */
