#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int main(int s, char* argv[]) {
    // Comprueba si se introdujo datos
    if (s < 2) {
        std::cerr << "No datos enviados" << std::endl;
        return 1;
    }

    if (s > 2) {
        std::cerr << "Error: no se permite en espacios, intente de nuevo." << std::endl;
        return 1;
    }

    string nameArchive = string(argv[1]) + ".csv";
    std::ifstream archive(nameArchive);
    // Comprueba que se encuentre un archivo existente
    if (!archive.is_open()) {
        cerr << "No se pudo abrir el archivo: " << nameArchive << std::endl;
        return 1;
    }
    cout << "Archivo abierto: " << nameArchive << endl;
    // menu
    std::cout << "Menu de opciones:\n";
    std::cout << "1. Buscar atlteta\n";
    std::cout << "2. Buscar medallas de oro de un pais\n";
    std::cout << "3. Atleta con mas medallas\n";
    std::cout << "4. Salir\n";
    int option;
    std::cout << "Seleccione una opcion: ";
    std::cin >> option;
    std::cin.ignore(); // Limpiar el buffer de entrada
    switch (option) {
        case 1:
            std::cout << "Buscar atleta seleccionado.\n";
            // Lógica para buscar atleta
            break;
        case 2:
            std::cout << "Buscar medallas de oro de un pais seleccionado.\n";
            // Lógica para buscar medallas de oro
            break;
        case 3:
            std::cout << "Atleta con mas medallas seleccionado.\n";
            // Lógica para encontrar atleta con más medallas
            break;
        case 4:
            std::cout << "Saliendo del programa.\n";
            break;
        default:
            std::cout << "Opcion no valida. Intente de nuevo.\n";
            break;
    }
    return 0;
}
