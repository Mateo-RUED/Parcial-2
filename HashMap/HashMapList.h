#ifndef U05_HASH_HASHMAP_HASHMAPLIST_H_
#define U05_HASH_HASHMAP_HASHMAPLIST_H_

#include "HashEntry.h"
#include "Lista.h"

using namespace std;

//Tabla hash con manejo de colisiones usando listas enlazadas
template <class K, class T>
class HashMapList {
private:
    Lista<HashEntry<K, T>> **tabla;

    unsigned int tamanio;

    static unsigned int hashFunc(K clave);

    unsigned int (*hashFuncP)(K clave);

public:
    explicit HashMapList(unsigned int k);

    HashMapList(unsigned int k, unsigned int (*hashFuncP)(K clave));

    void getList(K clave);

    void put(K clave, T valor);

    void remove(K clave);

    ~HashMapList();

    Lista<T> getLista(K clave);

    bool esVacio();

    void print();
};

template <class K, class T>
HashMapList<K, T>::HashMapList(unsigned int k) {
    tamanio = k;
    tabla = new Lista<HashEntry<K, T>> *[tamanio];
    for(int i = 0; i < tamanio; i++) {
        tabla[i] = NULL;
    }
    hashFuncP = hashFunc;
}

template <class K, class T>
HashMapList<K, T>::HashMapList(unsigned int k, unsigned int (*fp)(K)) {
    tamanio = k;
    tabla = new Lista<HashEntry<K, T>> *[tamanio];
    for(int i = 0; i < tamanio; i++) {
        tabla[i] = NULL;
    }
    hashFuncP = fp;
}

template <class K, class T>
HashMapList<K, T>::~HashMapList() {
    for(int i = 0; i < tamanio; i++) {
        if(tabla[i] != NULL) {
            delete tabla[i];
        }
    }
}

template <class K, class T>
void HashMapList<K, T>::put(K clave, T valor) {
    unsigned int pos = hashFuncP(clave) % tamanio;

    if(tabla[pos] == NULL) {
        tabla[pos] = new Lista<HashEntry<K, T>>();
    }

    tabla[pos]->insertarUltimo(HashEntry<K, T>(clave, valor));
}

template <class K, class T>
void HashMapList<K, T>::remove(K clave) {
    unsigned int pos = hashFuncP(clave) % tamanio;

    if(tabla[pos] == NULL) {
        throw 404;
    }

    T dato = get(clave);

    tabla[pos]->remove({clave, dato});

    if(tabla[pos]->esVacio()) {
        delete tabla[pos];
        tabla[pos] = NULL;
    }
}

template <class K, class T>
bool HashMapList<K, T>::esVacio() {
    for(int i = 0; i < tamanio; i++) {
        if(tabla[i] != NULL) {
            return false;
        }
    }
    return true;
}

template <class K, class T>
unsigned int HashMapList<K, T>::hashFunc(K clave) {
    return (unsigned int) clave;
}

template <class K, class T>
void HashMapList<K, T>::getList(K clave) { //Método que devuelve la lista según la clave que recibe
    unsigned int pos = hashFuncP(clave) % tamanio;

    if(tabla[pos] == NULL) {
        throw 404;
    }

    Nodo<HashEntry<K, T>> *aux = tabla[pos]->getInicio();

    while (aux != NULL) {

        cout << aux->getDato().getValor() << endl;
        aux = aux->getSiguiente();
    }
}

template <class K, class T>
Lista<T> HashMapList<K, T>::getLista(K clave) {
    unsigned int pos = hashFuncP(clave) % tamanio;

    if (tabla[pos] == NULL) {
        throw 404; // Si no hay una lista en esa posición, lanza una excepción
    }

    Lista<T> listaProductos;

    Nodo<HashEntry<K, T>>* aux = tabla[pos]->getInicio();
    while (aux != nullptr) {
        listaProductos.insertarUltimo(aux->getDato().getValor());
        aux = aux->getSiguiente();
    }

    return listaProductos;
}

#endif // U05_HASH_HASHMAP_HASHMAPLIST_H_