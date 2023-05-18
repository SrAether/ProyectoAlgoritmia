#include "Tarjetas.h"
#include <vector>
#include <string>
#include <iostream>
// para generacion de numeros aleatorios
#include <algorithm>
#include <set>
#include <random>
// Manejar archivos
#include <fstream>
// verificacion de carpeta
#include <sys/stat.h>
// Manejo de excepcione

//para tener diccionarios
#include <map>

// segun sistema operativo



#ifdef _WIN32
    #include <direct.h>
#endif






/******************************************************************************/
/* Nombre de funcion | prototipoDeComentado*/
/* Descripcion | este es el prototipo de como comentar el encabezado de una funcion*/
/* Precondiciones | aqui van las condiciones necesarias para que ocurra dicha funcion*/
/* Parametros | aqui van los parametros que tomaria dicha funcion*/
/* Valores de retorno | aqui van los valores que retorna dicha funcion*/
/* Notas | aqui van notas que se consideren prudentes*/
/******************************************************************************/

/******************************************************************************/
/* arregloDeElementosAleatorios | prototipoDeComentado*/
/* Descripcion | Crea arreglo aleatorio de de tamaño n, con numeros unicos entre 0 y 200,000*/
/* Precondiciones | Que no exista el archivo de texto que se evaluará*/
/* Parametros | Cantidad de elementos (nElementos) */
/* Valores de retorno | Retorna el arreglo*/
/* Notas | */
/******************************************************************************/
std::vector<int> Tarjetas::arregloDeElementosAleatorios(int nElementos)
{
    // crear un objeto random:device con el fin de obtener un número aleatorio de hardware
    std::random_device rd;
    ; // rd == random device
    // Usamos rd como semilla para mt19937 que es un generador de números aleatorios, tiene una capacidad muy amplia de generación antes de caer en repeticiones
    std::mt19937_64 gen(rd());                                     // creamos un objeto de la clase mt19937 de tipo gen
    std::uniform_int_distribution<uint64_t> dis(0, 200000); /// numeros entre 0 y 200 000

    // creamos un vector para almacenar los numeros aleatorios generados, es relevante tener en cuenta que se usa la clase vector por comodidad se podria crear un contenedor propio
    std::vector< int> arr;
    // creamos un conjunto vacio para almacenar los números ya generados y verificar diplicados, es importante tener en cuenta que este conjunto es de tipo set, esta estructura de datos cuenta con la peculiaridad de que todos sus elementos se encuentran ordenados y no permite repeticiones
    std::set< int> nums_generados;

    // comenzamos a generar numeros aleatorios hasta que se hayan generado n numeros unicos (n es nElementos)
    while (arr.size() < nElementos)
    {
        // generamos numeros aleatorios usando el generador de numeros aleatorios y la distribucion uniforme
         long num = dis(gen);
        // ahora toca verificar que el elemento generado no este en el conjunto
        if (nums_generados.find(num) == nums_generados.end()) // esto es un poco engorroso de explicar pero basicamente el metodo find(elemento buscado) retorna un iterador del elemento (recuerda clases de caro) dentro del objeto de tipo set y de no existir el elemento buscado dentro de la estructura set regresa un iterador al final del arreglo, supongo que se basa en una busqueda binaria
        {
            // si el numero no esta dentro del conjunto, agregarlo al vector y al conjunto
            nums_generados.insert(num);
            arr.push_back(num);
        }
    }
    // para este punto ya tenemos el vector del tamaño deseado con elementos seudoaleatorios así que lo retornamos junto con el dato de tipo set

    return arr;
}

