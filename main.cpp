#include <iostream>
#include <fstream>
#include <string>
#include <sstream> // Necesario para parsear las líneas del CSV

using namespace std;
// Prototipos de las funciones que ahora reciben el archivo
void searchAthlete(ifstream& archive);
void searchCountryGoldMedals(ifstream& archive);
void showGoldMedalsAthlete(ifstream& archive);

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Uso: ./programa <nombre_archivo_sin_extension>" << std::endl;
        return 1;
    }

    string nameArchive = string(argv[1]) + ".csv";
    ifstream archive(nameArchive);

    if (!archive.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo: " << nameArchive << std::endl;
        return 1;
    }

    std::cout << "Archivo abierto con exito: " << nameArchive << std::endl;

    // --- MENÚ PRINCIPAL ---
    int option;
    do {
        std::cout << "\n--- Menu de opciones ---\n"
                  << "1. Buscar atleta\n"
                  << "2. Buscar medallas de un pais\n"
                  << "3. Atleta con mas medallas\n"
                  << "4. Salir\n"
                  << "Seleccione una opcion (1-4): ";
        std::cin >> option;
        std::cin.ignore(); // Limpiar el buffer de entrada

        switch (option) {
            case 1:
                searchAthlete(archive);
                break;
            case 2:
                searchCountryGoldMedals(archive);
                break;
            case 3:
                showGoldMedalsAthlete(archive);
                break;
            case 4:
                std::cout << "Saliendo del programa.\n";
                break;
            default:
                std::cout << "Opcion no valida. Intente de nuevo.\n";
                break;
        }
    } while (option != 4);
    
    archive.close(); // Cerramos el archivo al final
    return 0;
}

void searchAthlete(ifstream& archive) {
    archive.clear();
    archive.seekg(0, std::ios::beg);

    string athleteName;
    std::cout << "Ingrese el nombre del atleta a buscar: ";
    std::getline(std::cin, athleteName);

    string line;
    std::getline(archive, line); // Saltar la línea del encabezado

    bool found = false;
    while (std::getline(archive, line)) {
        stringstream ss(line);
        string nombre, pais, disciplina, genero, medallaStr;
        
        std::getline(ss, nombre, ',');
        
        // Si el nombre del atleta en la línea actual contiene el texto buscado
        if (nombre.find(athleteName) != std::string::npos) {
            std::getline(ss, pais, ',');
            std::getline(ss, disciplina, ',');
            std::getline(ss, genero, ',');
            std::getline(ss, medallaStr, ',');
            
            std::cout << "\n--- Atleta Encontrado ---\n"
                      << "Nombre: " << nombre << "\n"
                      << "Pais: " << pais << "\n"
                      << "Disciplina: " << disciplina << "\n"
                      << "Genero: " << genero << "\n"
                      << "Medallas: " << medallaStr << std::endl;
            found = true;
        }
    }

    if (!found) {
        std::cout << "Atleta no encontrado." << std::endl;
    }
}

void searchCountryGoldMedals(ifstream& archive) {
    archive.clear();
    archive.seekg(0, std::ios::beg);

    string countryName;
    std::cout << "Ingrese el nombre del pais a buscar: ";
    std::getline(std::cin, countryName);

    string line;
    std::getline(archive, line); // Saltar encabezado

    int totalMedals = 0;
    while (std::getline(archive, line)) {
        stringstream ss(line);
        string nombre, pais, disciplina, genero, medallaStr;

        std::getline(ss, nombre, ',');
        std::getline(ss, pais, ',');
        
        if (pais == countryName) {
            std::getline(ss, disciplina, ',');
            std::getline(ss, genero, ',');
            std::getline(ss, medallaStr, ',');
            try {
                totalMedals += std::stoi(medallaStr);
            } catch (const exception&) {  }
        }
    }
    
    std::cout << "El pais " << countryName << " tiene un total de " << totalMedals << " medallas." << std::endl;
}

void showGoldMedalsAthlete(ifstream& archive) {
    archive.clear();
    archive.seekg(0, std::ios::beg);

    string line;
    std::getline(archive, line); // Saltar la línea del encabezado

    string topAthletes; // Un string para guardar todos los nombres
    int maxMedals = -1;

    while (std::getline(archive, line)) {
        stringstream ss(line);
        string nombre, pais, disciplina, genero, medallaStr;

        // Extraemos los datos de la línea
        std::getline(ss, nombre, ',');
        std::getline(ss, pais, ',');
        std::getline(ss, disciplina, ',');
        std::getline(ss, genero, ',');
        std::getline(ss, medallaStr, ',');
        
        try {
            int currentMedals = std::stoi(medallaStr);
            
            // Si encontramos un nuevo máximo
            if (currentMedals > maxMedals) {
                maxMedals = currentMedals;
                topAthletes = nombre; // Se convierte en el único de la lista
            } 
            // Si encontramos un empate con el máximo actual
            else if (currentMedals == maxMedals) {
                topAthletes += ", " + nombre; // Lo añadimos a la lista
            }
        } catch (const exception&) {
            // Ignora líneas donde la medalla no sea un número válido
        }
    }
    
    if (maxMedals == -1) {
        std::cout << "No se encontraron datos de medallas en el archivo." << std::endl;
    } else {
        std::cout << "Atleta(s) con mas medallas (" << maxMedals << " medallas): " << topAthletes << std::endl;
    }
}