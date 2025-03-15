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
    void print()
    {
        if (estaVacia())
            return;
        Nodo<T> *ptr_aux = this->ptr_primero;
        while (ptr_aux != nullptr)
        {
            cout << ptr_aux->valor.valor << endl;
            ptr_aux = ptr_aux->ptr_siguiente;
        }
    }
};

class Arista
{
public:
    int vertice_ady;
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
    Vertice *vertices;
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
            return vertices[-1];
        }
        else
        {
            return vertices[indice];
        }
    }
};

class Sospechoso
{
public:
    string nombre;
    int contadorHechizosIlegales;

    Sospechoso(string nombre) : nombre(nombre), contadorHechizosIlegales(0) {}
};

void magosBajoInvestigacion()
{
    ifstream archivo("underInvestigation.in");
    if (archivo.is_open())
    {
        char nombreMago[100];
        archivo.close();
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

bool excesoRunasElementales(Hechizo &hechizo, char &runaElemental, bool &esArcano, bool &tieneCatalitica, bool &tieneEstabilidad)
{
    const int max = 3;
    int sum = 0;
    bool flag = false, flag2 = false, flag3 = false;
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
        if (!flag2)
        {
            if (hechizo.obtenerVertice(i).runa == 'F')
            {
                tieneEstabilidad = true;
                flag2 = true;
            }
        }
        if (!flag3)
        {
            if (hechizo.obtenerVertice(i).runa == 'D')
            {
                tieneCatalitica = true;
                flag3 = true;
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
                    continue;
                }

                aristasVisitadas[idArista] = true;

                if (!visitados[verticeAdy])
                {
                    DFS_CAMINO_PESADO(hechizo, verticeAdy, visitados, aristasVisitadas, pesoAcumulado + pesoArista, pesoMaximo, caminoActual, longitudCaminoActual, caminoMaximo, longitudCaminoMaximo, runasElementalesVisitadas);
                }

                aristasVisitadas[idArista] = false;
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

    DFS_CAMINO_PESADO(hechizo, puntoConfluencia, visitados, aristasVisitadas, 0, pesoMaximo, caminoActual, longitudCaminoActual, caminoMaximo, longitudCaminoMaximo, runasElementalesVisitadas);

    delete[] visitados;
    delete[] aristasVisitadas;
    delete[] runasElementalesVisitadas;
    delete[] caminoActual;
    delete[] caminoMaximo;
    return pesoMaximo;
}

int asignarIndice(char runa)
{
    if (runa == '-')
    {
        return 0;
    }
    else if (runa == 'I')
    {
        return 1;
    }
    else if (runa == 'Q')
    {
        return 2;
    }
    else if (runa == 'T')
    {
        return 3;
    }
    else if (runa == 'V')
    {
        return 4;
    }
    else if (runa == 'L')
    {
        return 5;
    }
    else
    {
        return 6;
    }
}

void modificarApellido(string &apellido)
{
    int pos_espacio = 0;
    string apellido_modificado = "";
    for (int i = 0; i < apellido.size(); i++)
    {
        if (apellido[i] == ' ')
        {
            pos_espacio = i;
            break;
        }
    }
    int j = pos_espacio + 1;
    while (apellido[j] != '\0')
    {
        apellido_modificado.push_back(apellido[j]);
        j++;
    }

    int ultimo = apellido_modificado.length() - 1;
    if (apellido_modificado[ultimo] == 'a' || apellido_modificado[ultimo] == 'e' || apellido_modificado[ultimo] == 'i' || apellido_modificado[ultimo] == 'o' || apellido_modificado[ultimo] == 'u')
    {
        apellido_modificado.pop_back();
        apellido_modificado += "ium";
    }
    else
    {
        apellido_modificado += "um";
    }

    apellido = apellido_modificado;
}

Nodo<Sospechoso> *buscar(Lista<Sospechoso> sospechosos, Sospechoso mago)
{
    Nodo<Sospechoso> *ptr_aux = sospechosos.ptr_primero;
    while (ptr_aux != nullptr)
    {
        if (ptr_aux->valor.nombre == mago.nombre)
        {
            return ptr_aux;
        }
        ptr_aux = ptr_aux->ptr_siguiente;
    }
    return nullptr;
}

void procesarHechizo(Hechizo &hechizo, Lista<Nodo<string>> hechizosIlegales[], Lista<Nodo<string>> hechizosLegales[], Lista<Sospechoso> sospechosos)
{
    bool esIlegal = false;
    if (!confluenciaValida(hechizo))
    {
        esIlegal = true;
    }

    string apellido = hechizo.nombreMago;
    modificarApellido(apellido);

    const char *tipoHechizo[] = {"", "Ignatum ", "Aquos ", "Terraminium ", "Ventus ", "Lux ", "Tenebrae "};
    string nombreHechizo;
    char runaElemental = '-';
    bool esArcano = false;
    bool tieneCatalitica = false, tieneEstabilidad = false;

    if (excesoRunasElementales(hechizo, runaElemental, esArcano, tieneCatalitica, tieneEstabilidad))
    {
        esIlegal = true;
    }

    if (!runasCataliticasValidas(hechizo))
    {
        esIlegal = true;
    }

    int longitudCiclo = encontrarCicloMasLargo(hechizo, 0);

    if (longitudCiclo % 2 != 0)
    {
        esIlegal = true;
    }

    float caminoMasPesado = encontrarCaminoMasPesado(hechizo);

    nombreHechizo = string(tipoHechizo[asignarIndice(runaElemental)]);

    nombreHechizo = nombreHechizo + apellido + " ";
    if (!tieneCatalitica && !tieneEstabilidad && runaElemental == '-')
    {
        nombreHechizo = nombreHechizo + "Arcante";
    }
    else
    {
        if (longitudCiclo < caminoMasPesado)
        {
            nombreHechizo = nombreHechizo + "modicum";
        }
        else if (longitudCiclo >= caminoMasPesado)
        {
            nombreHechizo = nombreHechizo + "maximus";
        }
    }

    hechizo.nombreHechizo = nombreHechizo;
    nombreHechizo = nombreHechizo + "\n" + hechizo.nombreMago;
    if (esIlegal)
    {
        hechizosIlegales[asignarIndice(runaElemental)].insertarFinal(nombreHechizo);
        Sospechoso sospechoso = Sospechoso(hechizo.nombreMago);

        Nodo<Sospechoso> *ptr_sospechoso = buscar(sospechosos, sospechoso);
        if (ptr_sospechoso == nullptr)
        {
            sospechosos.insertarFinal(sospechoso);
            sospechosos.ptr_ultimo->valor.contadorHechizosIlegales++;
        }
        else
        {
            ptr_sospechoso->valor.contadorHechizosIlegales++;
        }
    }
    else
    {
        hechizosLegales[asignarIndice(runaElemental)].insertarFinal(nombreHechizo);
    }
}
void enviarDatos(Lista<Nodo<string>> hechizosIlegales[], Lista<Nodo<string>> hechizosLegales[])
{
    ofstream archivoSalida("processedSpells.out");
    if (!archivoSalida.is_open())
    {
        return;
    }

    archivoSalida << "Hechizos Legales" << endl
                  << endl;
    for (int i = 0; i < 7; i++)
    {
        Nodo<Nodo<string>> *ptr_aux = hechizosLegales[i].ptr_primero;
        while (ptr_aux != nullptr)
        {
            archivoSalida << ptr_aux->valor.valor << endl;
            ptr_aux = ptr_aux->ptr_siguiente;
        }
    }

    archivoSalida << endl
                  << "Hechizos Ilegales" << endl
                  << endl;
    for (int i = 0; i < 7; i++)
    {
        Nodo<Nodo<string>> *ptr_aux = hechizosIlegales[i].ptr_primero;
        while (ptr_aux != nullptr)
        {
            archivoSalida << ptr_aux->valor.valor << endl;
            ptr_aux = ptr_aux->ptr_siguiente;
        }
    }

    archivoSalida.close();
}
void actualizarListaInvestigacion(Lista<Sospechoso> sospechosos)
{
    ifstream archivoEntrada("underInvestigation.in");
    if (!archivoEntrada.is_open())
    {
        return;
    }

    Lista<string> lineasArchivo;
    string linea;
    while (getline(archivoEntrada, linea))
    {
        lineasArchivo.insertarFinal(linea);
    }
    archivoEntrada.close();

    Nodo<Sospechoso> *ptr_sospechoso = sospechosos.ptr_primero;
    while (ptr_sospechoso != nullptr)
    {
        if (ptr_sospechoso->valor.contadorHechizosIlegales > 3)
        {
            bool existe = false;
            Nodo<string> *ptr_linea = lineasArchivo.ptr_primero;
            while (ptr_linea != nullptr)
            {
                if (ptr_linea->valor == ptr_sospechoso->valor.nombre)
                {
                    existe = true;
                    break;
                }
                ptr_linea = ptr_linea->ptr_siguiente;
            }

            if (!existe)
            {
                lineasArchivo.insertarFinal(ptr_sospechoso->valor.nombre);
            }
        }
        ptr_sospechoso = ptr_sospechoso->ptr_siguiente;
    }

    ofstream archivoSalida("underInvestigation.in");
    if (!archivoSalida.is_open())
    {
        return;
    }

    Nodo<string> *ptr_linea = lineasArchivo.ptr_primero;
    while (ptr_linea != nullptr)
    {
        archivoSalida << ptr_linea->valor << endl;
        ptr_linea = ptr_linea->ptr_siguiente;
    }

    archivoSalida.flush();
    archivoSalida.close();
}

void Entrada(const char *nombreArchivo)
{
    Lista<Nodo<string>> hechizosIlegales[7];
    Lista<Nodo<string>> hechizosLegales[7];
    Lista<Sospechoso> sospechosos;

    ifstream archivo(nombreArchivo);

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

            archivo >> vertice1 >> vertice2 >> peso;

            vertice1--;
            vertice2--;

            if (vertice1 >= 0 && vertice1 < cantidadVertices && vertice2 >= 0 && vertice2 < cantidadVertices)
            {
                hechizo.obtenerVertice(vertice1).aristas.insertarFinal(Arista(vertice2, peso));
                hechizo.obtenerVertice(vertice2).aristas.insertarFinal(Arista(vertice1, peso));
            }
        }
        procesarHechizo(hechizo, hechizosIlegales, hechizosLegales, sospechosos);
    }
    archivo.close();

    enviarDatos(hechizosIlegales, hechizosLegales);

    actualizarListaInvestigacion(sospechosos);

    magosBajoInvestigacion();
}
int main()
{
    Entrada("spellList.in");
    return 0;
}
