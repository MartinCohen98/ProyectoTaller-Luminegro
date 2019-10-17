#ifndef SRC_CLIENTE_H_
#define SRC_CLIENTE_H_

#include "Socket.h"
#include "VistaEnemigo.h"
#include "VistaFondo.h"
#include "VistaJugador.h"
#include "VistaObjeto.h"
#include "VentanaDeJuego.h"
#include "VentanaCliente.h"
#include "ConfigManager.h"
#include "Renderizador.h"
#include "MensajeCliente.h"
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
	char *puerto;
	int cantMaxDatos;
	Socket socket;
	SDL_Event evento;
	MensajeCliente mensajeCliente;

public:
	 Cliente(char* NumPuerto);
	 int inicializar(char* direccionIP, char* puerto, pugi::xml_document* archiConfig);
	 int conectar(char* direccionIP, char* puerto);
	 int recibir(long int* datos, int* cantMaxDatos, bool* elSocketEsValido);
	 void actualizar(int accionRecibida, Protagonista* protagonista);
	 virtual ~Cliente();

private:
	 void enviarInput(MensajeCliente* mensaje);
};

#endif /* SRC_CLIENTE_H_ */
