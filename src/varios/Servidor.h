#ifndef SRC_SERVIDOR_H_
#define SRC_SERVIDOR_H_

#include "../comunicacion/AceptadorConexiones.h"
#include "../comunicacion/MensajeCredenciales.h"
#include "GestorThreadsServidor.h"
#include "../comunicacion/UsuarioYClave.h"

enum jugadoresNombres {
	mariano, julio, martin, nicolas
};

class Servidor {

private:
	int jugadoresCantidadEsperada;
	int nivelActual;
	MensajeCliente mensajeCliente;
	MensajeServidor* mensajesServidor;
	int cantidadDeMensajes;
	Socket socketAceptador;
	Socket* socketsDeClientes;
	char *puerto;
	MensajeCredenciales credenciales[4];
	GestorThreadsServidor* gestorThreads;
	pugi::xml_document* archivoConfiguracion;
	UsuarioYClave* usuariosYClaves;
	Modelo* modelo;

public:
	Servidor(int cantidadDeJugadores, char* puerto,
			pugi::xml_document* archivoConfiguracion);
	int abrirSesion();
	int esperarConexiones();
	void correr();
	virtual ~Servidor();

private:
	void jugarNivel();
	void recibirInputs();
	void enviarCantidadDeReceives();
	void enviarMensajes();
	void enviarMensajeDeNivelTerminado(bool nivelTerminado);
	void generarMensajesParaEnviar();
	void desconectarJugadoresDesconectados();
	void leerTodosLosUsuariosYClavesDelConfig(int *cantidadDeJugadores);
	bool validarUsuarioYClave(MensajeCredenciales* mensajeCredenciales);
	MensajeInicioPartida generarMensajeInicioPartida();
	int enviarMensajeInicioPartida(MensajeInicioPartida *mensaje);

};

#endif /* SRC_SERVIDOR_H_ */
