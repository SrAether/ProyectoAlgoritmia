// se colocan las funciones de tarjetas
/*
 funcion que genere numeros aleatorios
 funcion que tome numeros aleatorios y los coloque dentro de un archivo 
 funcion que lea un archivo con numeros aleatorios

 calcular tarjetas toma como parametro un arreglo de tarjetas
 void calcularTarjetas(std::vector<int> tarjetas)

 
*/
#include <vector>
#include <string>


/******************************************************************************
 Nombre de funcion | prototipoDeComentado
 Descripcion | este es el prototipo de como comentar el encabezado de una funcion
 Precondiciones | aqui van las condiciones necesarias para que ocurra dicha funcion
 Parametros | aqui van los parametros que tomaria dicha funcion
 Valores de retorno | aqui van los valores que retorna dicha funcion
 Notas | aqui van notas que se consideren prudentes
******************************************************************************/

namespace Tarjetas
{
    // VERIFICACION DE EXISTENCIA DE ARCHIVO, Y CREACION

    /**ArregloDeElementosAleatoriosDoc**********************************************
     Nombre de funcion | ArregloDeElementosAleatorios
     Descripcion | 
        Esta funcion se encarga de generar un arreglo de elementos aleatorios entre 1 y 200 000 de tamaño nElemetnos, el arreglo generado se almacena en una estructura de tipo vector de enteros y se retorna dicho vector de enteros
     Precondiciones | 
        Para la llamada de este metodo es necesario que al momento de ejecutarse la funcion verificacion() esta detecte que no existe el archivo tarjetas.txt, de no existir se llama a esta funcion para crear los elementos que guardaremos en dicho archivo
     Parametros | 
        La función toma un parametro entero que indica el tamaño del vector de numeros aleatorios
     Valores de retorno | 
        La funcion retorna un vector de enteros que contiene nElementos de numeros aleatorios
     Notas | se usa la clase std::mt19937_64 para generar los numeros aleatorios
    ******************************************************************************/
    std::vector<int> arregloDeElementosAleatorios(int nElementos); 
    //para la verificacion, lectura y creacion de archivo de tarjetas
    void verificacion(const int numTar = 1000,const std::string& ruta_carpeta = "./archivos/",const std::string& nombre_archivo = "tarjetas.txt"); // verifica la existencia del archivo y carpeta dados, ademas de no existir da al usuario la opcion de crearlos, por defecto el tamaño del archivo es de 1000 tarjetas
    bool existeArchivo(const std::string& nombre); // retorna true de existir un archivo con el nombre dado como parametro
    bool existeCarpeta(const std::string& ruta); // retorna true de existir una carpeta con el nombre dado como parametro
    void creacionArchivo(std::string nombre, std::vector< int> arr, bool tam = false); // recibe como parametro el nombre del archivo y un vector del cual se extraera la información que se colocara en el archivo
    
    // LECTURA DE ARCHIVO
    std::vector<int> lectura(const std::string& nombre = "./archivos/tarjetas.txt");

    // FUNCIONES PARA CALCULAR TARJETAS

    std::vector<int> calcularTarjetas(std::vector<int> tarjetas);
    


}