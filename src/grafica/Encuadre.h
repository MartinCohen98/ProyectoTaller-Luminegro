#ifndef ENCUADRE_H_
#define ENCUADRE_H_
#include <SDL2/SDL.h>

class Encuadre {
     private:
	       SDL_Rect encuadre;
     public:
	       Encuadre();
	       Encuadre(int desplazamientoX, int desplazamientoY, int resolucionX, int resolucionY);
	       SDL_Rect get();
	       int getX();
	       int getY() const;
	       int getAncho();
	       int getAlto() const;
	       int modificar(int desplazamientoX, int desplazamientoY, int resolucionX, int resolucioY);
	       virtual ~Encuadre();
};


#endif /* ENCUADRE_H_ */
