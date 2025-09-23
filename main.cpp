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
    return 0;
}
