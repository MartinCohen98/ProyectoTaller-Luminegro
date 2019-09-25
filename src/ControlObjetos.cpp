#include "ControlObjetos.h"

ControlObjetos::ControlObjetos(Renderizador *renderizador,
			pugi::xml_document *archiConfig, int terrenoWidth) {
	desplazamiento = 0;
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
	int i;
	barriles = new Barril*[barrilesCantidad];
	cajas = new Caja*[cajasCantidad];
	cuchillos = new Cuchillo*[cuchillosCantidad];
	tubos = new Tubo*[tubosMetalicosCantidad];

	for(i = 0; i < barrilesCantidad; i++){
		int distrX = i * (terrenoWidth*3/cajasCantidad) + 500;
		int distrY = i * 5 + 400;
	    barriles[i] = new Barril(renderizador, distrX, distrY, archiConfig);
	    barriles[i]->refrescar(renderizador);
	}

	for(i = 0; i < cajasCantidad; i++){
		int distrX = i * (terrenoWidth*3/cajasCantidad) + 500;
		int distrY = i * 5 + 400;
		cajas[i] = new Caja(renderizador, distrX, distrY, archiConfig);
		cajas[i]->refrescar(renderizador);
	}

	for(i=0;i<cuchillosCantidad;i++){
		int distrX = i * (terrenoWidth*3/cuchillosCantidad) + 700;
		int distrY = i * 5 + 500;
		cuchillos[i] = new Cuchillo(renderizador, distrX, distrY, archiConfig);
		cuchillos[i]->refrescar(renderizador);
	}

	for(i=0;i<tubosMetalicosCantidad;i++){
		int distrX = i * (terrenoWidth*3/tubosMetalicosCantidad) + 900;
		int distrY = i * 5 + 500;
		tubos[i] = new Tubo(renderizador, distrX, distrY, archiConfig);
		tubos[i]->refrescar(renderizador);
	}
}

bool ControlObjetos::Actualizar(Renderizador *renderizador, int avance){
 int i;
 if (avance > desplazamiento){
	 desplazamiento = avance;
	 for(i=0;i<barrilesCantidad;i++){
	      barriles[i]->actualizar(renderizador);
	    }
	 for(i=0;i<cajasCantidad;i++){
	 	  cajas[i]->actualizar(renderizador);
	 	}
	 for(i=0;i<cuchillosCantidad;i++){
	 	  cuchillos[i]->actualizar(renderizador);
	    }
	 for(i=0;i<tubosMetalicosCantidad;i++){
	 	  tubos[i]->actualizar(renderizador);
	 	}
	 return true;
    } else {
	 for(i=0;i<barrilesCantidad;i++){
	       barriles[i]->refrescar(renderizador);
	    }
	 for(i=0;i<cajasCantidad;i++){
	 	   cajas[i]->refrescar(renderizador);
	    }
	 for(i=0;i<cuchillosCantidad;i++){
	 	   cuchillos[i]->refrescar(renderizador);
	    }
	 for(i=0;i<tubosMetalicosCantidad;i++){
	 	   tubos[i]->refrescar(renderizador);
	    }
	 return false;
    }
 }


ControlObjetos::~ControlObjetos() {
	if (barriles != NULL)
		delete[] barriles;
	if (cajas != NULL)
		delete[] cajas;
	if (cuchillos != NULL)
		delete[] cuchillos;
	if (tubos != NULL)
		delete[] tubos;

}

