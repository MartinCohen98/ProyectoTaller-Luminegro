#include "ControlObjetos.h"

ControlObjetos::ControlObjetos(Renderizador *renderizador,
			pugi::xml_document *archiConfig, int terrenoWidth, int nivel) {

    std::string nivelNodeName = "nivel";
    nivelNodeName.append( std::to_string(nivel) );

	std::string barrilesCantidadString = archiConfig->child("configuracion").child("escenario")
            .child("niveles").child( nivelNodeName.data() ).child("barril").child_value("cantidad");

    std::string cajasCantidadString = archiConfig->child("configuracion").child("escenario")
            .child("niveles").child( nivelNodeName.data() ).child("caja").child_value("cantidad");

    std::string cuchillosCantidadString = archiConfig->child("configuracion").child("escenario")
            .child("niveles").child( nivelNodeName.data() ).child("cuchillo").child_value("cantidad");

    std::string tubosMetalicosCantidadString = archiConfig->child("configuracion").child("escenario")
            .child("niveles").child( nivelNodeName.data() ).child("tuboMetalico").child_value("cantidad");

    barrilesCantidad = std::stoi(barrilesCantidadString);
    cajasCantidad = std::stoi(cajasCantidadString);
    cuchillosCantidad = std::stoi(cuchillosCantidadString);
    tubosMetalicosCantidad = std::stoi(tubosMetalicosCantidadString);

	int i;

	barriles = new BarrilModelo*[barrilesCantidad];
	cajas = new CajaModelo*[cajasCantidad];
	cuchillos = new CuchilloModelo*[cuchillosCantidad];
	tubos = new TuboModelo*[tubosMetalicosCantidad];

	srand (time(NULL));

	for(i = 0; i < barrilesCantidad; i++) {
		int distrX = rand() % (terrenoWidth * 3) - 90;
		int distrY = i * 1 + 450;
	    barriles[i] = new BarrilModelo(/*renderizador, */distrX, distrY/*, archiConfig*/);
	    //barriles[i]->actualizar(renderizador);
	}

	for(i = 0; i < cajasCantidad; i++) {
		int distrX = rand() % (terrenoWidth * 3) - 96;
		int distrY = i * 5 + 420;
		cajas[i] = new CajaModelo(/*renderizador, */distrX, distrY/*, archiConfig*/);
		//cajas[i]->actualizar(renderizador);
	}

	for(i = 0; i < cuchillosCantidad; i++) {
		int distrX = rand() % (terrenoWidth * 3) - 66;
		int distrY = i * 5 + 500;
		cuchillos[i] = new CuchilloModelo(/*renderizador, */distrX, distrY/*, archiConfig*/);
	//	cuchillos[i]->actualizar(renderizador);
	}

	for(i = 0; i < tubosMetalicosCantidad; i++) {
		int distrX = rand() % (terrenoWidth * 3) - 144;
		int distrY = i * 5 + 500;
		tubos[i] = new TuboModelo(/*renderizador, */distrX, distrY/*, archiConfig*/);
		//tubos[i]->actualizar(renderizador);
	}
}

void ControlObjetos::movidaDePantalla() {
	for(int i = 0; i < barrilesCantidad; i++){
		barriles[i]->movidaDePantalla();
	}

	for(int i = 0; i < cajasCantidad; i++){
		cajas[i]->movidaDePantalla();
	}

	for(int i = 0; i < cuchillosCantidad; i++){
		cuchillos[i]->movidaDePantalla();
	}

	for(int i = 0; i < tubosMetalicosCantidad; i++){
		tubos[i]->movidaDePantalla();
	}
}

void ControlObjetos::actualizar(Renderizador *renderizador) {
	for(int i = 0; i < cuchillosCantidad; i++){
		//cuchillos[i]->actualizar(renderizador);
	}
	for(int i = 0; i < tubosMetalicosCantidad; i++){
		//tubos[i]->actualizar(renderizador);
	}
}

void ControlObjetos::actualizarFrente(Renderizador* renderizador) {
	for(int i = 0; i < barrilesCantidad; i++){
		//barriles[i]->actualizar(renderizador);
	}

	for(int i = 0; i < cajasCantidad; i++){
	//	cajas[i]->actualizar(renderizador);
	}
}


ControlObjetos::~ControlObjetos() {
	if (barriles != NULL) {
		for(int i = 0; i < barrilesCantidad; i++)
			delete barriles[i];
		delete[] barriles;
	}

	if (cajas != NULL) {
		for(int i = 0; i < cajasCantidad; i++)
			delete cajas[i];
		delete[] cajas;
	}

	if (cuchillos != NULL) {
		for(int i = 0; i < cuchillosCantidad; i++)
			delete cuchillos[i];
		delete[] cuchillos;
	}

	if (tubos != NULL) {
		for(int i = 0; i < tubosMetalicosCantidad; i++)
			delete tubos[i];
		delete[] tubos;
	}
}

