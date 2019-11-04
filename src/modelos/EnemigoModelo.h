#ifndef SRC_ENEMIGOMODELO_H_
#define SRC_ENEMIGOMODELO_H_

#include "PersonaModelo.h"
#include "../estados/EstadoEnemigoParado.h"
#include "../comunicacion/Socket.h"

class EnemigoModelo: public PersonaModelo {

private:
	int ancho;
	int alto;
    bool subiendo;
    tipoDeSprite tipoEnemigo;

public:
	EnemigoModelo(int posXinicial, int posYinicial, tipoDeSprite tipo);
	void avanzar();
	void parar();
	void retroceder();
	void agacharse();
	void subir();
	void bajar();
	void avanzarDiagArriba();
	void avanzarDiagAbajo();
    void estaSubiendo();
    void estaBajando();
    bool consultarSubiendo();
	void retrocederDiagArriba();
	void retrocederDiagAbajo();
	void trasladarse(int destinoX,int destinoY);
	void patrullar();
	void retrocesoDePantalla();
	void generarMensaje(MensajeServidor* mensajes, int* mensajeActual);
	virtual ~EnemigoModelo();

private:
	void actualizarInsercion();
	void moverEnX(int movimiento);
	void moverEnY(int movimiento);
};

#endif /* SRC_ENEMIGOMODELO_H_ */
