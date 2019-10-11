/*
 * Cliente.cpp
 *
 *  Created on: 8 oct. 2019
 *      Author: julio
 */

#include "Cliente.h"

Cliente::Cliente() {
	// TODO Auto-generated constructor stub

}

int Cliente::inicializar(char* direccionIP, char* puerto, pugi::xml_document* archiConfig){

	VentanaCliente ventana;

	int resultado=conectar(direccionIP, puerto);

	int retorno = ventana.abrir(archiConfig);

	return retorno;

}

int Cliente::conectar(char* direccionIP, char* puerto){

	int resultado=socket.conectarAUnServidor(direccionIP, puerto);
	return resultado;
}

int Cliente::enviar(unsigned char* datos, int* cantidadDeBytes){

}

int Cliente::recibir(unsigned char* datos, int* cantMaxDatos, bool* elSocketEsValido){

}

int Cliente::cerrar(){

}

Cliente::~Cliente() {
	// TODO Auto-generated destructor stub
}

