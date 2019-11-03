#ifndef SRC_SERVIDOR_H_
#define SRC_SERVIDOR_H_

#include "../comunicacion/AceptadorConexiones.h"
#include "../comunicacion/Socket.h"
#include "../comunicacion/MensajeCredenciales.h"
#include "../modelos/ControlJugadoresModelo.h"
#include "../modelos/ControlEnemigosModelo.h"
#include "../modelos/ControlObjetosModelo.h"
#include "GestorThreadsServidor.h"
#include "../comunicacion/UsuarioYClave.h"

enum jugadoresNombres {mariano, julio, martin, nicolas};


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

    void recibirInputs(ControlJugadoresModelo* protagonistas);
	void enviarCantidadDeReceives(ControlEnemigosModelo* enemigos,
							ControlObjetosModelo* objetos);
	void enviarMensajes(ControlJugadoresModelo* protagonistas, FondoModelo* fondo,
			ControlEnemigosModelo* enemigos, ControlObjetosModelo* objetos);
	void enviarMensajeDeNivelTerminado(bool nivelTerminado);
	void generarMensajesParaEnviar();
    void desconectarJugadoresDesconectados(ControlJugadoresModelo* jugadores);
    void leerTodosLosUsuariosYClavesDelConfig(int *cantidadDeJugadores);
    bool validarUsuarioYClave(MensajeCredenciales* mensajeCredenciales);

public:
    Servidor(int cantidadDeJugadores, char* puerto, pugi::xml_document* archivoConfiguracion);
    int abrirSesion();
    int esperarConexiones();
    void correr();
    virtual ~Servidor();

};

#endif /* SRC_SERVIDOR_H_ */
