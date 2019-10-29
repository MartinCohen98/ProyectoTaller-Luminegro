#ifndef SRC_SERVIDOR_H_
#define SRC_SERVIDOR_H_

#include "../comunicacion/Socket.h"
#include "../comunicacion/MensajeCredenciales.h"
#include "../comunicacion/RechazadorConexiones.h"
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

private:
    std::thread* threadRechazadorConexiones;

    void validarCredenciales(MensajeCredenciales *mensajeCredenciales);
	void recibirInputs(ControlJugadoresModelo* protagonistas,
						GestorThreadsServidor* gestorThreads);
	void enviarCantidadDeReceives(ControlEnemigosModelo* enemigos,
							ControlObjetosModelo* objetos,
							GestorThreadsServidor* gestorThreads);
	void generarMensajes(ControlJugadoresModelo* protagonistas, FondoModelo* fondo,
			ControlEnemigosModelo* enemigos, ControlObjetosModelo* objetos);
	void enviarMensajes(GestorThreadsServidor* gestorThreads);
	void enviarMensajeDeNivelTerminado(bool nivelTerminado,
							GestorThreadsServidor* gestorThreadds);
	void generarMensajesParaEnviar();

public:
    Servidor(int cantidadDeJugadores, char* puerto);
    int AbrirSesion();
    int EsperarConexiones();
    void Correr(pugi::xml_document* archiConfig);
    virtual ~Servidor();

};

#endif /* SRC_SERVIDOR_H_ */
