#ifndef SRC_ENEMIGOMODELO_H_
#define SRC_ENEMIGOMODELO_H_

#include "PersonaModelo.h"
#include "../estados/EstadoEnemigoParado.h"
#include "../comunicacion/Socket.h"
#include "Colisionador.h"
#include "JugadorModelo.h"

enum accionDeEnemigo {Detenido, Patrullando,
           Esquivando, Atacando};

class EnemigoModelo: public PersonaModelo {

protected:
	int ancho;
	int alto;
	float escaladoDeSprite;
    bool subiendo;
    bool avanzando;
    int bordeSuperior;
    int bordeInferior;
    int limiteInicial;
    int limiteFinal;
    int jugadorObjetivo;
    JugadorModelo* objetivo;
    int tiempoDeGolpe;
    int tiempoDeEsquivada;
    int vivo;
    accionDeEnemigo modo, modoAnterior;
    tipoDeSprite tipoEnemigo;
    bool ejecutarSonidoCaida = false;
    bool ejecutarSonidoGolpeTiro = false;
    bool ejecutarSonidoGolpeImpacto = false;

public:
    EnemigoModelo();
	EnemigoModelo(int posXinicial, int posYinicial, tipoDeSprite tipo,FondoModelo* fondo);
	void avanzar();
	void parar();
	void retroceder();
	void subir();
	void bajar();
    void pegar();
    void morir();
    void serGolpeado();
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
	void atacar();
	void esquivar();
	void cambiarModo(accionDeEnemigo nuevoModo);
	void asignarObjetivo(JugadorModelo *jugador);
	bool estaVivo();
	bool estaMuerto();
	void verificarMuerte();
	bool muerteTerminada();
	void retrocesoDePantalla();
	void guardarPosicionesActuales();
	int recibirDanioDe(Colisionable* colisionable);
	int obtenerDanio();
	bool estaAtacando();
	void realizarMovimientos(Colisionador* colisionador);
	void generarMensaje(MensajeServidor* mensajes, int* mensajeActual);
	virtual ~EnemigoModelo();

protected:
	void checkearColisiones(Colisionador* colisionador);
	void actualizarInsercion();
	void moverEnX(int movimiento);
	void moverEnY(int movimiento);
	void desaparecer();
	int escalar(int tamanio);
};

#endif /* SRC_ENEMIGOMODELO_H_ */
