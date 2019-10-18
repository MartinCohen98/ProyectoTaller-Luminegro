#include "VistaEnemigo.h"

VistaEnemigo::VistaEnemigo(Renderizador* elRenderizador,
		pugi::xml_document *archiConfig, sprite codigoEnemigo) {
	std::string path;

	switch (codigoEnemigo) {
		case Enemigo1:	path = archiConfig->child("configuracion").child("escenario").
						child("enemigos").child("bred").child("imagen").attribute("url").value();
						break;
		case Enemigo2:	path = archiConfig->child("configuracion").child("escenario").
						child("enemigos").child("dug").child("imagen").attribute("url").value();
						break;
		case Enemigo3:	path = archiConfig->child("configuracion").child("escenario").
						child("enemigos").child("jake").child("imagen").attribute("url").value();
						break;
	}

	Imagen sprite;
	sprite.cargar(path.data(), Imagen::TIPO_PERSONAJE);
	textura.texturizar(renderizador, sprite);
}

VistaEnemigo::~VistaEnemigo() {}

