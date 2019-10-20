#include "Cola.h"


template <typename T>
Cola<T>::Cola() {
    this->ultimoNodo = nullptr;
    this->primerNodo = nullptr;
    this->cantidadElementos = 0;
    pthread_mutex_init(&this->mutexCola, NULL);
}

template<typename T>
bool Cola<T>::estaVacia() {
    return this->cantidadElementos == 0;
}

template<typename T>
void Cola<T>::encolar(T dato) {
    Nodo *nodo = new Nodo();
    nodo->dato = dato;
    nodo->siguienteNodo = nullptr;
    //Bloqueo modificaciones
    pthread_mutex_lock(&this->mutexCola);

    if(!this->primerNodo){
        this->primerNodo = nodo;
    }else{
        this->ultimoNodo->siguienteNodo = nodo;
    }
    this->ultimoNodo = nodo;
    this->cantidadElementos++;
    //Libero
    pthread_mutex_unlock(&this->mutexCola);
}

template<typename T>
T Cola<T>::desencolar() {
	//Bloqueo modificaciones
    pthread_mutex_lock(&this->mutexCola);

    if(!this->cantidadElementos){
    	pthread_mutex_unlock(&this->mutexCola);
     //   return nullptr;
    }
    Nodo *nodo = this->primerNodo;
    T elemento = nodo->dato;
    this->primerNodo = nodo->siguienteNodo;
    delete nodo;
    this->cantidadElementos--;
    //Libero
    pthread_mutex_unlock(&this->mutexCola);

    return elemento;
}

template <typename T>
Cola<T>::~Cola() {
    Nodo *nodoTemp;
    while(primerNodo != nullptr){
        nodoTemp = primerNodo;
        primerNodo = nodoTemp->siguienteNodo;
        delete nodoTemp;
    }
    cantidadElementos = 0;
    ultimoNodo = nullptr;
}


// Definir acá para qué tipo de datos aplica esta Cola
template class Cola<std::string>;
template class Cola<int>;
