#ifndef U02_LISTAS_LISTA_LISTA_H_
#define U02_LISTAS_LISTA_LISTA_H_

#include <iostream>
#include "Nodo.h"

/**
 * Clase que implementa una Lista Enlazada genérica, ya que puede
 * almacenar cualquier tipo de dato T
 * @tparam T cualquier tipo de dato
 */
template <class T>
class Lista {
    private:
        Nodo<T> *inicio;


    public:
        Lista();

        Lista(const Lista<T> &li);

        bool esVacia();

        int getTamanio();

        void insertar(int pos, T dato);

        void insertarPrimero(T dato);

        void insertarUltimo(T dato);

        void remover(int pos);

        T getDato(int pos);

        void reemplazar(int pos, T dato);

        Nodo<T> *getInicio();
};

/**
 * Constructor de la clase Lista
 * @tparam T
 */
template <class T>
Lista<T>::Lista() {
    inicio = nullptr;
}

/**
 * Constructor por copia de la clase Lista
 * @tparam T
 * @param li
 */
template <class T>
Lista<T>::Lista(const Lista<T> &li) {
    inicio = li.inicio;
}


/**
 * Método para saber si la lista esta vacía
 * @tparam T
 * @return true si la lista esta vacía, sino false
 */
template <class T>
bool Lista<T>::esVacia() {
    return inicio == nullptr;
}

/**
 * Método para obtener la cantidad de nodos de la lista
 * @tparam T
 * @return la cantidad de nodos de la lista
 */
template <class T>
int Lista<T>::getTamanio() {
    Nodo<T> *aux = inicio;
    int tam = 0;

    while(aux != nullptr) {
        aux = aux->getSiguiente();
        tam++;
    }

    return tam;
}

/**
 * Inserta un nodo con el dato en la posición pos
 * @tparam T
 * @param pos lugar donde será insertado el dato
 * @param dato dato a insertar
 */
template <class T>
void Lista<T>::insertar(int pos, T dato) {
    Nodo<T> *aux = inicio;
    int posActual = 0;

    Nodo<T> *nuevo = new Nodo<T>(dato, inicio);
    nuevo->setDato(dato);

    if(pos == 0) {
        nuevo->setSiguiente(inicio);
        inicio = nuevo;
        return;
    }

    while(aux != nullptr && posActual < pos - 1) {
        aux = aux->getSiguiente();
        posActual++;
    }

    if(aux == nullptr) {
        throw 400;
    }

    nuevo->setSiguiente(aux->getSiguiente());
    aux->setSiguiente(nuevo);
}

/**
 * Inserta un nodo con el dato en la primera posición
 * @tparam T
 * @param dato dato a insertar
 */
template <class T>
void Lista<T>::insertarPrimero(T dato) {
    insertar(0, dato);
}

/**
 * Inserta un nodo con el dato en la última posición
 * @tparam T
 * @param dato dato a insertar
 */
template <class T>
void Lista<T>::insertarUltimo(T dato) {
    Nodo<T> *aux = inicio;

    Nodo<T> *nuevo = new Nodo<T>(dato, inicio);
    nuevo->setDato(dato);

    if(aux == nullptr) {
        nuevo->setSiguiente(inicio);
        inicio = nuevo;
        return;
    }

    while(aux->getSiguiente() != nullptr) {
        aux = aux->getSiguiente();
    }

    nuevo->setSiguiente(aux->getSiguiente());
    aux->setSiguiente(nuevo);
}

/**
 * Elimina el nodo en la posición 'pos' de la lista enlazada
 * @tparam T
 * @param pos posición del nodo a eliminar
 */
template <class T>
void Lista<T>::remover(int pos) {
    Nodo<T> *aux = inicio, *aBorrar;
    int posActual = 0;

    if(pos == 0) {
        inicio = inicio->getSiguiente();
        delete aux;
        return;
    }

    while(aux != nullptr && posActual < pos - 1) {
        aux = aux->getSiguiente();
        posActual++;
    }

    if(aux == nullptr) {
        throw 400;
    }

    aBorrar = aux->getSiguiente();
    aux->setSiguiente(aBorrar->getSiguiente());

    delete aBorrar;
}

/**
 * Obtener el dato del nodo en la posición pos
 * @tparam T
 * @param pos posición del dato
 * @return dato almacenado en el nodo
 */
template <class T>
T Lista<T>::getDato(int pos) {
    Nodo<T> *aux = inicio;
    int posActual = 0;

    while(aux != nullptr && posActual < pos) {
        aux = aux->getSiguiente();
        posActual++;
    }

    if(aux == nullptr) {
        throw 400;
    }

    return aux->getDato();
}

/**
 * Reemplaza el dato almacenado en un nodo por este otro
 * @tparam T
 * @param pos posición donde se desea reemplazar
 * @param dato nuevo dato a almacenar
 */
template <class T>
void Lista<T>::reemplazar(int pos, T dato) {
    Nodo<T> *aux = inicio;
    int posActual = 0;

    while(aux != nullptr && posActual < pos) {
        aux = aux->getSiguiente();
        posActual++;
    }

    if(aux == nullptr) {
        throw 400;
    }

    aux->setDato(dato);
}


/**
 * Método que inserta un nodo con el valor newValue después de la enésima
 * ocurrencia de oldValue
 * @tparam T
 * @param oldValue valor dentro de la lista
 * @param n número de repeticiones de oldValue
 * @param newValue nuevo valor a insertar
 */

template <class T>
Nodo<T> *Lista<T>::getInicio() {
    return inicio;
}

#endif // U02_LISTAS_LISTA_LISTA_H_