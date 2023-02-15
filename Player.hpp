#include <iostream>
#include <string>
#include <vector>
#include <array>

/**
 * @brief Dies ist die Klasse, welche den Spieler darstellt. *
 * Die Klasser beinhaltet einen Spieler und seine Eigentschaften. Es besitzt einen String...
 *
 * @author Felix Kirchner
 * @see Spielablauf
 */
class Player
{
private:
    int identifier;
    std::string Lager;                        // String dem die Zahl des Lagers ("X") zugewissen wird.
    std::string startingField;                // String dem das Startfeldern des Spielers zugewiesen wird.
    std::array<std::string, 4> targetFields;  // Array der Groesse 4 welches mit Strings der vier Zielfelder gefuellt wird.
    std::array<std::string, 4> aktuellesFeld; // Array der Groesse 4 welches mit Strings der aktuellen Positionen der vier Spielfiguren gefuellt wird.
    std::array<int, 4> distance;              // Array der Groesse 4 welches mit Strings der Distanz der vier Spielfiguren gefuellt wird.

public:
    // Objektmanagement
    Player(int, std::string, std::array<std::string, 4>, std::array<std::string, 4>, std::array<int, 4>); // Konstruktor der Klasse Player
    ~Player();                                                                                            // Destruktor der Klasse Player

    // Getter der Klasse
    int get_identifier();
    std::string get_startingField();                 // Gibt das Startfeld-Array der Spieler-Instanz zurÅck
    std::array<std::string, 4> get_targetFields();   // Gibt die Zielfeld-Array der Spieler-Instanz zurÅck
    std::array<std::string, 4> &get_aktuellesFeld(); // Gibt das Array der aktuellen Felder der Spielfiguren der Player-Instanz zurueck
    std::array<int, 4> &get_distance();              // Gibt das Array der Distanzen der Spielfiguren der Player-Instanz zurueck

    // Debug
    void printData();               // REMOVE

    // Aktionen der Figuren
    int rollDice();                 // Methode, welche eine Zufallszahl zwischen eins und sechs zurueckgibt.
    int selectToken();              // Methode, welche den Benutzer eine Spielfigur auswaehlen laesst.
    int randomFromStorage();        // Methode, welche eine zufaellige Figur aus dem Lager auswaehlt und den Index dieser Figur zurueckgibt.
    int randomFromArena();          // Methode, welche eine zufaellige Figur aus dem Spielfeld auswaehlt und den Index dieser Figur zurueckgibt.

    // *Abfragen der Figuren*
    // Einzelabfragen
    bool tokenInStorage(int);       // ‹berpr¸ft, ob eine Figur am jeweiligen Index im Lager ist.
    bool tokenInArena(int);         // ‹berpr¸ft, ob eine Figur am jeweiligen Index auf dem Spielfeld ist.
    bool tokenInTargetField(int);   // ‹berpr¸ft, ob eine Figur am jeweiligen Index auf einem Zielfeld ist.

    // Gebuendelte Abfragen
    bool allTokenInStorage();       // ‹berpr¸ft, ob alle Spielfiguren im Lager sind
    bool allTokenInArena();         // ‹berpr¸ft, ob alle Spielfiguren auf dem Spielfeld sind
    bool allTokenInTargetField();   // ‹berpr¸ft, ob alle Spielfiguren im Ziel sind

    // Vorraussetzungen
    bool minOneInStorage();         // Uberprueft, ob mindestens eine Spielfigur im Lager ist.
    bool minOneInArena();           // Uberprueft, ob mindestens eine Spielfigur im Spielfeld ist.
    bool minOneInTargetField();     // Uberprueft, ob mindestens eine Spielfigur im Ziel ist.
};