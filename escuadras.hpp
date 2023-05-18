#include <bits/stdc++.h>
#include "iostream"

namespace escuadras
{
    int numeroEscuadra = 0;

    // calcularEscuadrasión para llenar las esquinas de los tres subtableros
    // que no contienen la celda faltante
    // linea             columna,
/******************************************************************************
 Nombre de funcion | llenar()
 Descripcion | coloca el número a la escuadra "nueva" en los valores proporcionados. 
 Precondiciones | Definición de numeroEscuadra, validez de los índices (los parámetros deben ser enteros válidos)
 Parametros | x1, y1, x2, y2, x3, y3 
 Valores de retorno | No retorna.
 Notas | Cada vez que se llama la función,aumenta el número de escuadra +1. 
******************************************************************************/    
    void llenar(int x1, int y1, int x2, int y2, int x3, int y3, std::vector<std::vector<int>> &tablero)
    {
        numeroEscuadra++;
        tablero[x1][y1] = numeroEscuadra;
        tablero[x2][y2] = numeroEscuadra;
        tablero[x3][y3] = numeroEscuadra;
    }

    // calcularEscuadras para llenar el tablero
/******************************************************************************
 Nombre de funcion | calcularEscuadras()
 Descripcion | 
 -Si el tablero es de tamaño 2x2 (caso base): Toma el tablero y llena con el número de la escuadra actual, excepto la celda que ya está ocupada. 
 -Si el tablero es más grande que 2x2, se busca la celda ocupada y se divide el tablero en cuatro cuadrantes. Se pone una escuadra en el centro de manera que ocupa una celda en cada cuadrante, excepto en el cuadrante donde se encuentra la celda ya ocupada. Se llama a la función de manera recursiva para cada cuadrante, considerando que cada cuadrante tiene ahora una celda ocupada.
 Precondiciones | 'tam' debe ser una potencia de 2 
 Parametros | x1, y1, x2, y2, x3, y3 
 Valores de retorno | No retorna.
 Notas |  
******************************************************************************/    
    void calcularEscuadras(int tam, std::vector<std::vector<int>> &tablero, int f = 0, int c = 0)
    {
        // Declarar variables que almacenarán el número de fila y columna de la celda faltante
        int fila_celda_faltante, col_celda_faltante;
        // Caso base
        // Si el tamaño del tablero es 2x2 (tam=2)
        if (tam == 2)
        {
            // Llenaremos el tablero con una nueva figura,
            // que aumentará el contador de figuras en 1
            numeroEscuadra++;
            // Llenar todas las celdas excepto la que falta
            for (int i = 0; i < tam; i++) // Filas
            {
                for (int j = 0; j < tam; j++) // Columnas
                {
                    if (tablero[f + i][c + j] == 0)
                    {
                        tablero[f + i][c + j] = numeroEscuadra;
                    }
                }
            }
            return;
        }
        else
        {
            // Encontrar la fila y columna de la celda faltante
            for (int i = f; i < f + tam; i++)
            {
                for (int j = c; j < c + tam; j++)
                {
                    if (tablero[i][j] != 0)
                        // La celda cuyo valor no es 0 es la celda faltante
                        fila_celda_faltante = i,
                        col_celda_faltante = j;
                }
            }
        }

        // Si la celda faltante está en el 1er cuadrante
        if (fila_celda_faltante < f + tam / 2 && col_celda_faltante < c + tam / 2)
        {
            llenar(f + tam / 2, c + (tam / 2) - 1, f + tam / 2, c + tam / 2, f + tam / 2 - 1, c + tam / 2, tablero);
        }

        // Si la celda faltante está en el 3er cuadrante
        else if (fila_celda_faltante >= f + tam / 2 && col_celda_faltante < c + tam / 2)
        {
            llenar(f + (tam / 2) - 1, c + (tam / 2), f + (tam / 2), c + tam / 2, f + (tam / 2) - 1, c + (tam / 2) - 1, tablero);
        }

        // Si la celda faltante está en el 2do cuadrante
        else if (fila_celda_faltante < f + tam / 2 && col_celda_faltante >= c + tam / 2)
        {
            llenar(f + tam / 2, c + (tam / 2) - 1, f + tam / 2, c + tam / 2, f + tam / 2 - 1, c + tam / 2 - 1, tablero);
        }

        // Si la celda faltante está en el 4to cuadrante
        else if (fila_celda_faltante >= f + tam / 2 && col_celda_faltante >= c + tam / 2)
        {
            llenar(f + (tam / 2) - 1, c + (tam / 2), f + (tam / 2), c + (tam / 2) - 1, f + (tam / 2) - 1, c + (tam / 2) - 1, tablero);
        }

        // Llamar a la calcularEscuadras recursiva para los 4 subtableros
        //                tam    tablero  fila      columna
        calcularEscuadras(tam / 2, tablero, f, c + tam / 2);         // 1er cuadrante
        calcularEscuadras(tam / 2, tablero, f, c);                 // 3er cuadrante
        calcularEscuadras(tam / 2, tablero, f + tam / 2, c);         // 2do cuadrante
        calcularEscuadras(tam / 2, tablero, f + tam / 2, c + tam / 2); // 4to cuadrante

        return;
    }

    void mostrarEscuadras(std::vector<std::vector<int>>& tablero)
    {
        int tam = tablero.size();
        std::cout << std::endl << "#\t";
        for (int i = 0; i < tam; i++)
        {
            std::cout << i << "\t";
        }
        std::cout << std::endl;
        // Imprimir el tablero lleno al final
        for (int i = 0; i < tam; i++)
        {
            std::cout << i << "\t";
            for (int j = 0; j < tam; j++)
            {
                std::cout << tablero[i][j] << "\t";
            }
            std::cout << std::endl;
        }

        return;
    }
    std::vector<std::vector<int>> generarTablero(int tam, int cordenadaX = 0, int cordenadaY = 0)
    {
        std::cout << "\nGenerando tablero.";
        std::vector<std::vector<int>> tablero;
        for (int i{0}; i < tam; i++)
        {
            std::vector<int> linea;
            for (int j{0}; j < tam; j++)
            {
                linea.push_back(0);
            }
            tablero.push_back(linea);
        }
        tablero[cordenadaY][cordenadaX] = -1;
        return tablero;
    }

    void creacionArchivo(std::vector<std::vector<int>> matriz, const std::string nombre = "./archivos/escuadras.txt")
    {
        std::ofstream archivo(nombre); // creamos un archivo con el nombre que recibimos como   parametro
        try
        {
            if (!archivo) // comprobamos si el archivo se creo correctamente
            {
                // si el archivo no se creo
                throw std::runtime_error("\nNo se pudo abrir el archivo.");
            }
            // trajamos con el archivo recien creado
            for (auto arr : matriz)
            {
                for (int dato : arr)
                {
                    archivo << std::to_string(dato) << "\t"; 
                }
                archivo << std::endl;
            }

        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
        archivo.close();
    }
} // namespace escuadras
