#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector> // Necesario para usar vectores

using namespace std;

vector<string> g_nombres;
vector<string> g_paises;
vector<string> g_disciplinas;
vector<string> g_generos;
vector<int> g_medallas; 

void cargarDatos(ifstream& archive); 
void searchAthlete();
void searchCountryGoldMedals();
void showGoldMedalsAthlete();
void registerAthlete(const string& filename); 

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
    
    cargarDatos(archive);
    archive.close(); // Cerramos el archivo, ya no lo necesitamos para leer.

    // Menu Princupal 
    int option;
    do {
        std::cout << "\n--- Menu de opciones ---\n"
                  << "1. Buscar atleta\n"
                  << "2. Buscar medallas de un pais\n"
                  << "3. Atleta con mas medallas\n"
                  << "4. Registrar atleta\n"
                  << "5. Salir\n"
                  << "Seleccione una opcion (1-5): ";
        std::cin >> option;
        std::cin.ignore(); // Limpiar el buffer de entrada

        switch (option) {
            case 1:
                searchAthlete();
                break;
            case 2:
                searchCountryGoldMedals();
                break;
            case 3:
                showGoldMedalsAthlete(); 
                break;
            case 4:
                registerAthlete(nameArchive);
                break; 
            case 5:
                std::cout << "Saliendo del programa.\n";
                break;
            default:
                std::cout << "Opcion no valida. Intente de nuevo.\n";
                break;
        }
    } while (option != 5);
    
    return 0;
}

void cargarDatos(ifstream& archive) {
    string line;
    getline(archive, line); // Saltar la línea del encabezado

    while (getline(archive, line)) {
        stringstream ss(line);
        string nombre, pais, disciplina, genero, medallaStr;

        // Parsear la línea del CSV
        getline(ss, nombre, ',');
        getline(ss, pais, ',');
        getline(ss, disciplina, ',');
        getline(ss, genero, ',');
        getline(ss, medallaStr, ',');

        // agrega los datos a los vectores globales
        g_nombres.push_back(nombre);
        g_paises.push_back(pais);
        g_disciplinas.push_back(disciplina);
        g_generos.push_back(genero);
        try {
            g_medallas.push_back(stoi(medallaStr));
        } catch (const exception&) {
            g_medallas.push_back(0); // Si la medalla no es un número, se guarda 0
        }
    }
    std::cout << "Se cargaron " << g_nombres.size() << " registros de atletas en memoria." << std::endl;
}

void searchAthlete() {
    string athleteName;
    std::cout << "Ingrese el nombre del atleta a buscar: ";
    std::getline(std::cin, athleteName);

    bool found = false;
    // Iteramos sobre el vector de nombres
    for (size_t i = 0; i < g_nombres.size(); ++i) {
        if (g_nombres[i].find(athleteName) != std::string::npos) {
            std::cout << "\n--- Atleta Encontrado ---\n"
                      << "Nombre: " << g_nombres[i] << "\n"
                      << "Pais: " << g_paises[i] << "\n"
                      << "Disciplina: " << g_disciplinas[i] << "\n"
                      << "Genero: " << g_generos[i] << "\n"
                      << "Medallas: " << g_medallas[i] << std::endl;
            found = true;
        }
    }

    if (!found) {
        std::cout << "Atleta no encontrado." << std::endl;
    }
}

void searchCountryGoldMedals() {
    string countryName;
    std::cout << "Ingrese el nombre del pais a buscar: ";
    std::getline(std::cin, countryName);

    int totalMedals = 0;
    // Iteramos sobre el vector de países
    for (size_t i = 0; i < g_paises.size(); ++i) {
        if (g_paises[i] == countryName) {
            totalMedals += g_medallas[i];
        }
    }
    
    std::cout << "El pais " << countryName << " tiene un total de " << totalMedals << " medallas." << std::endl;
}

void showGoldMedalsAthlete() {
    if (g_nombres.empty()) {
        std::cout << "No hay datos de atletas cargados." << std::endl;
        return;
    }

    string topAthletes;
    int maxMedals = -1;

    // Iteramos sobre el vector de medallas
    for (size_t i = 0; i < g_medallas.size(); ++i) {
        if (g_medallas[i] > maxMedals) {
            maxMedals = g_medallas[i];
            topAthletes = g_nombres[i];
        } 
        else if (g_medallas[i] == maxMedals) {
            topAthletes += ", " + g_nombres[i];
        }
    }
    
    if (maxMedals == -1) {
        std::cout << "No se encontraron datos de medallas." << std::endl;
    } else {
        std::cout << "Atleta(s) con mas medallas (" << maxMedals << " medallas): " << topAthletes << std::endl;
    }
}

void registerAthlete(const string& filename) {
    string nombre, pais, disciplina, genero, medallasStr;

    std::cout << "\n--- Registrar Nuevo Atleta ---\n";
    std::cout << "Ingrese el nombre: ";
    std::getline(std::cin, nombre);
    
    std::cout << "Ingrese el pais: ";
    std::getline(std::cin, pais);

    std::cout << "Ingrese la disciplina: ";
    std::getline(std::cin, disciplina);

    std::cout << "Ingrese el genero (Male/Female): ";
    std::getline(std::cin, genero);
    
    std::cout << "Ingrese el numero de medallas: ";
    std::getline(std::cin, medallasStr);

    ofstream archive(filename, ios::app);
    if (archive.is_open()) {
        archive << endl << nombre << "," << pais << "," << disciplina << "," << genero << "," << medallasStr;
        archive.close();
    } else {
        std::cerr << "Error: No se pudo abrir el archivo para registrar." << std::endl;
        return;
    }

    g_nombres.push_back(nombre);
    g_paises.push_back(pais);
    g_disciplinas.push_back(disciplina);
    g_generos.push_back(genero);
    try {
        g_medallas.push_back(stoi(medallasStr));
    } catch (const exception&) {
        g_medallas.push_back(0);
    }

    std::cout << "Atleta registrado con exito." << std::endl;
}