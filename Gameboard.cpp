#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <iomanip>

#include "Gameboard.hpp"

/**
 * @brief Konstruktor der Klasse "Gameboard".
 * Der Konstruktor der Klasse beinhaltet nur eine Konsolenausgabe, da es fuer das Spielfeld keine weiteren
 * Startargumente gibt.
 * @post Das Gameboard-Objekt ist nun erstellt.
 * @since Version 1.0
 * @author Felix Kirchner
 */
Gameboard::Gameboard()
{
    std::cout << "[System]: Spielfeld generiert." << std::endl; // Konsolenausgabe
}

/**
 * @brief Destruktor der Klasse "Gameboard".
 * Der Destruktor der Klasse beinhaltet nur eine Konsolenausgabe, da fuer das Spielfeld keine weiteren
 * Argumente beim vernichten vorgesehen sind.
 * @pre Es muss ein Gameboard-Objekt geben.
 * @post Das Gameboard-Objekt ist nun geloescht.
 * @since Version 1.0
 * @author Felix Kirchner
 */
Gameboard::~Gameboard()
{
    std::cout << "[System]: Spielfeld geloescht." << std::endl; // Konsolenausgabe
}

/**
 * @brief Getter des Attributes "board".
 * Die Funktion gibt das private Attribut "board" zurueck, damit dieses von anderen Klassen benutzt werden kann.
 * @return Die Funktion gibt ein Array vom Typ std::string zurueck, welches das board der Gameboard-Klasse enthealt.
 * @pre Es muss ein Gameboard-Objekt existieren.
 * @since Version 1.0
 * @author Felix Kirchner
 */
std::array<std::string, 56> Gameboard::get_board()
{
    return board; // Gibt das Attribut "board" zurueck.
}