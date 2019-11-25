#include "EnemigoModelo.h"

EnemigoModelo::EnemigoModelo(){}

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
	subiendo=false;
	tiempoDeGolpe=0;
	tiempoDeEsquivada=0;
	vivo=true;
	esAtacante=false;
	activado=false;
	actualizarInsercion();
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
	}
	else {
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
	  yendoAdelante=false;
	}
	else {
	  parar();
	  estado = estado->parar();
	}
	actualizarInsercion();
}

void EnemigoModelo::subir() {
	if (posicionY > bordeSuperior) {
		estado = estado->avanzar();
		moverEnY(-1);
		subiendo=true;
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
        subiendo=false;
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
    yendoAdelante=true;
    subiendo=true;
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
    yendoAdelante=false;
    subiendo=true;
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
    yendoAdelante=false;
    subiendo=false;
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

    if (atras & alineado)
       retroceder();
    if (!atras & alineado)
       avanzar();

    if (posicionY==bordeSuperior)
       bajar();
    if (posicionY==bordeInferior)
       subir();
}

void EnemigoModelo::patrullar(){
	if(modo==Patrullando){

    if (posicionY==bordeSuperior)
        subiendo=false;
    if (posicionY==bordeInferior)
        subiendo=true;
    if (posicionX==limiteFinal){
        yendoAdelante=false;
        retroceder();
       }
    if (posicionX==limiteInicial){
    	yendoAdelante=true;
        avanzar();
      }
    if (!subiendo){
        if (dadoVuelta)
            retrocederDiagAbajo(bordeInferior);
        else
            avanzarDiagAbajo(bordeInferior);
      }
    else {
        if (dadoVuelta)
            retrocederDiagArriba(bordeSuperior);
        else
            avanzarDiagArriba(bordeSuperior);
      }

    if (esAtacante){
    	tiempoDeGolpe++;
    	if(tiempoDeGolpe==40){
    		cambiarModo(Atacando);
    	    tiempoDeGolpe=0;
    	   }
      }

	}
}

void EnemigoModelo::modificarJugadorObjetivo(int objetivo){
	jugadorObjetivo=objetivo;
}

int EnemigoModelo::consultarJugadorObjetivo(){
	return jugadorObjetivo;
}

void EnemigoModelo::atacar(){
	if (modo==Atacando){
	  esAtacante=true;
	int x,y;
	x=objetivo->darPosicionX();
	y=objetivo->darPosicionY();
/*	if (posicionY==y){
	//  if (tiempoDeGolpe==0)
	     pegar();
//	  tiempoDeGolpe++;
	//  if (tiempoDeGolpe==4)
//		  tiempoDeGolpe==0;
	     pegando = false;
	}*/
	  if (yendoAdelante)
	    trasladarse(x-110,y+20);
	  else
	    trasladarse(x+110,y+20);
	}
}

void EnemigoModelo::esquivar(){
	  if (subiendo){
	     bajar();
	    }
	  else {
	    subir();
	    }
	  if (yendoAdelante)
	    retroceder();
	  else
	    avanzar();

/*
	switch(tiempoDeEsquivada){
	    case 0:{
	    	modoAnterior = modo;
	    	modo = Esquivando;
			if (avanzando)
			  retroceder();
			else
			  avanzar();
			tiempoDeEsquivada++;
			break;
		    }
	    case 1:{
	    	if (avanzando)
	    	  avanzar();
	    	else
	    	  retroceder();
	    	  tiempoDeEsquivada++;
	    	break;
	    	}
	    case 2:{
    	   if (subiendo)
		     bajar();
		   else
		     subir();
    	   tiempoDeEsquivada++;
    	   break;
			}
	    case 3:
	    case 4:
	    case 5:
	    case 7:
	    case 8:{
	       if (subiendo)
	    	 subir();
	       else
	         bajar();
	        tiempoDeEsquivada++;
	       break;
	    	}
	    case 9:{
	    	if (!avanzando)
	    	  avanzar();
	    	else
	    	  retroceder();
	    	tiempoDeEsquivada=0;
	    	modo = modoAnterior;
	    	break;
	       }
	  }*/
}

void EnemigoModelo::cambiarModo(accionDeEnemigo nuevoModo){
	modo = nuevoModo;
}

void EnemigoModelo::asignarObjetivo(JugadorModelo *jugador){
	objetivo=jugador;
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
	if ((estado->estaMuerto()||!vivo) & estado->terminado()){
		desaparecer();
		cambiarModo(Detenido);
		}
}

void EnemigoModelo::estaSubiendo(){
    subiendo=true;
}

void EnemigoModelo::estaBajando(){
    subiendo=false;
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
	energia -= colisionable->obtenerDanio();
	int puntos = colisionable->obtenerPuntosDeGolpe();
	serGolpeado();
	if (energia <= 0) {
		morir();
		puntos += 500;
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
	insercion.modificar(posicionX, posicionY,
			escalar(estado->obtenerAncho()), escalar(estado->obtenerAlto()));
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
	  if (((fondo->darInicioTerreno())) > (posicionX-800)){
	    activado = true;
	    if (esAtacante)
		  cambiarModo(Atacando);
	    else
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
	    	//esquivar();
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
	bool siendoAtacado;
	if (colisionador->colisiona(this, &tipoColision, &siendoAtacado )) {
        if (ejecutarSonidoGolpeTiro) {
            ejecutarSonidoGolpeImpacto = true;
        }
		posicionX = posicionXAnterior;
		posicionY = posicionYAnterior;
        switch(tipoColision){
           case Enemigo1:
           case Enemigo2:
           case Enemigo3:
           case Barril:
           case Caja:
        	   esquivar();
        	   break;
           case Jugador1:
           case Jugador2:
           case Jugador3:{
        	   switch(modo){
        	   case Atacando:{
        		  if (tiempoDeGolpe == 0 & (!siendoAtacado)){
        			 pegar();
        			//esquivar();
        			 cambiarModo(Patrullando);
        		    }
        		   tiempoDeGolpe++;
        		  if (tiempoDeGolpe == 4)
        		    tiempoDeGolpe = 0;
        		  break;
                }
        	   case Patrullando:
        		   esquivar();
        		   break;
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

