#include "MensajeServidor.h"

using namespace std;

MensajeServidor::MensajeServidor() {
	sprite = Jugador1;
	dadoVuelta = false;
}

void MensajeServidor::generarMensaje(Encuadre* unFrame,
		Encuadre* unaInsercion, tipoDeSprite tipo) {
	frame = *unFrame;
	insercion = *unaInsercion;
	sprite = tipo;
	dadoVuelta = false;
}


void MensajeServidor::darVuelta() {
	dadoVuelta = true;
}


Encuadre* MensajeServidor::obtenerFrame() {
	return &frame;
}


Encuadre* MensajeServidor::obtenerInsercion() {
	return &insercion;
}


tipoDeSprite MensajeServidor::obtenerTipoDeSprite() {
	return sprite;
}


bool MensajeServidor::estaDadoVuelta() {
	return dadoVuelta;
}


string MensajeServidor::codificarMensaje(void){
	//Genera un string para enviar como datos al cliente

	string encuadre1;
	string encuadre2;
	string dadovuelta;
	string mensaje;
	encuadre1=(to_string(frame.getX()))+"-"+(to_string(frame.getY()))+"-"+(to_string(frame.getAncho()))+"-"+(to_string(frame.getAlto()));
	encuadre2=(to_string(insercion.getX()))+"-"+(to_string(insercion.getY()))+"-"+(to_string(insercion.getAncho()))+"-"+(to_string(insercion.getAlto()));
    if (dadoVuelta)
    	dadovuelta="1";
    else
	    dadovuelta="0";
	mensaje=encuadre1+"-"+encuadre2+"-"+dadovuelta+"-"+to_string(sprite);
	return mensaje;
}

void MensajeServidor::decodificarMensaje(std::string mensaje){

	int cifras[10];
	size_t posicion;
	string dato;
	int i=0;
	int x,y,ancho,alto;

	//Lee las cifras del string separadas por "-"
	while ((posicion=mensaje.find("-")) != string::npos) {
	     dato = mensaje.substr(0,posicion);
		 cifras[i]=stoi(dato);
		 mensaje.erase(0,posicion+1);
		 i++;
		}
	cifras[9]=stoi(mensaje);

	//Actualiza los encuadres de la clase MensajeServidor con los datos recibidos
	x=cifras[0];
	y=cifras[1];
	ancho=cifras[2];
	alto=cifras[3];
	frame.modificar(x,y,ancho,alto);
	x=cifras[4];
	y=cifras[5];
	ancho=cifras[6];
	alto=cifras[7];
	insercion.modificar(x,y,ancho,alto);

	if (cifras[8]==1)
	  dadoVuelta=true;
	else
	  dadoVuelta=false;

	sprite = static_cast<tipoDeSprite>(cifras[9]);
}


bool MensajeServidor::operator <(const MensajeServidor & mensaje) const {
	return ((insercion.getY() + insercion.getAlto()) <
			(mensaje.insercion.getY() +
			mensaje.insercion.getAlto()));
}


MensajeServidor::~MensajeServidor() {}

