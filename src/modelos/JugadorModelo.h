#ifndef SRC_JUGADORMODELO_H_
#define SRC_JUGADORMODELO_H_

#include "../estados/EstadoJugadorParado.h"
#include "PersonaModelo.h"
#include "../../lib/pugixml/pugixml.hpp"
#include "../comunicacion/Socket.h"
#include "../comunicacion/MensajeServidor.h"
#include <string>
#include "FondoModelo.h"

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
	EstadoJugadorParado* estadoOriginal;

public:
	JugadorModelo(pugi::xml_document *archiConfig);
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
	void desaparecer();
	void realizarMovimientos(FondoModelo* fondo, bool rezagado, bool conectado);
	bool llegoAlFin(FondoModelo *fondo);
	void movidaDePantalla(FondoModelo* fondo);
	void generarMensaje(MensajeServidor* mensajes, int* mensajeActual,
							int numeroSprite);
	int darPosicion();
	virtual ~JugadorModelo();

private:
	void actualizarPosicion(FondoModelo* fondo, bool rezagado);
	void actualizarInsercion();
	bool moverEnX(FondoModelo* fondo, bool rezagado);
	bool moverEnY();
	bool movioAlFondo(FondoModelo* fondo);
	int escalar(int tamanio);
};

#endif /* SRC_JUGADORMODELO_H_ */
