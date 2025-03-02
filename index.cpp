#include <iostream>
#include <fstream>

using namespace std;

template <typename T>
class Lista
{
private:
    int longitud;
    T *ptr_primero;
    T *ptr_ultimo;
public:
    Lista()
    {
        this->longitud = 0;
        this->ptr_primero = nullptr;
        this->ptr_ultimo = nullptr;
    };
    ~Lista()
    {
        clear(); //Esto es un poco innecesario
    };
    void insertarFinal(T elemento)
    {
        if (estaVacia())
        {
            T *nuevo = new T(elemento);
            this->ptr_primero = nuevo;
            this->ptr_ultimo = nuevo;
            return;
        }
        T *aux = new T(elemento);
        this->ptr_ultimo = aux;
        this->longitud++;
        return;
    };
    void insertarInicio(T elemento)
    {
        if (estaVacia())
        {
            T *nuevo = new T(elemento);
            this->ptr_primero = nuevo;
            this->ptr_ultimo = nuevo;
            return;
        }
        T *nuevo = new T(elemento);
        T *aux = this->ptr_primero;
        nuevo->ptr_siguiente = aux;
        this->ptr_primero = nuevo;
        this->longitud++;
        return;
    };
    bool estaVacia()
    {
        return this->ptr_primero == nullptr;
    }
    void pop()
    {
        if (estaVacia())
        {
            return;
        }
    
        T *ptr_aux = this->ptr_primero;
        this->ptr_primero = this->ptr_primero->ptr_siguiente;
        delete ptr_aux;
        this->longitud--;
        return;
    }
    void clear()
    {
        while (!estaVacia())
        {
            pop();
        }
    }
};
class Vertice
{
public:
    char runa;
    Lista<Arista> aristas;
    Vertice(char runa)
    {
        this->runa = runa;
        this->aristas = Lista<Arista>();
    };
    ~Vertice()
    {

    };
};

class Arista
{
private:
    int vertice_ady;
    float peso;
    Arista* ptr_siguiente;
public:
    Arista(int vertice_ady, float peso)
    {
        this->vertice_ady = vertice_ady;
        this->peso = peso;
        this->ptr_siguiente = nullptr;
    };
    ~Arista()
    {

    };
};

class Hechizo
{
public:
    string nombreMago;
    string nombreHechizo;
    Vertice vertices[];
};


