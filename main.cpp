#include <iostream>
#include "Tarjetas.h"
#include <vector>
#include "escuadras.hpp"
#include <cmath>
// para ejecutar comandos del sistema
#include <cstdlib>
// para detener el tiempo
#include <chrono>  // Necesario para std::chrono::seconds
#include <thread>  // Necesario para std::this_thread::sleep_for
#include <cstdlib>
#include <string>

// segun sistema operativo

#ifdef _WIN32
    #include <locale>
    #include <windows.h>
    const std::string CLEAR = "cls";
    
#elif __linux__
    #include <locale.h>
    const std::string CLEAR = "clear";
#else
    const std::string CLEAR = "clear";
#endif





void escuadrasUI();
void tarjetasUI();
void crearTarjetasUI();
/******************************************************************************
 Nombre de funcion | runCMatrix
 Descripcion | Esta funcion sirve para ejecutar cmatrix
 Precondiciones | debe estarse ejecutando en un sistema operativo basado en UNIX
 Parametros | NA
 Valores de retorno | void
 Notas | Esta funcion se activa solo con sistemas basados en UNIX
******************************************************************************/
void runCMatrix() {
    system("cmatrix");
}
/******************************************************************************
 Nombre de funcion | main
 Descripcion | Esta es la funcion principal, dentro de esta se ejecuta la secuencia principal
 Precondiciones | ninguna, como tal la funcion principal ya cuenta con todo lo necesario para la ejecucion del programa, en todo caso si se cuenta con un archivo de tarjetas en una ruta externa es necesario contar con la ruta exacta de dicho archivo
 Parametros | NA
 Valores de retorno | valores enteros, regularmente 0 en caso de un error -1
 Notas | La funcion principal cuenta con código que se activa segun las macros del sistema operativo, esto con el afan de que se pueda ejecutar en distintas plataformas
******************************************************************************/
int main()
{
    
    try // en caso de que no se cumplan los requisitos del programa lo detiene y arroja un mensaje de error
    {
        // Configurar el idioma a español
        #ifdef __linux__
        setlocale(LC_CTYPE, "es_MX.UTF-8");
        std::thread cmatrixThreadInicial(runCMatrix);
        std::this_thread::sleep_for(std::chrono::seconds(3));  // Detener el programa durante 1 segundo
        // Detener cmatrix
        system("pkill cmatrix");
        // Esperar a que el hilo de cmatrix termine
        cmatrixThreadInicial.join();
        #elif _WIN32
            SetConsoleOutputCP(CP_UTF8);
        #endif
        bool ejecucion{true};
        std::string seleccion{};
        while(ejecucion)
        {
            system(CLEAR.c_str());
            std::cout << "\nMenu: " <<
                         "\n1 - Escuadras." <<
                         "\n2 - Tarjetas." <<
                         "\n3 - Crear tarjetas." <<
                         "\nS - Salir." <<
                         "\nSeleccion: ";
            std::getline(std::cin >> std::ws, seleccion);
            switch (seleccion[0])
            {
            case '1':
                escuadrasUI(); // funcion que contiene la interfaz de escuadras
                break;
            case '2':
                tarjetasUI(); // funcion que contiene la interfaz de tarjetas
                break;
            case '3':
                crearTarjetasUI();
                break;
            case 'S': case 's':
                ejecucion = false;
                
                break;
            
            default:
                break;
            }
        


        }
        #ifdef __linux__
        std::thread cmatrixThread(runCMatrix);
        std::this_thread::sleep_for(std::chrono::seconds(3));  // Detener el programa durante 1 segundo
        // Detener cmatrix
        system("pkill cmatrix");
        // Esperar a que el hilo de cmatrix termine
        cmatrixThread.join();
        #endif
       
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n'; //informe del problema
        std::exit(1); // salida con error fatal
    }
    std::cout << "\nFIN DEL PROGRAMA. o.O\n";
    return 0;
}


