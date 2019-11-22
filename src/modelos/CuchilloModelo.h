#ifndef SRC_CUCHILLOMODELO_H_
#define SRC_CUCHILLOMODELO_H_

#include "ElementoModelo.h"

class CuchilloModelo: public ElementoModelo {

public:
	CuchilloModelo(int posXinicial, int posYinicial);
	tipoDeArma obtenerTipoDeArma();
	virtual ~CuchilloModelo();
};

#endif /* SRC_CUCHILLOMODELO_H_ */
