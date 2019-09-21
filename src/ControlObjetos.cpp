/*
 * ControlObjetos.cpp
 *
 *  Created on: 19 sep. 2019
 *      Author: julio
 */

#include "ControlObjetos.h"

ControlObjetos::ControlObjetos(){

}

ControlObjetos::ControlObjetos(Renderizador *renderizador, pugi::xml_document *archiConfig) {
	// TODO Auto-generated constructor stub
	desplazamiento=0;
	cantBarriles=5;
	cantCajas=5;
	cantCuchillos=5;
	cantTubos=5;
	for(int i=0;i<cantBarriles;i++){
		int distrX=i*400+20;
		int distrY=i*5+500;
	    barriles[i] = Barril(renderizador, distrX, distrY, archiConfig);
	}
	for(int i=0;i<cantCajas;i++){
		int distrX=i*400+200;
		int distrY=i*5+500;
		cajas[i] = Caja(renderizador, distrX, distrY, archiConfig);
		}
	for(int i=0;i<cantCuchillos;i++){
		int distrX=i*400+380;
		int distrY=i*5+500;
		cuchillos[i] = Cuchillo(renderizador, distrX, distrY, archiConfig);
		}
	for(int i=0;i<cantTubos;i++){
		int distrX=i*400+560;
		int distrY=i*5+500;
		tubos[i] = Tubo(renderizador, distrX, distrY, archiConfig);
		}

}

bool ControlObjetos::Actualizar(Renderizador *renderizador,int avance){
 int i;
 if (avance>desplazamiento){
	 desplazamiento=avance;
	 for(i=0;i<cantBarriles;i++){
	      barriles[i].actualizar(renderizador);
	    }
	 for(i=0;i<cantCajas;i++){
	 	  cajas[i].actualizar(renderizador);
	 	}
	 for(i=0;i<cantCuchillos;i++){
	 	  cuchillos[i].actualizar(renderizador);
	    }
	 for(i=0;i<cantTubos;i++){
	 	  tubos[i].actualizar(renderizador);
	 	}
	 return true;
    }

 else{
	 for(i=0;i<cantBarriles;i++){
	       barriles[i].refrescar(renderizador);
	    }
	 for(i=0;i<cantCajas;i++){
	 	   cajas[i].refrescar(renderizador);
	    }
	 for(i=0;i<cantCuchillos;i++){
	 	   cuchillos[i].refrescar(renderizador);
	    }
	 for(i=0;i<cantTubos;i++){
	 	   tubos[i].refrescar(renderizador);
	    }
	 return false;
    }
 }


ControlObjetos::~ControlObjetos() {
	// TODO Auto-generated destructor stub
}

