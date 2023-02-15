#include <random>
#include <time.h>

#include "System.hpp"
#include "Spieler.hpp"

/**
 * @brief Diese Funktion generiert eine Zufallszahl.
 * Es wird anhand eines eingegebenen Integer-Wertes eine obere Schranke gesetzt. Die Funktion
 * bestimmt dann einen zufaelligen Wert zwischen 1 und der oberen Grenze, wobei das Setzen des Seeds durch srand(time(NULL))
 * den Zufallsparameter in Abhaengigkeit von der Zeit bestimmt, somit die Werte nicht bei jedem Programmablauf gleich sind.
 * @param ObereGrenze Die obere Grenze des Zufallsgenerators
 * @return Gibt die generierte ganzahlige Zufallszahl als Integer zurueck
 * @post Eine Zufallszahl aus einem festgelegten Bereich ist gegeben
 * @since Version 1.0
 * @author Felix Kirchner
 */
int System::randomizer(int ObereGrenze) // Berechnet eine zufaellige Zahl von 1 bis x
{
        srand(time(NULL));
        int wurf = 0;
        wurf = rand() % ObereGrenze + 1;
        return wurf;
}

/**
 * \brief Kurzbeschreibung
 *
 * Langbeschriebung
 * @param parameter1 Funktion des Parameters 1
 * @param parameter2 Funktion des Parameters 2
 * @see Referenz auf andere Funktion, die ?hnliches macht oder dazu geh?rt
 * @return Beschreibung des R?ckgabewertes
 * @pre Bedingungen, die vor dem Aufruf der Funktion erf?llt sein m?ssen
 * @post Bedingungen, die nach dem Aufruf der Funktion erf?llt sind
 * @since Wann die Funktion eingef?hrt wurde
 * @author Autor der Funktion
 */
void System::initialiseGame() // Konsolenausgabe
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
    std::cin.ignore(); // Konsole wartet auf Tasteneingabe
}