/******************************************************************************/
/* Nombre de funcion | verificacion*/
/* Descripcion | Verifica si existe la carpeta donde se guardaran los resultados */
/* Precondiciones | Que no exista la carpeta o el archivo*/
/* Parametros | predeterminado = 1000 tarjetas, la ruta de la carpeta y nombre del archivo de texto*/
/* Valores de retorno | void*/
/* Notas | pipipi*/
/******************************************************************************/
void Tarjetas::verificacion(const int numTar = 1000, const std::string& ruta_carpeta = "./archivos/", const std::string& nombre_archivo = "tarjetas.txt") 
{
    /*
    //numero de tarjetas en archivo tarjetas
    int numTar = 1000;
    //ruta de carpeta donde se guarda el archivo con las tarjetas
    std::string ruta_carpeta{"./archivos/"};
    //nombre del archivo que contiene las tarjetas
    std::string nombre_archivo{"tarjetas.txt"};*/
    if (!existeCarpeta(ruta_carpeta))
    {
        std::cout << "\nNo existe la carpeta " << ruta_carpeta << ", desea crearla? \nS/n:";
        std::string eleccion;
        std::getline(std::cin >> std::ws, eleccion);
        if ((eleccion[0] != 'S') and (eleccion[0] != 's'))
        {
            throw std::runtime_error("23");
        }
        
        #ifdef _WIN32
            int estado = _mkdir(ruta_carpeta.c_str());
        #elif __linux__
            int estado = mkdir(ruta_carpeta.c_str(), 0777);
        #else
            int estado = mkdir(ruta_carpeta.c_str(), 0777);

        #endif
    
        if (!estado)
        {
            std::cout << "La carpeta se creo correctamente";
        }
        else
        {
            throw std::runtime_error("22");
        }
        
    }
    if (!existeArchivo(ruta_carpeta + nombre_archivo))
    {
        std::cout << "\nNo existe el archivo " << nombre_archivo << " desea crearlos?\nS/n: ";
        std::string eleccion;
        std::getline(std::cin >> std::ws, eleccion);
        if (eleccion[0] != 's' and eleccion[0] != 'S')
        {
            throw std::runtime_error("No se puede ejecutar el programa puesto que no existe el archivo " + nombre_archivo);
        }
        std::vector<int> arregloTarjetas{arregloDeElementosAleatorios(numTar)};
        creacionArchivo(ruta_carpeta + nombre_archivo, arregloTarjetas);
    }
    
}


