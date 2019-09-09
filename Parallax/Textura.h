#ifndef SRC_TEXTURA_H_
#define SRC_TEXTURA_H_

#include "Renderizador.h"
#include "Imagen.h"

class Textura {

private:
	SDL_Texture* textura;

public:
	Textura(Renderizador* renderizador, Imagen* imagen);
	void copiarseEn(Renderizador* renderizador);
	virtual ~Textura();
};

#endif /* SRC_TEXTURA_H_ */
