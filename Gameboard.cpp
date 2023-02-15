#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <iomanip>

#include "Gameboard.hpp"

/**
 * \brief Konstruktor der Klasse Spielfeld.
 *
 * Der Konstruktor der Klasse beinhaltet nur eine Konsolenausgabe, da es fÅr das Spielfeld keine weiteren
 * Startargumente gibt.
 * @post Das Spielfeldobjekt ist nun erstellt.
 * @since Version 1.0
 * @author Felix Kirchner
 */
Gameboard::Gameboard()
{
    std::cout << "[System]: Spielfeld generiert." << std::endl; // Konsolenausgabe
}

/**
 * \brief Destruktor der Klasse Spielfeld.
 *
 * Der Destruktor der Klasse beinhaltet nur eine Konsolenausgabe, da es fÅr das Spielfeld keine weiteren
 * Argumente beim vernichten vorgesehen sind.
 * @pre Es muss ein Spielfeldobjekt geben.
 * @post Das Spielfeldobjekt ist nun geloescht.
 * @since Version 1.0
 * @author Felix Kirchner
 */
Gameboard::~Gameboard()
{
    std::cout << "[System]: Spielfeld geloescht." << std::endl; // Konsolenausgabe
}

/**
 * \brief Getter des Attributes Spielbrett
 *
 * Die Funktion gibt das Private Attribut "Spielbrett" zurueck, damit dieses von anderen Klassen benutz werden kann
 * @see Referenz auf andere Funktion, die Ñhnliches macht oder dazu gehîrt
 * @return Die Funktion gibt ein Array vom Typ String zurueck, welches das Spielbrett der Spielbrett-Klasse enthealt.
 * @pre Es muss ein Spielfeldobjekt existieren.
 * @since Version 1.0
 * @author Felix Kirchner
 */
std::array<std::string, 56> Gameboard::get_board() // Gibt das Array "Spielbrett" zurueck.
{
    return board;
}