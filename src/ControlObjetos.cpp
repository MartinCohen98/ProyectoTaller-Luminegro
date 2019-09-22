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

    std::string barrilesCantidadString = archiConfig->child("configuracion").child("escenario")
            .child("niveles").child("nivel1").child("barril").child_value("cantidad");

    std::string cajasCantidadString = archiConfig->child("configuracion").child("escenario")
            .child("niveles").child("nivel1").child("caja").child_value("cantidad");

    std::string cuchillosCantidadString = archiConfig->child("configuracion").child("escenario")
            .child("niveles").child("nivel1").child("cuchillo").child_value("cantidad");

    std::string tubosMetalicosCantidadString = archiConfig->child("configuracion").child("escenario")
            .child("niveles").child("nivel1").child("tuboMetalico").child_value("cantidad");

    barrilesCantidad = std::stoi(barrilesCantidadString);
    cajasCantidad = std::stoi(cajasCantidadString);
    cuchillosCantidad = std::stoi(cuchillosCantidadString);
    tubosMetalicosCantidad = std::stoi(tubosMetalicosCantidadString);

	for(int i=0;i<barrilesCantidad;i++){
		int distrX=i*400+20;
		int distrY=i*5+500;
	    barriles[i] = Barril(renderizador, distrX, distrY, archiConfig);
	}
	for(int i=0;i<cajasCantidad;i++){
		int distrX=i*400+200;
		int distrY=i*5+500;
		cajas[i] = Caja(renderizador, distrX, distrY, archiConfig);
		}
	for(int i=0;i<cuchillosCantidad;i++){
		int distrX=i*400+380;
		int distrY=i*5+500;
		cuchillos[i] = Cuchillo(renderizador, distrX, distrY, archiConfig);
		}
	for(int i=0;i<tubosMetalicosCantidad;i++){
		int distrX=i*400+560;
		int distrY=i*5+500;
		tubos[i] = Tubo(renderizador, distrX, distrY, archiConfig);
		}

}

bool ControlObjetos::Actualizar(Renderizador *renderizador,int avance){
 int i;
 if (avance>desplazamiento){
	 desplazamiento=avance;
	 for(i=0;i<barrilesCantidad;i++){
	      barriles[i].actualizar(renderizador);
	    }
	 for(i=0;i<cajasCantidad;i++){
	 	  cajas[i].actualizar(renderizador);
	 	}
	 for(i=0;i<cuchillosCantidad;i++){
	 	  cuchillos[i].actualizar(renderizador);
	    }
	 for(i=0;i<tubosMetalicosCantidad;i++){
	 	  tubos[i].actualizar(renderizador);
	 	}
	 return true;
    }

 else{
	 for(i=0;i<barrilesCantidad;i++){
	       barriles[i].refrescar(renderizador);
	    }
	 for(i=0;i<cajasCantidad;i++){
	 	   cajas[i].refrescar(renderizador);
	    }
	 for(i=0;i<cuchillosCantidad;i++){
	 	   cuchillos[i].refrescar(renderizador);
	    }
	 for(i=0;i<tubosMetalicosCantidad;i++){
	 	   tubos[i].refrescar(renderizador);
	    }
	 return false;
    }
 }


ControlObjetos::~ControlObjetos() {
	// TODO Auto-generated destructor stub
}

