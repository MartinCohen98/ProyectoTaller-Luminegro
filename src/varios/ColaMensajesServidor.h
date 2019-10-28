#ifndef SRC_VARIOS_COLAMENSAJESSERVIDOR_H_
#define SRC_VARIOS_COLAMENSAJESSERVIDOR_H_

#include <thread>
#include <mutex>
#include <queue>
#include "../comunicacion/MensajeServidor.h"

class ColaMensajesServidor {

private:
	std::mutex m;
	std::queue<MensajeServidor> cola;

public:
	ColaMensajesServidor();
	void encolar(MensajeServidor* mensaje);
	MensajeServidor desencolar();
	virtual ~ColaMensajesServidor();
};

#endif /* SRC_VARIOS_COLAMENSAJESSERVIDOR_H_ */
