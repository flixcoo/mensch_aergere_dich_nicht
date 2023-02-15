#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <iomanip>

#include "Spielfeld.hpp"

/**
 * \brief Konstruktor der Klasse Spielfeld.
 *
 * Der Konstruktor der Klasse beinhaltet nur eine Konsolenausgabe, da es f�r das Spielfeld keine weiteren
 * Startargumente gibt.
 * @post Das Spielfeldobjekt ist nun erstellt.
 * @since Version 1.0
 * @author Felix Kirchner
 */
PlayingField::PlayingField()
{
    std::cout << "[System]: Spielfeld generiert." << std::endl; // Konsolenausgabe
}

/**
 * \brief Destruktor der Klasse Spielfeld.
 *
 * Der Destruktor der Klasse beinhaltet nur eine Konsolenausgabe, da es f�r das Spielfeld keine weiteren
 * Argumente beim vernichten vorgesehen sind.
 * @pre Es muss ein Spielfeldobjekt geben.
 * @post Das Spielfeldobjekt ist nun geloescht.
 * @since Version 1.0
 * @author Felix Kirchner
 */
PlayingField::~PlayingField()
{
    std::cout << "[System]: Spielfeld geloescht." << std::endl; // Konsolenausgabe
}

/**
 * \brief Getter des Attributes Spielbrett
 *
 * Die Funktion gibt das Private Attribut "Spielbrett" zurueck, damit dieses von anderen Klassen benutz werden kann
 * @see Referenz auf andere Funktion, die �hnliches macht oder dazu geh�rt
 * @return Die Funktion gibt ein Array vom Typ String zurueck, welches das Spielbrett der Spielbrett-Klasse enthealt.
 * @pre Es muss ein Spielfeldobjekt existieren.
 * @since Version 1.0
 * @author Felix Kirchner
 */
std::array<std::string, 56> PlayingField::get_board() // Gibt das Array "Spielbrett" zurueck.
{
    return board;
}