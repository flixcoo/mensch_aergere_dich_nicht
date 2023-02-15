#include <random>
#include <iostream>

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
    static int randomizer(int);   // Zufallsgenerator, welcher eine Zufallszahl zwischen eins und einem selbstgewaehlten Wert zurueckgibt.
    static void initialiseGame(); // Konsolenausgabe zum Starten des Spiels.
};