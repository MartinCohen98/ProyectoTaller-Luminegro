/*
 * EnemigoJefeModelo.h
 *
 *  Created on: 15 nov. 2019
 *      Author: julio
 */

#include "EnemigoModelo.h"

#ifndef SRC_MODELOS_ENEMIGOJEFEMODELO_H_
#define SRC_MODELOS_ENEMIGOJEFEMODELO_H_

class EnemigoJefeModelo: public EnemigoModelo {
public:
	EnemigoJefeModelo();
	EnemigoJefeModelo(int posXinicial, int posYinicial, tipoDeSprite tipo);
	virtual ~EnemigoJefeModelo();
};

#endif /* SRC_MODELOS_ENEMIGOJEFEMODELO_H_ */
