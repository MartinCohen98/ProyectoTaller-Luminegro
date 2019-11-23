#ifndef SRC_JUGADORMODELO_H_
#define SRC_JUGADORMODELO_H_

#include "../estados/EstadoJugadorParado.h"
#include "../estados/EstadoJugador.h"
#include "PersonaModelo.h"
#include "../../lib/pugixml/pugixml.hpp"
#include "../comunicacion/Socket.h"
#include "../comunicacion/MensajeServidor.h"
#include <string>
#include "../comunicacion/MensajeEstadoJugador.h"
#include "FondoModelo.h"
#include "Colisionador.h"

class JugadorModelo: public PersonaModelo {

private:
	int escaladoDeSprite;
	int movimientoEnX;
	int movimientoEnY;
	int movimientoAlSaltarEnX;
	int movimientoAlSaltarEnY;
	int posicionXMaxima;
	bool agachado;
	bool salio;
	bool desconectado;
	bool inmortal;
	bool ejecutarSonidoGolpeTiro = false;
	bool ejecutarSonidoGolpeImpacto = false;
    bool ejecutarSonidoSalto = false;
    bool ejecutarSonidoCaida = false;
    int vidas;
	int puntaje;
	int golpesDeArma;
	tipoDeArma arma;
	EstadoJugadorParado* estadoOriginal;

    void actualizarPosicion(FondoModelo* fondo, bool rezagado);
    void checkearColisiones(Colisionador* colisionador);
    void actualizarInsercion(bool conElevacion);
    bool moverEnX(FondoModelo* fondo, bool rezagado);
    bool moverEnY();
    bool movioAlFondo(FondoModelo* fondo);
    int escalar(int tamanio);

public:
	JugadorModelo(pugi::xml_document *archiConfig, int posXinicial, int poYinicial);
	void avanzar();
	void dejarDeAvanzar();
	void retroceder();
	void dejarDeRetroceder();
	void agacharse();
	void dejarDeAgacharse();
	void subir();
	void dejarDeSubir();
	void bajar();
	void dejarDeBajar();
	void pegar();
	void saltar();
	void congelarse();
    void acuchillar();
    void apalear();
    void morir();
    void serGolpeado();
	void desaparecer();
	void descongelarse();
	bool estaDesconectado();
	bool estaAtacando();
	int obtenerDanio();
	int obtenerPuntosDeGolpe();
	bool consultarModoTest();
	void activarModoTest();
	void desactivarModoTest();
	tipoDeArma consultarArma();
	int recibirDanioDe(Colisionable* colisionable);
	void realizarMovimientos(FondoModelo* fondo, bool rezagado,
										Colisionador* colisionador);
	bool llegoAlFin(FondoModelo *fondo);
	void movidaDePantalla(FondoModelo* fondo);
	void generarMensaje(MensajeServidor* mensajes, int* mensajeActual,
							int numeroSprite);
	MensajeEstadoJugador generarMensajeEstado(int numeroJugador);
	virtual ~JugadorModelo();
};

#endif /* SRC_JUGADORMODELO_H_ */
