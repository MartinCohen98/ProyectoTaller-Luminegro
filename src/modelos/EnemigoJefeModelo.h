#ifndef SRC_MODELOS_ENEMIGOJEFEMODELO_H_
#define SRC_MODELOS_ENEMIGOJEFEMODELO_H_

#include "EnemigoModelo.h"

class EnemigoJefeModelo: public EnemigoModelo {
public:
	EnemigoJefeModelo();
	EnemigoJefeModelo(int posXinicial, int posYinicial, tipoDeSprite tipo);
	virtual ~EnemigoJefeModelo();
};

#endif /* SRC_MODELOS_ENEMIGOJEFEMODELO_H_ */
