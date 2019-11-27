#include "EnemigoModelo.h"

EnemigoModelo::EnemigoModelo() {}

EnemigoModelo::EnemigoModelo(int posXinicial, int posYinicial, tipoDeSprite tipoNuevo,
								FondoModelo* fondoNuevo) {
	posicionX = posXinicial;
	posicionY = posYinicial;
	bordeSuperior = 180;
	bordeInferior = 320;
	fondo = fondoNuevo;
	limiteInicial = 0;
	limiteFinal = (fondo->obtenerAncho());
	escaladoDeSprite = 3.6;
	energia = 100;
	tipo = tipoNuevo;
	estado = new EstadoEnemigoParado(tipo);
	dadoVuelta = false;
	subiendo = false;
	tiempoDeGolpe = 0;
	tiempoDeEsquivada = 0;
	vivo = true;
	esAtacante = false;
	activado = false;
	estadoOriginal = new EstadoEnemigoParado(tipo);
	actualizarInsercion();
	delayDeGolpe = 0;
}


void EnemigoModelo::parar() {
	estado = estado->parar();
    actualizarInsercion();
}

void EnemigoModelo::avanzar() {
	if (posicionX < limiteFinal) {
  		dadoVuelta = false;
		estado = estado->avanzar();
		moverEnX(5);
		yendoAdelante=true;
	} else {
		parar();
		estado = estado->parar();
	}
	actualizarInsercion();
}

void EnemigoModelo::retroceder() {
	if (posicionX > limiteInicial) {
		dadoVuelta = true;
		estado = estado->avanzar();
		moverEnX(-5);
		yendoAdelante = false;
	} else {
		parar();
		estado = estado->parar();
	}
	actualizarInsercion();
}

void EnemigoModelo::subir() {
	if (posicionY > bordeSuperior) {
		estado = estado->avanzar();
		moverEnY(-1);
		subiendo = true;
	} else {
	    parar();
		estado = estado->parar();
	}
	actualizarInsercion();
}

void EnemigoModelo::bajar() {
	if (posicionY < bordeInferior) {
		moverEnY(1);
        estado = estado->avanzar();
        subiendo = false;
	} else {
	    parar();
		estado = estado->parar();
	}
	actualizarInsercion();
}

void EnemigoModelo::pegar() {
    ejecutarSonidoGolpeTiro = true;
    estado = estado->pegar();
    actualizarInsercion();
}

void EnemigoModelo::morir() {
    ejecutarSonidoCaida = true;
    estado = estado->morir();
    cambiarModo(Detenido);
    vivo = false;
    actualizarInsercion();
}

void EnemigoModelo::serGolpeado(){
	estado = estado->serGolpeado();
	actualizarInsercion();
}

void EnemigoModelo::avanzarDiagArriba(int tope){
    dadoVuelta = false;
    moverEnX(5);
    if (posicionY > tope) {
        moverEnY(-1);
        estado = estado->avanzar();
    } else {
        parar();
        estado = estado->parar();
    }
    yendoAdelante = true;
    subiendo = true;
    actualizarInsercion();
}

void EnemigoModelo::avanzarDiagAbajo(int tope){
    dadoVuelta = false;
    moverEnX(5);
    if (posicionY < tope) {
        moverEnY(1);
        estado = estado->avanzar();
    } else {
        parar();
        estado = estado->parar();
    }
    yendoAdelante=true;
    subiendo=false;
    actualizarInsercion();
}

void EnemigoModelo::retrocederDiagArriba(int tope){
    dadoVuelta = true;
    moverEnX(-5);
    if (posicionY > tope) {
        moverEnY(-1);
        estado = estado->avanzar();
    } else {
        parar();
        estado = estado->parar();
    }
    yendoAdelante = false;
    subiendo = true;
    actualizarInsercion();
}

void EnemigoModelo::retrocederDiagAbajo(int tope){
    dadoVuelta = true;
    if (posicionY < tope) {
        moverEnX(-5);
        moverEnY(1);
        estado = estado->avanzar();
    } else {
        parar();
        estado = estado->parar();
    }
    yendoAdelante = false;
    subiendo = false;
    actualizarInsercion();
}

