# ProyectoTaller-Luminegro

Para poder correr el proyecto se requiere tener instalado SDL2. 

¿Cómo instalar dichas bibliotecas? Ejecutando la siguiente línea en una terminal:

`sudo apt-get install libsdl2-dev libsdl2-2.0-0 libsdl2-image-dev libsdl2-image-2.0-0 libsdl2-ttf-dev libsdl2-ttf-2.0-0`

En **CLion** (y puede que en otros IDEs) no encuentra la biblioteca de SDL2_ttf. Para solucionar esto, en Ubuntu versión 64 bits (que fue donde se probó), ir al directorio /usr/lib/x86_64-linux-gnu

`cd /usr/lib/x86_64-linux-gnu`

Y una vez aquí, ejecutar:

`sudo cp libSDL2_ttf-2.0.so libSDL_ttf.so`
