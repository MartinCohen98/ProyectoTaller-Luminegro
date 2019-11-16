#ifndef SRC_MODELOS_MODELO_H_
#define SRC_MODELOS_MODELO_H_

#include "../modelos/FondoModelo.h"
#include "../modelos/ControlJugadoresModelo.h"
#include "../modelos/ControlEnemigosModelo.h"
#include "../modelos/ControlObjetosModelo.h"

class Modelo {

private:
	int cantidadJugadores;
    pugi::xml_document* archivoConfiguracion;
    FondoModelo* fondo;
    ControlJugadoresModelo* protagonistas;
    ControlEnemigosModelo* enemigos;
    ControlObjetosModelo* objetos;
    int nivelActual;
    int atacante;

public:
	Modelo(pugi::xml_document* archiConfig, int cantidadDeJugadores);
	int obtenerCantidadDeEntidades();
	void procesarInputDeJugador(MensajeCliente* mensaje, int jugador);
	void realzarMovimientos();
	void generarMensajesServidor(MensajeServidor* mensajes);
	bool nivelTerminado();
	void pasarNivel();
	void desaparecerJugador(int jugador);
	void desconectarJugador(int jugador);
	void conectarJugador(int jugador);
	virtual ~Modelo();
};

#endif /* SRC_MODELOS_MODELO_H_ */
