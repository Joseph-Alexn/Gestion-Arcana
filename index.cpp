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
        clear();
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

bool excesoRunasElementales(Hechizo &hechizo, char &runaElemental, bool &esArcano)
{
    const int max = 3;
    int sum = 0;
    bool flag = false;
    for (int i = 0; i < hechizo.cantidadVertices; i++)
    {
        if (hechizo.obtenerVertice(i).runa != 'F' && hechizo.obtenerVertice(i).runa != 'A' &&
            hechizo.obtenerVertice(i).runa != 'B' && hechizo.obtenerVertice(i).runa != 'D')
        {
            sum++;
            if (!flag)
            {
                runaElemental = hechizo.obtenerVertice(i).runa;
                flag = true;
            }
        }
        if (sum > max)
        {
            return true;
        }
    }
    if (sum == 0)
        esArcano = true;
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

int generarIdArista(int u, int v, int cantidadVertices)
{
    return min(u, v) * cantidadVertices + max(u, v);
}

bool esRunaElemental(char runa)
{
    return (runa == 'I' || runa == 'Q' || runa == 'T' || runa == 'V' || runa == 'L' || runa == 'O');
}

void DFS_CAMINO_PESADO(Hechizo &hechizo, int verticeActual, bool visitados[], bool aristasVisitadas[], float pesoAcumulado, float &pesoMaximo, int caminoActual[], int &longitudCaminoActual, int caminoMaximo[], int &longitudCaminoMaximo, bool runasElementalesVisitadas[])
{
    visitados[verticeActual] = true;
    caminoActual[longitudCaminoActual++] = verticeActual;

    if (esRunaElemental(hechizo.obtenerVertice(verticeActual).runa))
    {
        runasElementalesVisitadas[verticeActual] = true;
    }

    char runaActual = hechizo.obtenerVertice(verticeActual).runa;
    if ((runaActual == 'D' || runaActual == 'F' || esRunaElemental(runaActual)) && longitudCaminoActual > 1)
    {
        if (pesoAcumulado > pesoMaximo)
        {
            pesoMaximo = pesoAcumulado;
            longitudCaminoMaximo = longitudCaminoActual;

            for (int i = 0; i < longitudCaminoActual; i++)
            {
                caminoMaximo[i] = caminoActual[i];
            }
        }

        visitados[verticeActual] = false;
        longitudCaminoActual--;
        return;
    }

    Nodo<Arista> *iterador = hechizo.obtenerVertice(verticeActual).aristas.ptr_primero;
    while (iterador != nullptr)
    {
        int verticeAdy = iterador->valor.vertice_ady;
        float pesoArista = iterador->valor.peso;

        int idArista = generarIdArista(verticeActual, verticeAdy, hechizo.cantidadVertices);

        if (!aristasVisitadas[idArista])
        {
            char runaAdy = hechizo.obtenerVertice(verticeAdy).runa;
            if (runaAdy == 'A' || runaAdy == 'B' || runaAdy == 'D' || runaAdy == 'F' || esRunaElemental(runaAdy))
            {
                if (esRunaElemental(runaAdy) && runasElementalesVisitadas[verticeAdy])
                {
                    iterador = iterador->ptr_siguiente;
                    continue; // Saltar esta arista si la runa elemental ya fue visitada
                }

                aristasVisitadas[idArista] = true; // Marcar la arista como visitada

                if (!visitados[verticeAdy])
                {
                    DFS_CAMINO_PESADO(hechizo, verticeAdy, visitados, aristasVisitadas, pesoAcumulado + pesoArista, pesoMaximo, caminoActual, longitudCaminoActual, caminoMaximo, longitudCaminoMaximo, runasElementalesVisitadas);
                }

                aristasVisitadas[idArista] = false; // Desmarcar la arista al retroceder
            }
        }
        iterador = iterador->ptr_siguiente;
    }

    visitados[verticeActual] = false;
    longitudCaminoActual--;

    if (esRunaElemental(hechizo.obtenerVertice(verticeActual).runa))
    {
        runasElementalesVisitadas[verticeActual] = false;
    }
}

float encontrarCaminoMasPesado(Hechizo &hechizo)
{
    bool *visitados = new bool[hechizo.cantidadVertices];
    bool *aristasVisitadas = new bool[hechizo.cantidadVertices * hechizo.cantidadVertices];
    bool *runasElementalesVisitadas = new bool[hechizo.cantidadVertices];
    int *caminoActual = new int[hechizo.cantidadVertices];
    int *caminoMaximo = new int[hechizo.cantidadVertices];
    int longitudCaminoActual = 0;
    int longitudCaminoMaximo = 0;
    float pesoMaximo = -1;

    for (int i = 0; i < hechizo.cantidadVertices; i++)
    {
        visitados[i] = false;
        runasElementalesVisitadas[i] = false;
    }
    for (int i = 0; i < hechizo.cantidadVertices * hechizo.cantidadVertices; i++)
    {
        aristasVisitadas[i] = false;
    }

    int puntoConfluencia = -1;
    for (int i = 0; i < hechizo.cantidadVertices; i++)
    {
        if (hechizo.obtenerVertice(i).runa == 'A')
        {
            puntoConfluencia = i;
            break;
        }
    }

    if (puntoConfluencia == -1)
    {
        cout << "No se encontró el punto de confluencia (A)." << endl;
        return;
    }

    DFS_CAMINO_PESADO(hechizo, puntoConfluencia, visitados, aristasVisitadas, 0, pesoMaximo, caminoActual, longitudCaminoActual, caminoMaximo, longitudCaminoMaximo, runasElementalesVisitadas);

    if (longitudCaminoMaximo > 0)
    {
        cout << "Camino mas pesado encontrado con peso: " << pesoMaximo << endl;
        cout << "Camino: ";
        for (int i = 0; i < longitudCaminoMaximo; i++)
        {
            cout << caminoMaximo[i] + 1 << " ";
        }
        cout << endl;
    }
    else
    {
        cout << "No se encontró ningún camino válido en el grafo." << endl;
    }

    delete[] visitados;
    delete[] aristasVisitadas;
    delete[] runasElementalesVisitadas;
    delete[] caminoActual;
    delete[] caminoMaximo;
    return pesoMaximo;
}
// Si es ilegal se agrega al arreglo de hechizos ilegales
// En caso contrario, se agrega el de hechizos legales
// Cada arreglo contiene una lista de hechizos en cada vertice
// Cada posicion es un tipo de hechizo
// 0 Arcano - 1 Fuego - 2 Agua - 3 Tierra - 4 Aire - 5 Luz - 6 Oscuridad

int asignarIndice(char runa)
{
    if (runa == '-') // Es arcano
    {
        return 0;
    }
    else if (runa == 'I') // Es de fuego
    {
        return 1;
    }
    else if (runa == 'Q') // Es de agua
    {
        return 2;
    }
    else if (runa == 'T') // Es de tierra
    {
        return 3;
    }
    else if (runa == 'V') // Es de aire
    {
        return 4;
    }
    else if (runa == 'L') // Es de luz
    {
        return 5;
    }
    else // Es de oscuridad
    {
        return 6;
    }
}

void procesarHechizo(Hechizo &hechizo)
{
    cout << "Procesando hechizo de " << hechizo.nombreMago << "..." << endl;

    bool esIlegal = false;
    if (!confluenciaValida(hechizo))
    {
        esIlegal = true;
        cout << "Confluencia invalida" << endl;
    }

    const char* tipoHechizo[] = {"", "Ignatum", "Aquos", "Terraminium", "Ventus", "Lux", "Tenebrae"};
    string nombreHechizo;
    char runaElemental = '-';
    bool esArcano = false;
    if (excesoRunasElementales(hechizo, runaElemental, esArcano))
    {
        esIlegal = true;
        cout << "Exceso de runas elementales" << endl;
    }

    if (!runasCataliticasValidas(hechizo))
    {
        esIlegal = true;
        cout << "Runas cataliticas invalidas" << endl;
    }

    int longitudCiclo = encontrarCicloMasLargo(hechizo, 0);
    cout << "Longitud del ciclo mas largo: " << longitudCiclo << endl;

    if (longitudCiclo % 2 != 0)
    {
        esIlegal = true;
        cout << "Ciclo de longitud impar" << endl;
    }

    float caminoMasPesado = encontrarCaminoMasPesado(hechizo);

    if (esIlegal)
    {
        cout << "El hechizo es ilegal." << endl;
    }
    else
    {
        cout << "El hechizo es legal." << endl;
    }

    nombreHechizo = string(tipoHechizo[asignarIndice(runaElemental)]);
    // TO DO: Agregar al nombre del hechizo el apellido del mago
    nombreHechizo = nombreHechizo + " ";
    if (longitudCiclo < caminoMasPesado)
    {
        nombreHechizo = nombreHechizo + " modicum";
    }
    else if (longitudCiclo >= caminoMasPesado)
    {
        nombreHechizo = nombreHechizo + " maximus";
    }
    // TO DO: Agregar al nombre la palabra Arcante si no se consigue ninguno de estos elementos
    cout << "Hechizo procesado" << endl;
}

void Entrada(const char *nombreArchivo)
{
    Lista<Nodo<string>> hechizosIlegales[7];
    Lista<Nodo<string>> hechizosIlegales[7];

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
}
int main()
{
    Entrada("spellList.in");
    return 0;
}
