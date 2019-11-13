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
    int bordeSuperior=180;
    int bordeInferior=320;
    int jugadorObjetivo;
    tipoDeSprite tipoEnemigo;

public:
    EnemigoModelo();
	EnemigoModelo(int posXinicial, int posYinicial, tipoDeSprite tipo);
	void avanzar();
	void parar();
	void retroceder();
	void agacharse();
	void subir();
	void bajar();
    void pegar();
    void morir();
    void acuchillar();
    void apalear();
	void avanzarDiagArriba(int tope);
	void avanzarDiagAbajo(int tope);
	void retrocederDiagArriba(int tope);
	void retrocederDiagAbajo(int tope);
    void estaSubiendo();
    void estaBajando();
    bool consultarSubiendo();
	void trasladarse(int destinoX,int destinoY);
	void patrullar();
	void modificarJugadorObjetivo(int objetivo);
	int consultarJugadorObjetivo();
	void atacar(int objetivo);
	void retrocesoDePantalla();
	void generarMensaje(MensajeServidor* mensajes, int* mensajeActual);
	virtual ~EnemigoModelo();

private:
	void actualizarInsercion();
	void moverEnX(int movimiento);
	void moverEnY(int movimiento);
};

#endif /* SRC_ENEMIGOMODELO_H_ */
