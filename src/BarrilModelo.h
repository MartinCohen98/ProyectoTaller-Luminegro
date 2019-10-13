#ifndef SRC_BARRILMODELO_H_
#define SRC_BARRILMODELO_H_

#include "ElementoModelo.h"

class BarrilModelo: public ElementoModelo {

public:
	BarrilModelo(int posXinicial, int posYinicial);
	virtual ~BarrilModelo();
};

#endif /* SRC_BARRILMODELO_H_ */