/******************************************************************************/
/* Nombre de funcion | creacionArchivo*/
/* Descripcion | Crea la carpeta y el txt dentro de ella que se evaluará*/
/* Precondiciones | Que la carpeta y el txt no existan*/
/* Parametros | nombre del txt, arreglo ,tamaño del arreglo(booleano) */
/* Valores de retorno | void*/
/* Notas | */
/******************************************************************************/
void Tarjetas::creacionArchivo(std::string nombre, std::vector< int> arr, bool tam = false) // tam sirve para agregar el tamaño del arreglo al comienzo del archivo
{
    std::ofstream archivo(nombre); // creamos un archivo con el nombre que recibimos como parametro
    try
    {
        if (!archivo) // comprobamos si el archivo se creo correctamente
        {
            // si el archivo no se creo
            throw std::runtime_error("\nNo se pudo abrir el archivo.");
        }
        // trajamos con el archivo recien creado
        if (tam)
        {
            archivo << std::to_string(arr.size()) << "\n";
        }
        for (int dato : arr)
        {
            archivo << std::to_string(dato) << "\n"; 
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    archivo.close();
}

/******************************************************************************/
/* Nombre de funcion | existeCarpeta*/
/* Descripcion | Verifica si existe la carpeta donde se guardaran los resultados */
/* Precondiciones | Que no exista la carpeta o el archivo*/
/* Parametros | la ruta de la carpeta */
/* Valores de retorno | true, false*/
/* Notas | */
/******************************************************************************/
bool Tarjetas::existeCarpeta(const std::string &ruta)
{
    #ifdef _WIN32
        struct _stat info;
        if (_stat(ruta.c_str(), &info) != 0) 
        {
            return false;
        }
    #elif __linux__
        struct stat info;
        if (stat(ruta.c_str(), &info) != 0) 
        {
            return false;
        }
    #else
        struct stat info;
        if (stat(ruta.c_str(), &info) != 0) 
        {
            return false;
        }
    #endif
    return (info.st_mode & S_IFDIR) != 0;
}

/******************************************************************************/
/* Nombre de funcion | existeArchivo*/
/* Descripcion | Verifica si existe el archivo que contiene el arreglo */
/* Precondiciones | Que no exista el archivo*/
/* Parametros | nombre del archivo */
/* Valores de retorno | true, false*/
/* Notas | */
/******************************************************************************/
bool Tarjetas::existeArchivo(const std::string& nombre)
{
    bool existe{1};
    std::fstream archivo(nombre, std::ios::in | std::ios::out); // Abrimos el archivo en modo lectura escritura
    try
    {
        if (!archivo) // comprobamos que el archivo se abrio de forma correcta
        {
            throw std::runtime_error("No se pudo abrir el archivo " + nombre); // lanzamos una excepción si no se pudo abrir el archivo
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        existe = 0;
    }
    archivo.close();
    return existe;
}

/******************************************************************************/
/* Nombre de funcion | lectura*/
/* Descripcion | lee el archivo que contiene el arreglo a evaluar */
/* Precondiciones | Que exista el archivo*/
/* Parametros | ruta del archivo */
/* Valores de retorno | devuelve el arreglo de tarjetas*/
/* Notas | */
/******************************************************************************/
std::vector<int> Tarjetas::lectura(const std::string& nombre = "./archivos/tarjetas.txt")
{
    std::fstream archivo(nombre, std::ios::in | std::ios::out); // Abrimos el archivo en modo lectura escritura
    std::vector<int> retorname;
    try
    {
        if (!archivo) // comprobamos que el archivo se abrio de forma correcta
        {
            throw std::runtime_error("No se pudo abrir el archivo " + nombre); // lanzamos una excepción si no se pudo abrir el archivo
        }
        std::string linea{};
        while(std::getline(archivo, linea))
        {
            retorname.push_back(std::stoi(linea));
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    archivo.close();
    return retorname;
}

/******************************************************************************/
/* Nombre de funcion | calcularTarjetas*/
/* Descripcion | Aqui es donde se ejecuta el algoritmo para encontrar la subsecuencia de tarjetas mas larga   */
/* Precondiciones | Se manda a llamar una vez teniendo el arreglo de tarjetas proporcionado*/
/* Parametros | la lista de tarjetas */
/* Valores de retorno | subsecuencia*/
/* Notas | */
/******************************************************************************/
std::vector<int> Tarjetas::calcularTarjetas(std::vector<int> lista)
{
    int n = lista.size(); // tamaño de la lista
    int lis[n]{1}; //Arreglo de longitudes de la subsecuencia más larga

    //calculamos las lis para cada sublista
    //empezando desde un valor delante de j
    for (int i{1}; i < n; i++)
    {
        for (int j{0}; j < i; j++)
        {
            if (lista[i] > lista[j] and lis[i] < lis[j] + 1)
            {
                //lis es el arreglo que guarda las subsecuencias encontradas hasta i  
                lis[i] = lis[j] + 1;
            }
        }
    }
    // Encontramos la lis maxima
    int maximo{0};
    int ubi{0};
    for (int i{0}; i < n; i++)
    {
        if (lis[i] > maximo)
        {
            //
            maximo = lis[i];
            ubi = i;
        }
    }
    std::vector<int> subsecuencia;
    subsecuencia.push_back(lista[ubi]);
    --maximo;
    for (int j{ubi -1}; j > -1; j--)
    {
        if (lis[j] == maximo)
        {
            subsecuencia.push_back(lista[j]);
            --maximo;
        }
    }
    // Invertir el vector
    std::reverse(subsecuencia.begin(), subsecuencia.end());
    return subsecuencia;
}