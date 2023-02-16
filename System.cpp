#include <random>
#include <time.h>

#include "System.hpp"
#include "Player.hpp"

/**
 * @brief Funktion zum generieren einer Zufallszahl.
 * Es wird anhand eines eingegebenen Integer-Wertes eine obere Grenze gesetzt. Die Funktion
 * bestimmt dann einen zufaelligen Wert zwischen 1 und der oberen Grenze, wobei das Setzen des Seeds durch srand(time(NULL))
 * den Zufallsparameter in Abhaengigkeit von der Zeit bestimmt, somit die Werte nicht bei jedem Programmablauf gleich sind.
 * @param ObereGrenze Die obere Grenze des Zufallsgenerators
 * @return Gibt die generierte ganzahlige Zufallszahl als Integer zurueck
 * @post Eine Zufallszahl aus einem festgelegten Bereich ist gegeben
 * @since Version 1.1
 * @author Felix Kirchner
 */
int System::randomizer(int ObereGrenze) // Berechnet eine zufaellige Zahl von 1 bis x
{
    srand(time(NULL));
    return rand() % ObereGrenze + 1;
}

/**
 * \brief Funktion zum Ausgeben eines Startbildschirmes in der Konsole.
 * Die Funktion gibt eine grafische Ausgabe in der Konsole aus,
 * welche das Spiel einläuten soll.
 * @since Version 1.0
 * @author Felix Kirchner
 */
void System::initialiseGame()
{
    std::cout << "=================================================" << std::endl;
    std::cout << "*                                               *" << std::endl;
    std::cout << "*                  Willkommen                   *" << std::endl;
    std::cout << "*                     bei                       *" << std::endl;
    std::cout << "*                Mensch Aergere                 *" << std::endl;
    std::cout << "*                  Dich nicht                   *" << std::endl;
    std::cout << "*                                               *" << std::endl;
    std::cout << "*                                               *" << std::endl;
    std::cout << "*    Druecke [Enter] um das Spiel zu starten    *" << std::endl;
    std::cout << "*                                               *" << std::endl;
    std::cout << "=================================================" << std::endl;
    std::cin.ignore(); // Konsole wartet auf Eingabe von Enter.
}