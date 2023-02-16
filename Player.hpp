#include <iostream>
#include <string>
#include <vector>
#include <array>

/**
 * @brief Dies ist die Klasse, welche den Spieler darstellt.
 * Die Klasser beinhaltet einen Spieler und seine Eigentschaften. Sie besitzt das Integer-Attribut "identifier", welches dazu dient den Spieler anhand zu einer Zahl identifizieren.
 * Das String-Attribut "startingField" stellt das Startfeld des jeweiligen Spielers da.
 * Das currentField-Array beinhaltet die aktuellen Felder der vier Spielfiguren.
 * Das distance-Array beinhaltet die gegangene Distanz der vier Spielfiguren.
 * Das targetFields-Array beinhaltet die vier Zielfelder des Spielers.
 * @author Felix Kirchner
 * @see Spielablauf
 */
class Player
{
private:
    int identifier;      // Integer mit einem Identifikator für das Player-Objekt.
    std::string Storage; // Zeichen, anhand dessen das Programm erkennt, dass sich eine Figur im Lager befindet.

    std::string startingField;               // String der das Startfeld des Spielers enthaelt.
    std::array<std::string, 4> currentField; // Array der Groesse 4 welches Strings mit den aktuellen Positionen der vier Spielfiguren enthaelt.
    std::array<int, 4> distance;             // Array der Groesse 4 welches Integer mit der aktuell zurueckgelegten Distanz der jeweiligen Figuren enthaelt.
    std::array<std::string, 4> targetFields; // Array der Groesse 4 welches die vier Zielfelder enthaelt.

public:
    // Objektmanagement
    Player(int, std::string, std::array<std::string, 4>, std::array<std::string, 4>, std::array<int, 4>); // Konstruktor der Klasse Player
    ~Player();                                                                                            // Destruktor der Klasse Player

    // Getter der Klasse
    int get_identifier();                           // Getter des Attributes "identifier".
    std::string get_startingField();                // Getter des Attributes "startingField".
    std::array<std::string, 4> get_targetFields();  // Getter des Attributes "targetFields".
    std::array<std::string, 4> &get_currentField(); // Getter des Attributes "currentField".
    std::array<int, 4> &get_distance();             // Getter des Attributes "distance".

    // Aktionen der Figuren
    int rollDice();          // Methode, welche eine Zufallszahl zwischen eins und sechs zurueckgibt.
    int selectToken();       // Methode, welche den Benutzer eine Spielfigur auswaehlen laesst.
    int randomFromStorage(); // Methode, welche eine zufaellige Figur aus dem Lager auswaehlt und den Index dieser Figur zurueckgibt.
    int randomFromArena();   // Methode, welche eine zufaellige Figur aus dem Spielfeld auswaehlt und den Index dieser Figur zurueckgibt.

    // Einzelabfragen
    bool tokenInStorage(int);     // Methode, welche ueberprüft, ob eine Figur am jeweiligen Index im Lager ist.
    bool tokenInArena(int);       // Methode, welche ueberprüft, ob eine Figur am jeweiligen Index auf dem Spielfeld ist.
    bool tokenInTargetField(int); // Methode, welche ueberprüft, ob eine Figur am jeweiligen Index auf einem Zielfeld ist.

    // Gebuendelte Abfragen
    bool allTokenInStorage();     // Methode, welche ueberprüft, ob alle Spielfiguren im Lager sind
    bool allTokenInArena();       // Methode, welche ueberprüft, ob alle Spielfiguren auf dem Spielfeld sind
    bool allTokenInTargetField(); // Methode, welche ueberprüft, ob alle Spielfiguren im Ziel sind

    // Vorraussetzungen
    bool minOneInStorage();     // Methode, welche ueberprueft, ob mindestens eine Spielfigur im Lager ist.
    bool minOneInArena();       // Methode, welche ueberprueft, ob mindestens eine Spielfigur im Spielfeld ist.
    bool minOneInTargetField(); // Methode, welche ueberprueft, ob mindestens eine Spielfigur in einem der Zielfelder ist.
};