/******************************************************************************
 Nombre de funcion | escuadrasUI
 Descripcion | Esta funcion se encarga de la interfaz de usuario para escuadras
 Precondiciones | debe ser llamada por la funcion principal
 Parametros | NA
 Valores de retorno | void
 Notas | NA
******************************************************************************/
void escuadrasUI()
{
    std::string eleccion;
    int tam{0}, cordenadaX{-1}, cordenadaY{-1};
    do // ingreso del tamaño
    {
        system(CLEAR.c_str());
        std::cout << "ESCUADRAS" << 
                     "\n2^tamaño"
                     "\nColoque el tamaño del tablero: ";
        std::getline(std::cin >> std::ws, eleccion);
        if (eleccion[0] > 47 && eleccion[0] < 58)
        {
            tam = std::stoi(eleccion);
        }
        else
        {
            std::cout << "\nEl tamaño debe ser un numero entero" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));  // Detener el programa durante 1 segundo
        }
    } while (!tam);
    tam = std::pow(2, tam);
    do // ingreso de cordenada X
    {
        system(CLEAR.c_str());
        std::cout << " ESCUADRAS" << 
                     "\n Tamaño del tablero: " << tam << " x " << tam <<
                     "\n Coloque la cordenada x del punto sin escuadra: ";
        std::getline(std::cin >> std::ws, eleccion);
        if (eleccion[0] > 47 && eleccion[0] < 58)
        {
            cordenadaX = std::stoi(eleccion);
            if (cordenadaX >= tam || cordenadaX < 0)
            {
                std::cout << "\n 0 <= x < " << tam <<
                             "\nCordenada invalida." << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));  // Detener el programa durante 1 segundo
                cordenadaX = -1;
            }
        }
        else
        {
            std::cout << "\n La cordenada debe ser un punto valido." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));  // Detener el programa durante 1 segundo
        }
    } while (cordenadaX == -1);
    do // ingreso de cordenada Y
    {
        system(CLEAR.c_str());
        std::cout << " ESCUADRAS" << 
                     "\n Tamaño del tablero: " << tam << " x " << tam <<
                     "\n X = " << cordenadaX <<
                     "\n Coloque la cordenada Y del punto sin escuadra: ";
        std::getline(std::cin >> std::ws, eleccion);
        if (eleccion[0] > 47 && eleccion[0] < 58)
        {
            cordenadaY = std::stoi(eleccion);
            if (cordenadaY >= tam || cordenadaY < 0)
            {
                std::cout << "\n 0 <= x < " << tam <<
                             "\nCordenada invalida. " << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));  // Detener el programa durante 1 segundo
                cordenadaY = -1;
            }
        }
        else
        {
            std::cout << "\n La cordenada debe ser un punto valido." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));  // Detener el programa durante 1 segundo
        }
    } while (cordenadaY == -1);
    system(CLEAR.c_str());
    std::cout << " ESCUADRAS" << 
                 "\n Tamaño del tablero: " << tam << " x " << tam <<
                 "\n X = " << cordenadaX <<
                 "\n y = " << cordenadaY << std::endl;
    auto tablero = escuadras::generarTablero(tam, cordenadaX, cordenadaY);
    escuadras::calcularEscuadras(tam, tablero);
    escuadras::mostrarEscuadras(tablero);
    std::cout << "\nPresione cualquier tecla para continuar.";
    getchar();
    std::cout << "\n Desea guardar la matriz de escuadras en un archivo de texto?\n S/n: ";
    std::getline(std::cin >> std::ws, eleccion);
    if (eleccion[0] == 's' || eleccion[0] == 'S')
    {
        std::cout << "\n Desea nombrar su archivo de texto?\n S/n: ";
        std::getline(std::cin >> std::ws, eleccion);
        if (eleccion[0] == 's' || eleccion[0] == 'S')
        {
            std::cout << "\n Nombrado de archivo. " <<
                         "\n No coloque la extencion del archivo (.txt)" <<
                         "\n Coloque el nombre del archivo de texto: ";
            std::getline(std::cin >> std::ws, eleccion);
            eleccion += ".txt";
            escuadras::creacionArchivo(tablero, "./archivos/" + eleccion);
        }
        else
            escuadras::creacionArchivo(tablero);
    }

}
/******************************************************************************/
/* Nombre de funcion | tarjetasUI*/
/* Descripcion | Interfaz de usuario*/
/* Precondiciones | Se llama cuando se captura la opcion 2 en interfaz*/
/* Parametros | n/a     */
/* Valores de retorno | n/a*/
/* Notas | n/a */
/******************************************************************************/
void tarjetasUI()
{
    std::string ruta{"./archivos/tarjetas.txt"}, eleccion{}, rutaGuardado{"./archivos/tarjetasResultado.txt"};
    std::cout << "\n Desea usar el archivo " << ruta << "? \nS/n: ";
    std::getline(std::cin >> std::ws, eleccion);
    std::vector<int> tarjetas, retorno;
    if (eleccion[0] == 'n' || eleccion[0] == 'n')
    {
        std::cout << "\n Coloque la ruta del archivo: ";
        std::getline(std::cin >> std::ws, eleccion);
        bool existe = Tarjetas::existeArchivo(eleccion);
        if (!existe)
        {
            std::cout << "\n No existe ningun archivo en la ruta " << eleccion << std::endl;
            return;
        }
        tarjetas = Tarjetas::lectura(eleccion);
    }
    else
    {
        if (Tarjetas::existeArchivo(ruta))
        {
            tarjetas = Tarjetas::lectura(ruta);
        }
        else
        {
            std::cout << "\n No existe el archivo " << ruta << "." << std::endl;
        }
    }
    std::cout << "\n Calculando...";
    retorno = Tarjetas::calcularTarjetas(tarjetas);
    system(CLEAR.c_str());
    std::cout << "\n Calculo completado."
                 "\n Desea guardar en la ruta " << rutaGuardado <<
                 "\n S/n: ";
    std::getline(std::cin >> std::ws, eleccion);
    if (eleccion[0] == 'n' || eleccion[0] == 'N')
    {
        std::cout << "\n Coloque la ruta: ";
        std::getline(std::cin >> std::ws, eleccion);
        Tarjetas::creacionArchivo(eleccion, retorno, true);
    }
    Tarjetas::creacionArchivo(rutaGuardado, retorno, true);
}

