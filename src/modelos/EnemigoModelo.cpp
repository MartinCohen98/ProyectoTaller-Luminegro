#include "EnemigoModelo.h"

EnemigoModelo::EnemigoModelo(){}

EnemigoModelo::EnemigoModelo(int posXinicial, int posYinicial, tipoDeSprite tipo,
		FondoModelo* fondo) {
	posicionX = posXinicial;
	posicionY = posYinicial;
	bordeSuperior = 180;
	bordeInferior = 320;
	limiteInicial = 0;
	limiteFinal = fondo->obtenerAncho();
	escaladoDeSprite = 3.6;
	energia = 100;
	tipoEnemigo = tipo;
	estado = new EstadoEnemigoParado(tipoEnemigo);
	dadoVuelta = false;
	subiendo=false;
	tiempoDeGolpe=0;
	tiempoDeEsquivada=0;
	vivo=true;
	actualizarInsercion();
}

void EnemigoModelo::avanzar() {
	if (posicionX < limiteFinal) {
  	  dadoVuelta = false;
	  estado = estado->avanzar();
	  moverEnX(5);
	  avanzando=true;
	}
	else {
	  parar();
	  estado = estado->parar();
	}
	actualizarInsercion();
}

void EnemigoModelo::parar() {
	estado = estado->parar();
    actualizarInsercion();
}

void EnemigoModelo::retroceder() {
	if (posicionX > limiteInicial) {
	  dadoVuelta = true;
	  estado = estado->avanzar();
	  moverEnX(-5);
	  avanzando=false;
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
		moverEnY(-5);
		subiendo=true;
	} else {
	    parar();
		estado = estado->parar();
	}
	actualizarInsercion();
}

void EnemigoModelo::bajar() {
	if (posicionY < bordeInferior) {
		moverEnY(5);
        estado = estado->avanzar();
        subiendo=false;
	} else {
	    parar();
		estado = estado->parar();
	}
	actualizarInsercion();
}

void EnemigoModelo::pegar(){
    estado = estado->pegar();
    actualizarInsercion();
}

void EnemigoModelo::morir(){
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
    avanzando=true;
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
    avanzando=true;
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
    avanzando=false;
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
    avanzando=false;
    subiendo=false;
    actualizarInsercion();
}

void EnemigoModelo::trasladarse(int destinoX,int destinoY) {
    bool atras = false;
    bool abajo = false;
    if (destinoX < posicionX)
        atras = true;
    if (destinoY > posicionY)
        abajo = true;
    if (atras & abajo) {
        retrocederDiagAbajo(destinoY);
        if (posicionY==destinoY)
            retroceder();
    }
    if (atras & !abajo) {
        retrocederDiagArriba(destinoY);
        if (posicionY==destinoY)
            retroceder();
    }
    if (!atras & abajo) {
        avanzarDiagAbajo(destinoY);
        if (posicionY==destinoY)
            avanzar();
    }
    if (!atras & !abajo) {
        avanzarDiagArriba(destinoY);
        if (posicionY==destinoY)
            avanzar();
    }
    if (abajo)
    	bajar();
    if (!abajo)
    	subir();
}

void EnemigoModelo::patrullar(){
	if(modo==Patrullando & vivo){

    if (posicionY==bordeSuperior)
        subiendo=false;
    if (posicionY==bordeInferior)
        subiendo=true;
    if (posicionX==limiteFinal){
        avanzando=false;
        dadoVuelta=true;
       }
    if (posicionX==limiteInicial){
        avanzando=true;
        dadoVuelta=false;
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
   // if (posicionY==250)
     //  pegar();
	}
}

void EnemigoModelo::modificarJugadorObjetivo(int objetivo){
	jugadorObjetivo=objetivo;
}

int EnemigoModelo::consultarJugadorObjetivo(){
	return jugadorObjetivo;
}

void EnemigoModelo::atacar(){
	if (modo==Atacando & vivo){
	int x,y;
	x=objetivo->darPosicionX();
	y=objetivo->darPosicionY();
	//if (posicionY==y){
	//  if (tiempoDeGolpe==0)
	//     pegar();
//	  tiempoDeGolpe++;
	//  if (tiempoDeGolpe==4)
//		  tiempoDeGolpe==0;
//	}
	if (avanzando)
	  trasladarse(x-110,y+20);
	else
	  trasladarse(x+110,y+20);
	}
}

void EnemigoModelo::esquivar(){
/*	if (avanzando){
		retroceder();
	}
	else {
		avanzar();
	}*/

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
	  }
}

void EnemigoModelo::cambiarModo(accionDeEnemigo nuevoModo){
	modo = nuevoModo;
}

void EnemigoModelo::asignarObjetivo(JugadorModelo *jugador){
	objetivo=jugador;
}

bool EnemigoModelo::estaVivo(){
	return vivo;
}

void EnemigoModelo::estaSubiendo(){
    subiendo=true;
}

void EnemigoModelo::estaBajando(){
    subiendo=false;
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


void EnemigoModelo::generarMensaje(MensajeServidor* mensajes, int* mensajeActual) {
	Encuadre sprite = estado->obtenerSprite();
	mensajes[*mensajeActual].generarMensaje(&sprite, &insercion, tipoEnemigo);
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
	switch (modo){
	    case Detenido:{
	    	parar();
	    	break;
	      }
	    case Patrullando:{
	   // 	patrullar();
	    	break;
	      }
	    case Esquivando:{
	    	esquivar();
	    	break;
	      }
	    case Atacando:{
	    //	atacar();
	    	break;
	      }
	}
	if (estado->estaMuerto() & estado->terminado())
		desaparecer();
	checkearColisiones(colisionador);
}


void EnemigoModelo::checkearColisiones(Colisionador* colisionador) {
	actualizarInsercion();
	if (colisionador->colisiona(this)) {
		posicionX = posicionXAnterior;
		posicionY = posicionYAnterior;
		if(modo!=Atacando){
		  if (subiendo){
		     bajar();
		    }
		  else {
		    subir();
		    }
		  if (avanzando)
		    retroceder();
		  else
		    avanzar();
		}
		actualizarInsercion();
	}
}

void EnemigoModelo::desaparecer() {
	alto = 0;
	ancho = 0;
	cambiarModo(Detenido);
	posicionY=10000;
}

int EnemigoModelo::escalar(int tamanio) {
	return (tamanio * escaladoDeSprite);
}


EnemigoModelo::~EnemigoModelo() {}

