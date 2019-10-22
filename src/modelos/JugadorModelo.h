#ifndef SRC_JUGADORMODELO_H_
#define SRC_JUGADORMODELO_H_

#include "../estados/EstadoJugadorParado.h"
#include "PersonaModelo.h"
#include "../../lib/pugixml/pugixml.hpp"
#include "../varios/Socket.h"
#include "../varios/MensajeServidor.h"
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
	void realizarMovimientos(FondoModelo* fondo);
	bool llegoAlFin(FondoModelo *fondo);
	void movidaDePantalla(FondoModelo* fondo);
	void generarMensaje(MensajeServidor* mensajes, int* mensajeActual,
							int numeroSprite);
	virtual ~JugadorModelo();

private:
	void actualizarPosicion(FondoModelo* fondo);
	void actualizarInsercion();
	bool moverEnX(FondoModelo* fondo);
	bool moverEnY();
	bool movioAlFondo(FondoModelo* fondo);
	int escalar(int tamanio);
};

#endif /* SRC_JUGADORMODELO_H_ */
