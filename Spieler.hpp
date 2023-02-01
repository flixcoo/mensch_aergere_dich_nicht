/**
 * \brief Kurzbeschreibung der Klasse
 *
 *
 * Ausführliche Beschreibung der Funktionalität
 * der Klasse und allem, was dazu gehört.
 *
 * @author Autor der Klasse
 * @see Verweis auf andere Klasse, die im Bezug steht.
 */

#include <iostream>
#include <string>
#include <vector>
#include <array>

class Spieler
{
private:
    std::string Lager;                        // String dem die Zahl des Lagers ("X") zugewissen wird.
    std::string Startfeld;                    // String dem das Startfeld des Spielers zugewiesen wird.
    std::array<std::string, 4> Zielfelder;    // Array der Groesse 4 welches mit Strings der vier Zielfelder gefuellt wird.
    std::array<std::string, 4> aktuellesFeld; // Array der Groesse 4 welches mit Strings der aktuellen Positionen der vier Spielfiguren gefuellt wird.
    std::array<int, 4> Distanz;               // Array der Groesse 4 welches mit Strings der aktuellen Positionen der vier Spielfiguren gefuellt wird.

public:
    Spieler(std::string, std::array<std::string, 4>, std::array<std::string, 4>, std::array<int, 4>); // Konstruktor der Klasse Spieler
    ~Spieler();                                                                                       // Destruktor der Klasse Spieler

    // Getter der Klasse
    std::string get_Startfeld();                    // Gibt das Startfeld der Spieler-Instanz zurck
    std::array<std::string, 4> get_Zielfelder();    // Gibt die Zielfelder der Spieler-Instanz zurck
    std::array<std::string, 4> get_aktuellesFeld(); // Gibt das Array der aktuellen Felder der Spielfiguren der Spieler-Instanz zurueck
    std::array<int, 4> get_Distanz();               // Gibt das Array der Distanzen der Spielfiguren der Spieler-Instanz zurueck

    // Debug
    void DatenAusgabe();

    // Aktionen des Figuren
    int Wuerfeln();
    int ZufaelligerAusLager();
    int ZufaelligerAusFeld();

    // Abfragen der Figuren
    bool FigurImLager(int);      // Überprüft, ob eine Figur am jeweiligen Index im Lager ist.
    bool FigurAufSpielfeld(int); // Überprüft, ob eine Figur am jeweiligen Index auf dem Spielfeld ist.
    bool FigurImZiel(int);       // Überprüft, ob eine Figur am jeweiligen Index auf einem Zielfeld ist.

    bool AlleFigurenImLager();      // Überprüft, ob alle Spielfiguren im Lager sind
    bool AlleFigurenAufSpielfeld(); // Überprüft, ob alle Spielfiguren auf dem Spielfeld sind
    bool AlleFigurenImZiel();       // Überprüft, ob alle Spielfiguren im Ziel sind
};