void EnemigoModelo::trasladarse(int destinoX,int destinoY) {
    bool atras = false;
    bool abajo = false;
    bool alineado = false;

    if (destinoX < posicionX)
        atras = true;
    if (destinoY > posicionY)
        abajo = true;
    if (destinoY == posicionY)
    	alineado = true;

    if (atras & abajo & !alineado)
        retrocederDiagAbajo(destinoY);

    if (atras & !abajo & !alineado)
        retrocederDiagArriba(destinoY);

    if (!atras & abajo & !alineado)
        avanzarDiagAbajo(destinoY);

    if (!atras & !abajo & !alineado)
        avanzarDiagArriba(destinoY);

    if (alineado){
    	if (!atras)
           avanzar();
    	else{
    		dadoVuelta = true;
    		estado = estado->avanzar();
    		moverEnX(-5);
    		yendoAdelante = false;
    		actualizarInsercion();
    	}
      }

    if (posicionY == bordeSuperior)
       bajar();
    if (posicionY == bordeInferior)
       subir();
}

void EnemigoModelo::patrullar(){
	if (modo == Patrullando && estado->puedeMoverse() & tiempoDeGolpe>0){
		if (posicionY == bordeSuperior)
			subiendo = false;
		if (posicionY == bordeInferior)
			subiendo = true;
		if (posicionX == limiteFinal) {
			yendoAdelante = false;
			retroceder();
		}
		if (posicionX == limiteInicial){
			yendoAdelante = true;
			avanzar();
		}
		if (!subiendo){
			if (dadoVuelta) {
				retrocederDiagAbajo(bordeInferior);
			} else {
				avanzarDiagAbajo(bordeInferior);
			}
		} else {
			if (dadoVuelta) {
				retrocederDiagArriba(bordeSuperior);
			} else {
				avanzarDiagArriba(bordeSuperior);
			}
		}
		if (esAtacante){
			tiempoDeGolpe++;
			if(tiempoDeGolpe == 20){
				cambiarModo(Atacando);
				tiempoDeGolpe = 0;
			}
		}
	} else {
		estado = estado->parar();
	}
}

void EnemigoModelo::modificarJugadorObjetivo(int objetivo){
	jugadorObjetivo = objetivo;
}

int EnemigoModelo::consultarJugadorObjetivo(){
	return jugadorObjetivo;
}

void EnemigoModelo::atacar() {
	if (modo == Atacando){
		int diferenciaDeY = 20;
		if (tipo == EnemigoJefe)
			diferenciaDeY = -80;
		esAtacante = true;
		int x, y;
		x = objetivo->darPosicionX();
		y = objetivo->darPosicionY();

		if (yendoAdelante) {
			trasladarse(x - 110, y + diferenciaDeY);
		} else {
			trasladarse(x + 110, y + diferenciaDeY);
		}
	}
}

void EnemigoModelo::esquivar() {

			if (yendoAdelante) {
				switch (tiempoDeEsquivada){
				case 0:
				   retrocederDiagAbajo(posicionY+5);
				   break;
				case 1:
			       retrocederDiagArriba(posicionY-5);
			       break;
				}
			}
			 else {
				switch (tiempoDeEsquivada){
				case 0:
			       avanzarDiagArriba(posicionY-5);
			       break;
				case 1:
			       avanzarDiagAbajo(posicionY+5);
			       break;
			    }
			 }
			tiempoDeEsquivada++;
			if (tiempoDeEsquivada==2)
				tiempoDeEsquivada=0;
}

void EnemigoModelo::cambiarModo(accionDeEnemigo nuevoModo){
	modo = nuevoModo;
}

accionDeEnemigo EnemigoModelo::consultarModo(){
	return modo;
}

bool EnemigoModelo::consultarEsAtacante(){
	return esAtacante;
}

void EnemigoModelo::ponerAtacante(){
	esAtacante = true;
}

void EnemigoModelo::asignarObjetivo(JugadorModelo *jugador){
	objetivo = jugador;
}

JugadorModelo* EnemigoModelo::consultarObjetivo(){
	return objetivo;
}

bool EnemigoModelo::estaVivo(){
	return vivo;
}

bool EnemigoModelo::estaMuerto(){
	return (estado->estaMuerto());
}

bool EnemigoModelo::muerteTerminada(){
	return (estado->terminado());
}

void EnemigoModelo::verificarMuerte(){
	if ((estado->estaMuerto() || !vivo) && estado->terminado()){
		desaparecer();
		cambiarModo(Detenido);
	}
}

void EnemigoModelo::estaSubiendo(){
    subiendo = true;
}

void EnemigoModelo::estaBajando(){
    subiendo = false;
}

bool EnemigoModelo::estaAtacando() {
	return estado->estaAtacando();
}


bool EnemigoModelo::consultarSubiendo(){
    return subiendo;
}

void EnemigoModelo::retrocesoDePantalla() {
	posicionX = posicionX - 12;
}


void EnemigoModelo::guardarPosicionesActuales() {
	posicionXAnterior = posicionX;
	posicionYAnterior = posicionY;
}

