#include "ContadorDeJugadores.h"

ContadorDeJugadores::ContadorDeJugadores(int jugadores) {
	cantidad = jugadores;
	espaciosDisponibles = jugadores;
	conectados = new bool[jugadores];
	for (int i = 0; i < jugadores; i++) {
		conectados[i] =  true;
	}
	credenciales = NULL;
}


bool ContadorDeJugadores::hayEspacioDisponible() {
	return (espaciosDisponibles > 0);
}


void ContadorDeJugadores::seDesconectoElJugador(int jugador) {
	m.lock();
	conectados[jugador] = false;
	espaciosDisponibles++;
	m.unlock();
}


void ContadorDeJugadores::seConectoElJugador(int jugador) {
	m.lock();
	conectados[jugador] = true;
	espaciosDisponibles--;
	m.unlock();
}


bool ContadorDeJugadores::estaConectado(int jugador) {
	return conectados[jugador];
}


void ContadorDeJugadores::validarCredenciales(MensajeCredenciales* mensaje,
											Socket* socket) {
	std::string claveCorrecta;
	int numeroJugador;
    std::string usuario = mensaje->getUsuario();
    m.lock();

    for (int i = 0; i < cantidad; i++) {
    	if (!conectados[i] && (usuario.compare(credenciales[i].getUsuario()) == 0)) {
    		claveCorrecta = credenciales[i].getClave();
    		numeroJugador = i;
    	}
    }

    if (mensaje->getClave() == claveCorrecta) {
        mensaje->setEstado(MensajeCredenciales::ESTADO_AUTENTICADO);
        conectados[numeroJugador] = true;
        espaciosDisponibles--;
        InformacionJugador info(socket->obtenerNumero(), numeroJugador);
        cola.push(info);
    } else {
    	mensaje->setEstado(MensajeCredenciales::ESTADO_USUARIO_O_CLAVE_ERRONEOS);
    }
    socket->enviar(mensaje);
    m.unlock();
}


void ContadorDeJugadores::definirCredenciales(MensajeCredenciales* lasCredenciales) {
	credenciales = lasCredenciales;
}


InformacionJugador ContadorDeJugadores::obtenerInfo() {
	InformacionJugador info(0, 0);
	m.lock();
	if (!cola.empty()) {
		info = cola.front();
		cola.pop();
	}
	m.unlock();
	return info;
}


ContadorDeJugadores::~ContadorDeJugadores() {}

