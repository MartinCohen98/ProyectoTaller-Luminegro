#ifndef PROYECTOTALLER_LUMINEGRO_COLA_H
#define PROYECTOTALLER_LUMINEGRO_COLA_H

#include "pthread.h"
#include <string>

template <typename T>
class Cola
{
public:
    Cola();
    bool estaVacia();
    void encolar(T dato);
    T desencolar();
    ~Cola();
private:
    struct Nodo{
        T dato;
        Nodo *siguienteNodo;
    };

    Nodo *primerNodo;
    Nodo *ultimoNodo;
    int cantidadElementos;
    pthread_mutex_t mutexCola;
};
//NOTA: Para utilizar esto, definir el tipo de dato con el que se quiera manejar en "Cola.cpp" (ver el final del mismo)
//Ejemplo, quiero hacer una cola de doubles, declaro en "Cola.cpp" lo siguiente:
//                                                          template class Cola<double>;
//Esto es por algunas restricciones que tiene usar "template" y cómo separar interfaz de definición


#endif //PROYECTOTALLER_LUMINEGRO_COLA_H
