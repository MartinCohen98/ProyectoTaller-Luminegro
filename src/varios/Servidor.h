#ifndef SRC_SERVIDOR_H_
#define SRC_SERVIDOR_H_

#include "../comunicacion/AceptadorConexiones.h"
#include "../comunicacion/Socket.h"
#include "../comunicacion/MensajeCredenciales.h"
#include "../modelos/ControlJugadoresModelo.h"
#include "../modelos/ControlEnemigosModelo.h"
#include "../modelos/ControlObjetosModelo.h"
#include "GestorThreadsServidor.h"

enum jugadoresNombres {mariano, julio, martin, nicolas};


class Servidor {

private:
	int jugadoresCantidadEsperada;
	bool jugadoresConectados[4];
	MensajeCliente mensajeCliente;
	MensajeServidor* mensajesServidor;
	int cantidadDeMensajes;
	Socket socketAceptador;
	Socket* socketsDeClientes;
	char *puerto;
	MensajeCredenciales credenciales[4];
	GestorThreadsServidor* gestorThreads;

private:
    void validarCredenciales(MensajeCredenciales *mensajeCredenciales);
	void recibirInputs(ControlJugadoresModelo* protagonistas);
	void enviarCantidadDeReceives(ControlEnemigosModelo* enemigos,
							ControlObjetosModelo* objetos);
	void enviarMensajes(ControlJugadoresModelo* protagonistas, FondoModelo* fondo,
			ControlEnemigosModelo* enemigos, ControlObjetosModelo* objetos);
	void enviarMensajeDeNivelTerminado(bool nivelTerminado);
	void generarMensajesParaEnviar();
    void desconectarJugadoresDesconectados(ControlJugadoresModelo* jugadores);

public:
    Servidor(int cantidadDeJugadores, char* puerto);
    int abrirSesion();
    int esperarConexiones();
    void correr(pugi::xml_document* archiConfig);
    virtual ~Servidor();

};

#endif /* SRC_SERVIDOR_H_ */
