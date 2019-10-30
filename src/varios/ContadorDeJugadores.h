#ifndef SRC_VARIOS_CONTADORDEJUGADORES_H_
#define SRC_VARIOS_CONTADORDEJUGADORES_H_

#include <thread>
#include <mutex>
#include <queue>
#include "../comunicacion/MensajeCredenciales.h"
#include "../comunicacion/Socket.h"
#include "InformacionJugador.h"
#include <string>

class ContadorDeJugadores {

private:
	int cantidad;
	int espaciosDisponibles;
	std::mutex m;
	std::queue<InformacionJugador> cola;
	bool* conectados;
	MensajeCredenciales* credenciales;

public:
	ContadorDeJugadores(int jugadores);
	bool hayEspacioDisponible();
	void seDesconectoElJugador(int jugador);
	bool estaConectado(int jugador);
	void actualizarCantidadDeRecieves(int recieves);
	int obtenerCantidadDeRecieves();
	void validarCredenciales(MensajeCredenciales* mensaje, Socket* socket);
	void definirCredenciales(MensajeCredenciales* lasCredenciales);
	InformacionJugador obtenerInfo();
	virtual ~ContadorDeJugadores();
};

#endif /* SRC_VARIOS_CONTADORDEJUGADORES_H_ */
