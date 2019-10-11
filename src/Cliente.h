/*
 * Cliente.h
 *
 *  Created on: 8 oct. 2019
 *      Author: julio
 */

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


class Cliente {
private:
	int puerto;
	int cantMaxDatos;
	Socket socket;
public:
	 Cliente();
	 int inicializar(char* direccionIP, char* puerto, pugi::xml_document* archiConfig);
	 int conectar(char* direccionIP, char* puerto);
	 int enviar(unsigned char* datos, int* cantidadDeBytes);
	 int recibir(unsigned char* datos, int* cantMaxDatos, bool* elSocketEsValido);
	 int cerrar();
	 virtual ~Cliente();
};

#endif /* SRC_CLIENTE_H_ */
