#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include "omp.h"


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

    if (argc > 1) {
        std::string ruta(argv[1]);

        std::ifstream entrada(ruta);
        std::ofstream salida("promedio.csv");

        if (entrada) {

#pragma omp parallel
            {
#pragma omp single 
                {
                    for (std::string linea; getline(entrada, linea);) {
#pragma omp task
                        {
                            vector<int> puntajes = obtenerPuntajes(linea);
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
#pragma omp critical
                                salida << fila << std::endl;
                            }
                            puntajes.clear();
                        }
                    }
                }
            }
        }
        salida.close();
    } else {
        participante();
    }
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