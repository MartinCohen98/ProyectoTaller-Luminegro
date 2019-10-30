#ifndef SRC_VARIOS_INFORMACIONJUGADOR_H_
#define SRC_VARIOS_INFORMACIONJUGADOR_H_

class InformacionJugador {

private:
	int numeroSocket;
	int numeroDeJugador;

public:
	InformacionJugador(int socket, int elNumero);
	int obtenerSocket();
	int obtenerNumeroDeJugador();
	virtual ~InformacionJugador();
};

#endif /* SRC_VARIOS_INFORMACIONJUGADOR_H_ */
