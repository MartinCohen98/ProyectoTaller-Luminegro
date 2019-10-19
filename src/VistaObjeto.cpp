#include "VistaObjeto.h"

VistaObjeto::VistaObjeto(Renderizador* elRenderizador,
		pugi::xml_document *archiConfig, tipoDeSprite codigoObjeto) {
	std::string path;

	switch (codigoObjeto) {
		case Barril:	path = archiConfig->child("configuracion").child("escenario")
                    	.child("objetos").child("barril").child_value("imagen");
						break;
		case Caja:		path = archiConfig->child("configuracion").child("escenario")
                    	.child("objetos").child("caja").child_value("imagen");
						break;
		case Cuchillo:	path = archiConfig->child("configuracion").child("escenario")
                    	.child("objetos").child("cuchillo").child_value("imagen");
						break;
		case Tubo:		archiConfig->child("configuracion").child("escenario")
                    	.child("objetos").child("tuboMetalico").child_value("imagen");
						break;
	}

	Imagen sprite;
	sprite.cargar(path.data(), Imagen::TIPO_OBJETO);
	textura.texturizar(renderizador, sprite);
}

VistaObjeto::~VistaObjeto() {}

