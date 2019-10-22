#ifndef SRC_VARIOS_COLAMENSAJESCLIENTE_H_
#define SRC_VARIOS_COLAMENSAJESCLIENTE_H_

#include <thread>
#include <mutex>
#include <queue>
#include "comunicacion/MensajeCliente.h"

class ColaMensajesCliente {

private:
	std::mutex m;
	std::queue<MensajeCliente> cola;

public:
	ColaMensajesCliente();
	void encolar(MensajeCliente* mensaje);
	MensajeCliente desencolar();
	virtual ~ColaMensajesCliente();
};

#endif /* SRC_VARIOS_COLAMENSAJESCLIENTE_H_ */
