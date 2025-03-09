#include <iostream>
#include <fstream>

using namespace std;
template <typename T>
struct Nodo
{
    T valor;
    Nodo<T> *ptr_siguiente;
    Nodo(T valor) : valor(valor), ptr_siguiente(nullptr) {}
};
template <typename T>
class Lista
{
public:
    int longitud;
    Nodo<T> *ptr_primero;
    Nodo<T> *ptr_ultimo;

    Lista()
    {
        this->longitud = 0;
        this->ptr_primero = nullptr;
        this->ptr_ultimo = nullptr;
    };
    ~Lista()
    {
        clear(); // Esto es un poco innecesario
    };
    void insertarFinal(T elemento)
    {
        if (estaVacia())
        {
            Nodo<T> *nuevo = new Nodo<T>(elemento);
            this->ptr_primero = nuevo;
            this->ptr_ultimo = nuevo;
        }
        else
        {
            Nodo<T> *nuevo = new Nodo<T>(elemento);
            this->ptr_ultimo->ptr_siguiente = nuevo;
            this->ptr_ultimo = nuevo;
        }
        this->longitud++;
    };
    void insertarInicio(T elemento)
    {
        if (estaVacia())
        {
            Nodo<T> *nuevo = new Nodo<T>(elemento);
            this->ptr_primero = nuevo;
            this->ptr_ultimo = nuevo;
        }
        else
        {
            Nodo<T> *nuevo = new Nodo<T>(elemento);
            nuevo->ptr_siguiente = this->ptr_primero;
            this->ptr_primero = nuevo;
        }
        this->longitud++;
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

        Nodo<T> *ptr_aux = this->ptr_primero;
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
class Arista
{
public:
    int vertice_ady; // Indice del vertice adyacente
    float peso;
    Arista *ptr_siguiente;

    Arista(int vertice_ady, float peso)
    {
        this->vertice_ady = vertice_ady;
        this->peso = peso;
        this->ptr_siguiente = nullptr;
    };
    ~Arista()
    {
    }
};
class Vertice
{
public:
    char runa;
    Lista<Arista> aristas;
    Vertice() : runa('\0'), aristas(Lista<Arista>()) {};
    Vertice(char runa) : runa(runa), aristas(Lista<Arista>()) {};
    ~Vertice()
    {
    }
};

class Hechizo
{
public:
    string nombreMago;
    string nombreHechizo;
    Vertice *vertices; // Arreglo de vértices
    int cantidadVertices;

    Hechizo(int cantidadVertices)
    {
        this->nombreMago = "";
        this->nombreHechizo = "";
        this->cantidadVertices = cantidadVertices;
        this->vertices = new Vertice[cantidadVertices];
    }
    ~Hechizo()
    {
        delete[] vertices;
    }

    Vertice &obtenerVertice(int indice)
    {
        if (indice < 0 || indice >= cantidadVertices)
        {
            cout << "Indice fuera de rango" << endl;
            return vertices[-1]; // Esto es un error
        }
        else
        {
            return vertices[indice];
        }
    }
};

void magosBajoInvestigacion()
{
    ifstream archivo("underInvestigation.in");
    if (archivo.is_open())
    {
        cout << "magos bajo investigacion: " << endl;
        char nombreMago[100];
        while (archivo.getline(nombreMago, 100))
        {
            cout << nombreMago << endl;
        }
        archivo.close();
    }
    else
    {
        cout << "No se pudo abrir el archivo" << endl;
    }
}

bool confluenciaValida(Hechizo &hechizo)
{
    int sum = 0;
    int punto_confluencia = -1;
    for (int i = 0; i < hechizo.cantidadVertices; i++)
    {
        if (hechizo.obtenerVertice(i).runa == 'A')
        {
            sum++;
            punto_confluencia = i;
        }
        if (sum > 1)
        {
            return false;
        }
    }
    if (punto_confluencia == -1)
    {
        return false;
    }
    Nodo<Arista> *iterador = hechizo.obtenerVertice(punto_confluencia).aristas.ptr_primero;
    while (iterador != nullptr)
    {
        if (hechizo.obtenerVertice(iterador->valor.vertice_ady).runa != 'B')
        {
            return false;
        }
        iterador = iterador->ptr_siguiente;
    }
    return true;
}

bool excesoRunasElementales(Hechizo &hechizo)
{
    const int max = 3;
    int sum = 0;
    for (int i = 0; i < hechizo.cantidadVertices; i++)
    {
        if (hechizo.obtenerVertice(i).runa != 'F' && hechizo.obtenerVertice(i).runa != 'A' &&
            hechizo.obtenerVertice(i).runa != 'B' && hechizo.obtenerVertice(i).runa != 'D')
        {
            sum++;
        }
        if (sum > max)
        {
            return true;
        }
    }
    return false;
}
bool runasCataliticasValidas(Hechizo &hechizo)
{
    for (int i = 0; i < hechizo.cantidadVertices; i++)
    {
        if (hechizo.obtenerVertice(i).runa == 'D')
        {
            Nodo<Arista> *iterador = hechizo.obtenerVertice(i).aristas.ptr_primero;
            while (iterador != nullptr)
            {
                if (hechizo.obtenerVertice(iterador->valor.vertice_ady).runa != 'A' &&
                    hechizo.obtenerVertice(iterador->valor.vertice_ady).runa != 'B' &&
                    hechizo.obtenerVertice(iterador->valor.vertice_ady).runa != 'F')
                {
                    return false;
                }
                iterador = iterador->ptr_siguiente;
            }
        }
    }
    return true;
}
bool cicloValido(Vertice &vertice, const int origen)
{
    // Funcion auxiliar de DFS_CICLO para chequear si un camino dado es un ciclo valido
    Nodo<Arista> *iterador = vertice.aristas.ptr_primero;
    while (iterador != nullptr)
    {
        if (iterador->valor.vertice_ady == origen)
        {
            return true;
        }
        iterador = iterador->ptr_siguiente;
    }
    return false;
}

int DFS_CICLO(Hechizo &hechizo, int vertice, bool visitados[], int longitud, int &longitudMaxima, const int origen)
{
    // Implementación de DFS para contar la longitud de un camino y devolver la máxima
    visitados[vertice] = true;
    Nodo<Arista> *iterador = hechizo.obtenerVertice(vertice).aristas.ptr_primero;
    while (iterador != nullptr)
    {
        int verticeAdy = iterador->valor.vertice_ady;
        if (!visitados[verticeAdy])
        {
            DFS_CICLO(hechizo, verticeAdy, visitados, longitud + 1, longitudMaxima, origen);
        }
        else if (verticeAdy == origen && longitud > 1)
        {
            if (cicloValido(hechizo.obtenerVertice(vertice), origen))
            {
                if (longitud + 1 > longitudMaxima)
                {
                    longitudMaxima = longitud + 1;
                }
            }
        }
        iterador = iterador->ptr_siguiente;
    }
    visitados[vertice] = false;
    return longitudMaxima;
}

int encontrarCicloMasLargo(Hechizo &hechizo, int origen)
{
    bool *visitados = new bool[hechizo.cantidadVertices];
    for (int i = 0; i < hechizo.cantidadVertices; i++)
    {
        visitados[i] = false;
    }
    int longitudMaxima = 0;
    DFS_CICLO(hechizo, origen, visitados, 0, longitudMaxima, origen);
    delete[] visitados;
    return longitudMaxima;
}

void procesarHechizo(Hechizo &hechizo)
{
    cout << "Procesando hechizo de " << hechizo.nombreMago << "..." << endl;
    if (!confluenciaValida(hechizo))
    {
        cout << "Confluencia invalida" << endl;
    }
    if (excesoRunasElementales(hechizo))
    {
        cout << "Exceso de runas elementales" << endl;
    }
    if (!runasCataliticasValidas(hechizo))
    {
        cout << "Runas cataliticas invalidas" << endl;
    }

    int longitudCiclo = encontrarCicloMasLargo(hechizo, 0);
    cout << "Longitud del ciclo mas largo: " << longitudCiclo << endl;

    cout << "Hechizo procesado" << endl;
}

Hechizo Entrada(const char *nombreArchivo)
{
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open())
    {
        cout << "No se pudo abrir el archivo" << endl;
        exit(1);
    }

    int numeroGrafos;
    archivo >> numeroGrafos;

    for (int i = 0; i < numeroGrafos; i++)
    {
        char nombreMago[100];
        archivo.ignore();
        archivo.getline(nombreMago, 100);

        int cantidadVertices;
        archivo >> cantidadVertices;
        Hechizo hechizo(cantidadVertices);
        hechizo.nombreMago = nombreMago;
        hechizo.nombreHechizo = "Hechizo " + to_string(i + 1);

        string runas;
        archivo >> runas;

        for (int j = 0; j < cantidadVertices; j++)
        {
            hechizo.obtenerVertice(j) = Vertice(runas[j]);
        }

        int numeroAristas;
        archivo >> numeroAristas;

        for (int j = 0; j < numeroAristas; j++)
        {
            int vertice1, vertice2;
            float peso;

            cout << "Leyendo arista #" << j + 1 << "..." << endl;
            archivo >> vertice1 >> vertice2 >> peso;

            if (archivo.fail())
            {
                cout << "Error al leer los datos de la arista" << endl;
                exit(1);
            }

            vertice1--;
            vertice2--;

            if (vertice1 >= 0 && vertice1 < cantidadVertices && vertice2 >= 0 && vertice2 < cantidadVertices)
            {
                hechizo.obtenerVertice(vertice1).aristas.insertarFinal(Arista(vertice2, peso));
                hechizo.obtenerVertice(vertice2).aristas.insertarFinal(Arista(vertice1, peso));
            }
            else
            {
                cout << "Índice de arista fuera de rango: " << vertice1 + 1 << ", " << vertice2 + 1 << endl;
            }
        }
        procesarHechizo(hechizo);
    }

    archivo.close();
    magosBajoInvestigacion();

    return Hechizo(0);
}
int main()
{
    // Procesar el archivo de entrada y obtener el hechizo
    Hechizo hechizo = Entrada("spellList.in");

    // Acceder a la lista de aristas de un vértice específico
    int indiceVertice = 0; // Vértice con índice 0
    Vertice &vertice = hechizo.obtenerVertice(indiceVertice);

    cout << "Aristas del vertice " << indiceVertice << " (Runa: " << vertice.runa << "):" << endl;

    // Recorrer la lista de aristas
    Nodo<Arista> *iterador = vertice.aristas.ptr_primero;
    while (iterador != nullptr)
    {
        cout << "Arista hacia el vertice " << iterador->valor.vertice_ady
             << " con peso " << iterador->valor.peso << endl;
        iterador = iterador->ptr_siguiente;
    }

    return 0;
}
