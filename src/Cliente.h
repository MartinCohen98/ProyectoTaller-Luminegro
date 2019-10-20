#ifndef SRC_CLIENTE_H_
#define SRC_CLIENTE_H_

#include "Socket.h"
#include "VistaEnemigo.h"
#include "VistaFondo.h"
#include "VistaJugador.h"
#include "VistaObjeto.h"
#include "VentanaCliente.h"
#include "ConfigManager.h"
#include "Renderizador.h"
#include "MensajeCliente.h"
#include "MensajeServidor.h"
#include <pthread.h>
#include <iostream>
#include "Logger.h"
#include "Protagonista.h"
#include "ControlObjetos.h"
#include "ControlEnemigos.h"
#include "ControlJugadores.h"
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
