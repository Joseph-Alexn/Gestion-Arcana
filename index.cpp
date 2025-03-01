#include <iostream>
#include <fstream>

using namespace std;

// El #ifndef garantiza que este codigo solo se ejectuta cuando no este definido el macro LIST_V4
#ifndef LIST_V4
#define LIST_V4 // Aqui lo definimos, asi que la definicion de la clase solo se va a realizar una sola vez, esto evita redefinicion de cosas y redundancia ciclica

#include "node.h"

// En esta version final el nodo tiene dos apuntadores, uno al siguiente y uno al nodo previo, debido a esto podemos realizar todas las operaciones en O(1)
// Ademas podemos decidir si insertamos antes o despues del nodo seleccionado como iterador
template <typename T>
class ListV4
{
public:
    typedef DoubleLinkNode<T> *iterator;

    // Construye una lista vacia
    ListV4();

    ~ListV4();

    iterator first(); // En este caso esta funcion no puede ser const porque podemos alterar first a travez de ella
    // ya que retorna la direccion de memoria de la variable _first

    iterator last();

    T *get(iterator i) const;

    void next(iterator &i) const;

    void prev(iterator &i) const;

    bool isEmpty() const;

    int size() const;

    void insert(iterator i, T payload, bool before = true);

    void deleteNode(iterator i);

private:
    iterator _first;
    iterator _last;
    int _size;
};

template <typename T>
ListV4<T>::ListV4()
{
    this->_first = nullptr;
    this->_last = nullptr;
}

template <typename T>
ListV4<T>::~ListV4()
{
    while (!this->isEmpty())
    {
        this->deleteNode(this->first());
    }
}

template <typename T>
typename ::ListV4<T>::iterator ListV4<T>::first()
{
    return this->_first;
}

template <typename T>
typename ::ListV4<T>::iterator ListV4<T>::last()
{
    return this->_last;
}

template <typename T>
T *ListV4<T>::get(iterator i) const
{
    if (i == nullptr)
        return nullptr;

    return &i->payload;
}

template <typename T>
void ListV4<T>::next(iterator &i) const
{
    if (i == nullptr)
        return;
    i = i->next;
}

template <typename T>
void ListV4<T>::prev(iterator &i) const
{
    if (i == nullptr)
        return;
    i = i->prev;
}

template <typename T>
bool ListV4<T>::isEmpty() const
{
    return this->_first == nullptr;
}

template <typename T>
int ListV4<T>::size() const
{
    return this->_size;
}

template <typename T>
void ListV4<T>::insert(iterator i, T payload, bool before)
{
    DoubleLinkNode<T> *newNode = new DoubleLinkNode<T>(payload);

    this->_size++;

    if (this->isEmpty())
    {
        this->_first = newNode;
        this->_last = newNode;
        return;
    }

    if (before)
    {
        newNode->next = i;
        newNode->prev = i->prev;
        if (i->prev != nullptr)
            i->prev->next = newNode;

        i->prev = newNode;

        if (this->first() == i)
            this->_first = newNode;

        return;
    }

    newNode->next = i->next;
    newNode->prev = i;
    if (i->next != nullptr)
        i->next->prev = newNode;

    i->next = newNode;

    if (this->last() == i)
        this->_last = newNode;
}

template <typename T>
void ListV4<T>::deleteNode(iterator i)
{
    if (i == nullptr)
        return;

    this->_size--;

    if (i == this->first())
        this->_first = i->next;

    if (i == this->last())
        this->_last = i->prev;

    if (i->prev != nullptr)
        i->prev->next = i->next;

    if (i->next != nullptr)
        i->next->prev = i->prev;

    delete i;
}

#endif // LIST_V4