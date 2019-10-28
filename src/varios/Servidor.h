#ifndef SRC_SERVIDOR_H_
#define SRC_SERVIDOR_H_

#include "../comunicacion/Socket.h"
#include "../comunicacion/MensajeCredenciales.h"
#include "../modelos/ControlJugadoresModelo.h"
#include "../modelos/ControlEnemigosModelo.h"
#include "../modelos/ControlObjetosModelo.h"
#include "GestorThreadsServidor.h"

class Servidor {

private:
	int jugadores;
	MensajeCliente mensajeCliente;
	MensajeServidor* mensajesServidor;
	int cantidadDeMensajes;
	Socket socketAceptador;
	Socket* socketsDeClientes;
	char *puerto;


private:
    void validarCredenciales(MensajeCredenciales *mensajeCredenciales);
	void recibirInputs(ControlJugadoresModelo* protagonistas,
						GestorThreadsServidor* gestorThreads);
	void enviarCantidadDeReceives(ControlEnemigosModelo* enemigos,
							ControlObjetosModelo* objetos);
	void enviarEncuadres(ControlJugadoresModelo* protagonistas, FondoModelo* fondo,
			ControlEnemigosModelo* enemigos, ControlObjetosModelo* objetos);
	void enviarMensajeDeNivelTerminado(bool nivelTerminado);
	void generarMensajesParaEnviar();

public:
    Servidor(int cantidadDeJugadores, char* puerto);
    int AbrirSesion();
    int EsperarConexiones();
    void Correr(pugi::xml_document* archiConfig);
    virtual ~Servidor();

};

#endif /* SRC_SERVIDOR_H_ */
