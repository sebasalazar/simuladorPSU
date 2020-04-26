#include <iostream>
#include <fstream>
#include <random>
#include <cstdlib>


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
    // srand((unsigned int) time(0));

    std::ofstream archivoSalida("puntajes.csv");

    for (unsigned long rut = 14916641; rut <= 19932391; rut++) {
        archivoSalida << rut << ";";
        for (int i = 0; i < 6; i++) {
            archivoSalida << aleatoreo(475, 750) << ";";
        }
        archivoSalida << std::endl;
    }

    archivoSalida.close();

    participante();
    return EXIT_SUCCESS;
}

void participante() {
    std::cout << std::endl << "=== Tarea ===" << std::endl;
    std::cout << std::endl << "Sebastián Salazar Molina" << std::endl; // Reemplazar por su nombre
}

int aleatoreo(int inferior, int superior) {
    std::uniform_int_distribution<int> distribucion(inferior, superior);

    std::random_device dispositivo; // usa un dispositivo o /dev/urandom
    return distribucion(dispositivo);
}

/*
int aleatoreo(int inferior, int superior) {
    return (rand() % (superior - (inferior + 1))) +inferior;
}
 */ 