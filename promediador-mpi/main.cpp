#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include "mpi.h"

#define LARGO 100

using namespace std;

/**
 * Función que muestra los participantes del grupo
 */
void participante();

/**
 * 
 * @param linea Línea leída desde un archivo
 * @return el arreglo con los puntajes
 */
vector<int> obtenerPuntajes(std::string linea);

/**
 * Taller computacional
 * @param argc cantidad de argumentos
 * @param argv argumentos
 * @return El código de salida del programa
 */
int main(int argc, char** argv) {
    int mi_rango; /* rango del proceso    */
    int procesadores; /* numero de procesos   */
    int maestro = 0; /* Identificador maestro */
    int escritor = 1; /* Procesador escritor */
    int tag = 0; /* etiqueta del mensaje */
    MPI_Status estado; /* devuelve estado al recibir*/

    /* Este string se usara para detener los hilos paralelos */
    std::string parar("STOP");

    if (argc > 1) {


        /* Comienza las llamadas a MPI */
        MPI_Init(&argc, &argv);

        /* Averiguamos el rango de nuestro proceso */
        MPI_Comm_rank(MPI_COMM_WORLD, &mi_rango);

        /* Averiguamos el número de procesos que estan 
         * ejecutando nuestro porgrama 
         */
        MPI_Comm_size(MPI_COMM_WORLD, &procesadores);

        if (procesadores < 3) {
            fprintf(stderr, "\nLa implementación requiere al menos 3 procesadores\n");
            return EXIT_FAILURE;
        }


        if (mi_rango == 0) {
            /* Si paso por acá, soy el proceso MAESTRO */
            /**
             * 
             * Generación de archivos
             */

            std::string ruta(argv[1]);
            std::ifstream entrada(ruta);
            if (entrada) {
                /*
                 * En esta estrategia usaremos 
                 * El procesador 0 como maestro (lee y distribuye)
                 * El procesador 1 como escritor (recibe los promedios y escribe en disco)
                 * Los demás procesadores como "promediadores"
                 */
                int procesador = 2;
                for (std::string lectura; getline(entrada, lectura);) {
                    if (!lectura.empty()) {
                        /* Usa length +1 para que la marca /0 se transmita */
                        MPI_Send((char *) lectura.c_str(), lectura.length() + 1, MPI_CHAR, procesador, tag, MPI_COMM_WORLD);

                        procesador += 1;
                        if (procesador >= procesadores) {
                            procesador = 2;
                        }
                    }
                }
                std::cout << std::endl;

                for (procesador = 2; procesador < procesadores; procesador++) {
                    MPI_Send((char *) parar.c_str(), parar.length() + 1, MPI_CHAR, procesador, tag, MPI_COMM_WORLD);
                }

                entrada.close();
            }

            /*
             * Muestro los participantes
             */
            participante();
        } else if (mi_rango == 1) {
            /*
             * Este procesador se dedicará a recibir los datos para construir el archivo.
             */

            /* Obtengo el mensajes */
            std::ofstream salida("promedios.csv");
            bool procesar = true;
            while (procesar) {
                for (int procesador = 2; procesador < procesadores; procesador++) {
                    char* escritura = (char *) calloc(LARGO, sizeof (char));
                    MPI_Recv(escritura, LARGO, MPI_CHAR, procesador, tag, MPI_COMM_WORLD, &estado);
                    std::string texto(escritura);
                    if (parar.compare(texto) == 0 || texto.empty()) {
                        procesar = false;
                    } else {
                        salida << texto << std::endl;
                    }
                    free(escritura);
                }
            }
            salida.close();
        } else {
            /* Obtengo el mensajes */
            while (true) {
                char* mensaje = (char *) calloc(LARGO, sizeof (char));
                MPI_Recv(mensaje, LARGO, MPI_CHAR, maestro, tag, MPI_COMM_WORLD, &estado);
                std::string fila(mensaje);
                if (parar.compare(fila) == 0 || fila.empty()) {
                    // No hay datos, se debe salir del loop
                    MPI_Send((char *) parar.c_str(), parar.length() + 1, MPI_CHAR, escritor, tag, MPI_COMM_WORLD);
                    break;
                } else {
                    vector<int> puntajes = obtenerPuntajes(fila);
                    if (puntajes.size() >= 6) {
                        int rut = puntajes.at(0);
                        int nem = puntajes.at(1);
                        int ranking = puntajes.at(2);
                        int matematica = puntajes.at(3);
                        int lenguaje = puntajes.at(4);
                        int ciencias = puntajes.at(5);
                        int historia = puntajes.at(6);

                        double promedio = (nem + ranking + matematica + lenguaje + ciencias + historia) / 6.0;
                        std::string fila;
                        fila = std::to_string(rut) + ";" + to_string(promedio);

                        MPI_Send((char *) fila.c_str(), fila.length() + 1, MPI_CHAR, escritor, tag, MPI_COMM_WORLD);
                    }
                }
                free(mensaje);
            }


        }

        /* Termina con MPI. Recordemos que después de 
         * esta llamada no podemos llamar a funciones 
         * MPI, ni siquiera de nuevo a MPI_Init 
         */
        MPI_Finalize();
    }
    /**
     * 
     * Muestro los participantes.
     */


    return EXIT_SUCCESS;
}

void participante() {
    std::cout << std::endl << "=== Tarea ===" << std::endl;
    std::cout << std::endl << "Sebastián Salazar Molina" << std::endl; // Reemplazar por su nombre
}

vector<int> obtenerPuntajes(std::string linea) {
    vector<int> arreglo;
    std::stringstream ss(linea);
    std::string item;

    while (std::getline(ss, item, ';')) {
        int valor = atoi(item.c_str());
        arreglo.push_back(valor);
    }

    return arreglo;
}
