#include "MensajeServidor.h"

using namespace std;

MensajeServidor::MensajeServidor() {
	frame = NULL;
	insercion = NULL;
	tipoDeSprite = Jugador1;
	dadoVuelta = false;
}

void MensajeServidor::generarMensaje(Encuadre* unFrame,
		Encuadre* unaInsercion, sprite tipo) {
	frame = unFrame;
	insercion = unaInsercion;
	tipoDeSprite = tipo;
	dadoVuelta = false;
}

void MensajeServidor::darVuelta() {
	dadoVuelta = true;
}

string MensajeServidor::codificarMensaje(void){
	//Genera un string para enviar como datos al cliente

	string encuadre1;
	string encuadre2;
	string dadovuelta;
	string mensaje;
	encuadre1=(to_string(frame->getX()))+"-"+(to_string(frame->getY()))+"-"+(to_string(frame->getAncho()))+"-"+(to_string(frame->getAlto()));
	encuadre2=(to_string(insercion->getX()))+"-"+(to_string(insercion->getY()))+"-"+(to_string(insercion->getAncho()))+"-"+(to_string(insercion->getAlto()));
    if (dadoVuelta)
    	dadovuelta="1";
    else
	    dadovuelta="0";
	mensaje=encuadre1+"-"+encuadre2+"-"+dadovuelta+"-"+to_string(tipoDeSprite);
	return mensaje;
}

void MensajeServidor::decodificar(std::string mensaje){

	int cifras[10];
	size_t orden;
	string dato;
	int i=0;
	int x,y,ancho,alto;

	//Lee las cifras del string separadas por "-"
	while ((orden=mensaje.find("-")) != string::npos) {
		dato = mensaje.substr(0,orden);
		cifras[i]=stoi(dato);
	}
   //Actualiza los encuadres de la clase MensajeServidor con los datos recibidos
	x=cifras[0];
	y=cifras[1];
	ancho=cifras[2];
	alto=cifras[3];
	frame->modificar(x,y,ancho,alto);
	x=cifras[4];
	y=cifras[5];
	ancho=cifras[6];
	alto=cifras[7];
	insercion->modificar(x,y,ancho,alto);

	if (cifras[8]==1)
		dadoVuelta=true;
	else
		dadoVuelta=false;

	tipoDeSprite=static_cast<sprite>(cifras[9]);
}

MensajeServidor::~MensajeServidor() {}

