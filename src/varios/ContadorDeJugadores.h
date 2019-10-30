#ifndef SRC_VARIOS_CONTADORDEJUGADORES_H_
#define SRC_VARIOS_CONTADORDEJUGADORES_H_

#include <thread>
#include <mutex>
#include <queue>
#include "../comunicacion/MensajeCredenciales.h"
#include "InformacionJugador.h"

class ContadorDeJugadores {

private:
	int espaciosDisponibles;
	std::mutex m;
	std::queue<InformacionJugador> cola;
	bool* conectados;
	int cantidadDeRecieves;

public:
	ContadorDeJugadores(int jugadores);
	bool hayEspacioDisponible();
	void seDesconectoElJugador(int jugador);
	void seConectoElJugador(int jugador);
	bool estaConectado(int jugador);
	void actualizarCantidadDeRecieves(int recieves);
	int obtenerCantidadDeRecieves();
	virtual ~ContadorDeJugadores();
};

#endif /* SRC_VARIOS_CONTADORDEJUGADORES_H_ */
