#ifndef SRC_MENSAJESERVIDOR_H_
#define SRC_MENSAJESERVIDOR_H_

#include "../grafica/Encuadre.h"
#include <string>

enum tipoDeSprite {Jugador1, Jugador2, Jugador3, Jugador4,
	Enemigo1, Enemigo2, Enemigo3, EnemigoJefe, Barril, Caja,
	Cuchillo, Tubo, MensajeInvalido
};

class MensajeServidor {

private:
	Encuadre frame;
	Encuadre insercion;
	bool dadoVuelta;
	int posicionY;
	tipoDeSprite sprite;
	bool ejecutarSonidoGolpeTiro = false;
	bool ejecutarSonidoGolpeImpacto = false;
	bool ejecutarSonidoSalto = false;
	bool ejecutarSonidoCaida = false;
	bool ejecutarSonidoDestruccion = false;

public:
	MensajeServidor();
	void generarMensaje(Encuadre* unFrame, Encuadre* unaInsercion, tipoDeSprite tipo);
	void darVuelta();
	void agregarPosicionY(int posicion);
	Encuadre* obtenerFrame();
	Encuadre* obtenerInsercion();
	bool estaDadoVuelta();
	tipoDeSprite obtenerTipoDeSprite();
	bool operator <(const MensajeServidor & mensaje) const;
    void setSonidoEjecutarGolpeTiro(bool valor);
    bool getSonidoEjecutarGolpeTiro();
    void setSonidoEjecutarGolpeImpacto(bool valor);
    bool getSonidoEjecutarGolpeImpacto();
    void setSonidoEjecutarSalto(bool valor);
    bool getSonidoEjecutarSalto();
    void setSonidoEjecutarCaida(bool valor);
    bool getSonidoEjecutarCaida();
    void setSonidoEjecutarDestruccion(bool valor);
    bool getSonidoEjecutarDestruccion();
	virtual ~MensajeServidor();
};

#endif /* SRC_MENSAJESERVIDOR_H_ */
