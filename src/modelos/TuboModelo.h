#ifndef SRC_TUBOMODELO_H_
#define SRC_TUBOMODELO_H_

#include "ElementoModelo.h"

class TuboModelo: public ElementoModelo {
public:
	TuboModelo(int posXinicial, int posYinicial);
	virtual ~TuboModelo();
};

#endif /* SRC_TUBOMODELO_H_ */
