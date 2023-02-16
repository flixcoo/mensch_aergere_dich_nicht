#include <iostream>
#include <random>

/**
 * @brief Dies ist eine Klasse, welche verschiedene Systemoperationen durchfuehrt.
 * Sie ist dazu gedacht, generelle Operationen durchzufuehren. Von Ihr wird kein
 * Objekt erstellt, weshalb alle Methoden statisch sind.
 * @author Felix Kirchner
 * @see Spieler
 */
class System
{
public:
    static int randomizer(int);   // Funktion zum generieren einer Zufallszahl.
    static void initialiseGame(); // Funktion zum Ausgeben eines Startbildschirmes in der Konsole.
};