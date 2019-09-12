#ifndef SRC_TEXTURA_H_
#define SRC_TEXTURA_H_

#include "Renderizador.h"
#include "Imagen.h"
#include "Encuadre.h"



class Textura {

private:
	SDL_Texture* textura;

public:
	Textura();
	Textura(Renderizador* renderizador, Imagen imagen);
	void copiarseEn(Renderizador* renderizador,Encuadre encuadre,Encuadre encuadreFijo );
	int texturizar(Renderizador* renderizador, Imagen imagen);
	virtual ~Textura();
};

#endif /* SRC_TEXTURA_H_ */