int EnemigoModelo::recibirDanioDe(Colisionable* colisionable) {
	int puntos = 0;
	if ((colisionable->obtenerTipo() == Jugador1) ||
			(colisionable->obtenerTipo() == Jugador2) ||
			(colisionable->obtenerTipo() == Jugador3) ||
			(colisionable->obtenerTipo() == Jugador4)) {
		if (!estado->estaMuerto()) {
			energia -= colisionable->obtenerDanio();
			puntos = colisionable->obtenerPuntosDeGolpe();
			serGolpeado();
			if (energia <= 0) {
				morir();
				puntos += 500;
			}
		}
	}
	return puntos;
}

int EnemigoModelo::obtenerDanio() {
	return estado->obtenerDanio();
}

void EnemigoModelo::generarMensaje(MensajeServidor* mensajes, int* mensajeActual) {
	Encuadre sprite = estado->obtenerSprite();

	mensajes[*mensajeActual].generarMensaje(&sprite, &insercion, tipo);
    mensajes[*mensajeActual].setSonidoEjecutarGolpeTiro(ejecutarSonidoGolpeTiro);
    mensajes[*mensajeActual].setSonidoEjecutarGolpeImpacto(ejecutarSonidoGolpeImpacto);
    mensajes[*mensajeActual].setSonidoEjecutarCaida(ejecutarSonidoCaida);

    ejecutarSonidoGolpeTiro = false;
    ejecutarSonidoGolpeImpacto = false;
    ejecutarSonidoCaida = false;

	if (dadoVuelta)
		mensajes[*mensajeActual].darVuelta();

	(*mensajeActual)++;
}


void EnemigoModelo::actualizarInsercion() {
	bool modoDeGraficado = dadoVuelta;
	if(estado->estaMuerto()) {
		modoDeGraficado = (!modoDeGraficado);
	}
	if (!modoDeGraficado) {
		insercion.modificar(posicionX, posicionY,
			escalar(estado->obtenerAncho()), escalar(estado->obtenerAlto()));
	} else {
		insercion.modificar(posicionX - escalar(estado->obtenerAncho()) +
			escalar(estadoOriginal->obtenerAncho()),
			posicionY, escalar(estado->obtenerAncho()),
			escalar(estado->obtenerAlto()));
	}
}


void EnemigoModelo::moverEnX(int movimiento) {
	posicionX = posicionX + movimiento;
}


void EnemigoModelo::moverEnY(int movimiento) {
	posicionY = posicionY + movimiento;
}


void EnemigoModelo::realizarMovimientos(Colisionador* colisionador) {
	verificarMuerte();
	limiteInicial = (fondo->darInicioTerreno());

	if (!activado)

	  if (((fondo->darInicioTerreno()*2.7)) > (posicionX)){
	    activado = true;
	    if (!esAtacante)
		  cambiarModo(Patrullando);
	  }

	switch (modo){
		case Detenido:{
			parar();
			break;
		}
		case Patrullando:{
			patrullar();
			break;
		}
		case Esquivando:{
			esquivar();
			break;
		}
		case Atacando:{
			atacar();
			break;
		}
	}
	checkearColisiones(colisionador);
}


void EnemigoModelo::checkearColisiones(Colisionador* colisionador) {
	actualizarInsercion();
	tipoDeSprite tipoColision;
	if (colisionador->colisiona(this, &tipoColision)) {
		posicionX = posicionXAnterior;
		posicionY = posicionYAnterior;
        switch(tipoColision){
        	case Enemigo1:
        	case Enemigo2:
        	case Enemigo3:
        	case EnemigoJefe:
        	case Barril:
        	case Caja:
        		esquivar();
        		break;
        	case Jugador1:
        	case Jugador2:
        	case Jugador3:
        	case Jugador4:{
        		switch(modo){
        		case Atacando:
        			delayDeGolpe++;
        			if (tiempoDeGolpe == 0 && delayDeGolpe >= 10){
        				pegar();
        				if (ejecutarSonidoGolpeTiro)  ejecutarSonidoGolpeImpacto = true;
                        delayDeGolpe = 0;
                        cambiarModo(Patrullando);
                    }
        			tiempoDeGolpe++;
        			if (tiempoDeGolpe == 4)
        				tiempoDeGolpe = 0;
        			break;
        		/*case Patrullando:
        			esquivar();
        			break;*/
        		break;
        		}
        	}
        }
		actualizarInsercion();
	}
}

void EnemigoModelo::desaparecer() {
	escaladoDeSprite = 0;
	cambiarModo(Detenido);
	posicionY = 10000;
}

int EnemigoModelo::escalar(int tamanio) {
	return (tamanio * escaladoDeSprite);
}


EnemigoModelo::~EnemigoModelo() {}