/******************************************************************************/
/* Nombre de funcion | crearTarjetasUI                                        */
/* Descripcion | Interfaz de usuario                                          */
/* Precondiciones | Se llama cuando se captura la opcion 3 en interfaz        */
/* Parametros | n/a                                                           */
/* Valores de retorno | n/a                                                   */
/* Notas | n/a                                                                */
/******************************************************************************/
void crearTarjetasUI()
{
    int tam{};
    std::string ruta{"./archivos/"}, rutaArchivo{"tarjetas.txt"}, eleccion{};
    std::cout << "\n Ruta predeterminada: " << ruta << rutaArchivo <<
                 "\n Desea usar la ruta predeterminada?\n S/n: ";
    std::getline(std::cin >> std::ws, eleccion);
    if (eleccion[0] == 'n' || eleccion[0] == 'N')
    {
        std::cout << "\n (Debe existir)" <<
                     "\n Coloque la direccion de la carpeta en la que desea guardarlo: ";
        std::getline(std::cin >> std::ws, ruta);
        if (Tarjetas::existeCarpeta(ruta))
        {
            std::cout << "\n Coloque el nombre del archivo: ";
            std::getline(std::cin >> std::ws, rutaArchivo);
        }
        else
        {
            std::cout << "\n NO EXISTE LA CARPETA.";
            return;
        }
    }
    std::cout << "\n Las tarjetas se generaran aleatorioamente" <<
                 "\n 1 <= tarjeta < 200 000" <<
                 "\n EL maximo numero de tarjetas es 1000" << 
                 "\n Coloque el número de tarjetas a generar: ";
    std::getline(std::cin >> std::ws, eleccion);
    if (eleccion[0] > 47 && eleccion[0] < 58)
    {
        tam = std::stoi(eleccion);
        Tarjetas::verificacion(tam, ruta, rutaArchivo);
    }
    else
    {
        std::cout << "\n El numero de tarjetas debe estar en formato numerico";
    }
}