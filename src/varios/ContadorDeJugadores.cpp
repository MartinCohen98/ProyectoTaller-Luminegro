#include "ContadorDeJugadores.h"

ContadorDeJugadores::ContadorDeJugadores(int jugadores) {
	cantidad = jugadores;
	espaciosDisponibles = jugadores;
	conectados = new bool[jugadores];
	for (int i = 0; i < jugadores; i++) {
		conectados[i] =  true;
	}
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
    int jugadorNombre;
    std::string usuario = mensaje->getUsuario();
    m.lock();
    if (usuario.compare("mariano") == 0) {
        claveCorrecta = "cognitiva";

    } else if (usuario.compare("julio") == 0) {
        claveCorrecta = "conductual";

    } else if (usuario.compare("martin") == 0) {
        claveCorrecta = "gestalt";

    } else if (usuario.compare("nicolas") == 0) {
        claveCorrecta = "freud";
    }

    if (mensaje->getClave() == claveCorrecta) {
        mensaje->setEstado(MensajeCredenciales::ESTADO_AUTENTICADO);
        for (int i = 0; i < cantidad; i++) {
        	if (!conectados[i]) {
        		conectados[i] = true;
        		espaciosDisponibles--;
        		InformacionJugador info(socket->obtenerNumero(), i);
        		cola.push(info);
        	}
        }
    } else {
    	mensaje->setEstado(MensajeCredenciales::ESTADO_USUARIO_O_CLAVE_ERRONEOS);
    }
    socket->enviar(mensaje);
    m.unlock();
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

