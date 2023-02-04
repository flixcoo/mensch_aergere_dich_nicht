#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <iomanip>

#include "Spielfeld.hpp"

// Konstruktor
Spielfeld::Spielfeld()
{
    std::cout << "[System]: Spielfeld generiert." << std::endl; // Konsolenausgabe
}

// Destruktor
Spielfeld::~Spielfeld()
{
    std::cout << "[System]: Spielfeld geloescht." << std::endl; // Konsolenausgabe
}

// Getter
std::array<std::string, 56> Spielfeld::get_Spielbrett() // Gibt das Array "Spielbrett" zurueck.
{
    return Spielbrett;
}

void Spielfeld::InitialisiereSpiel() // Konsolenausgabe
{
    std::cout << "=================================================" << std::endl;
    std::cout << "*                                               *" << std::endl;
    std::cout << "*                  Willkommen                   *" << std::endl;
    std::cout << "*                     bei                       *" << std::endl;
    std::cout << "*                Mensch Aergere                 *" << std::endl;
    std::cout << "*                  Dich nicht                   *" << std::endl;
    std::cout << "*                                               *" << std::endl;
    std::cout << "*                                               *" << std::endl;
    std::cout << "*          [Press any key to continue]          *" << std::endl;
    std::cout << "*                                               *" << std::endl;
    std::cout << "=================================================" << std::endl;
    std::cin.ignore(); // Konsole wartet auf Tasteneingabe
}