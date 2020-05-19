#include <iostream>
#include <fstream>
#include <cstdlib>
#include <random>
#include <omp.h>
#include "db.h"

using namespace std;

/**
 * Función que muestra los participantes del grupo
 */
void participante();

/**
 * 
 * @param inferior límite menor para buscar
 * @param superior límite mayor para buscar
 * @return un número entre dichos límites
 */
int aleatoreo(int inferior, int superior);

/**
 * Taller computacional
 * @param argc cantidad de argumentos
 * @param argv argumentos
 * @return El código de salida del programa
 */
int main(int argc, char** argv) {



#pragma omp parallel 
    {

        PGconn* conexion = dbconnect((char *) DBSERVER, DBPORT, (char *) DBNAME, (char *) DBUSER, (char *) DBPASSWORD);

#pragma omp for
        for (unsigned long rut = 14916641; rut <= 19932391; rut++) {
            int nem = aleatoreo(475, 750);
            int ranking = aleatoreo(475, 750);
            int matematica = aleatoreo(475, 750);
            int lenguaje = aleatoreo(475, 750);
            int ciencias = aleatoreo(475, 750);
            int historia = aleatoreo(475, 750);

            std::string linea;
            linea = "INSERT INTO puntajes (rut, nem, ranking, matematica, lenguaje, ciencias, historia) VALUES ('" + std::to_string(rut) + "','" + std::to_string(nem) + "','" + std::to_string(ranking) + "','" + std::to_string(matematica) + "','" + std::to_string(lenguaje) + "','" + std::to_string(ciencias) + "','" + std::to_string(historia) + "');";


            PGresult* resultado = dbquery(conexion, (char *) linea.c_str());
            dbfree(resultado);


        }

        dbclose(conexion);

    }



    participante();
    return EXIT_SUCCESS;
}

void participante() {
    std::cout << std::endl << "=== Tarea ===" << std::endl;
    std::cout << std::endl << "Sebastián Salazar Molina" << std::endl; // Reemplazar por su nombre
}

int aleatoreo(int inferior, int superior) {
    /**
     * Si se especifica usa un dispositivo de generación de números pseudoaleatoreos o /dev/urandom
     */
    std::random_device dispositivo;

    /**
     * 
     * Se especifica una distribución uniforme de datos.
     */
    std::uniform_int_distribution<int> distribucion(inferior, superior);

    // Retornamos un número pseudoaleatoreo
    return distribucion(dispositivo);
}
