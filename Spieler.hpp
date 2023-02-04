/**
 * \brief Kurzbeschreibung der Klasse
 *
 *
 * Ausf�hrliche Beschreibung der Funktionalit�t
 * der Klasse und allem, was dazu geh�rt.
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
    int Kennzeichner;
    std::string Lager;                        // String dem die Zahl des Lagers ("X") zugewissen wird.
    std::string Startfeld;                    // String dem das Startfeld des Spielers zugewiesen wird.
    std::array<std::string, 4> Zielfelder;    // Array der Groesse 4 welches mit Strings der vier Zielfelder gefuellt wird.
    std::array<std::string, 4> aktuellesFeld; // Array der Groesse 4 welches mit Strings der aktuellen Positionen der vier Spielfiguren gefuellt wird.
    std::array<int, 4> Distanz;               // Array der Groesse 4 welches mit Strings der aktuellen Positionen der vier Spielfiguren gefuellt wird.

public:
    Spieler(int, std::string, std::array<std::string, 4>, std::array<std::string, 4>, std::array<int, 4>); // Konstruktor der Klasse Spieler
    ~Spieler();                                                                                       // Destruktor der Klasse Spieler

    // Getter der Klasse
    int get_Kennzeichner();
    std::string get_Startfeld();                    // Gibt das Startfeld der Spieler-Instanz zur�ck
    std::array<std::string, 4> get_Zielfelder();    // Gibt die Zielfelder der Spieler-Instanz zur�ck
    std::array<std::string, 4> & get_aktuellesFeld(); // Gibt das Array der aktuellen Felder der Spielfiguren der Spieler-Instanz zurueck
    std::array<int, 4> & get_Distanz();               // Gibt das Array der Distanzen der Spielfiguren der Spieler-Instanz zurueck

    // Debug
    void DatenAusgabe();

    // Aktionen des Figuren
    int Wuerfeln();
    int FigurAussuchen();
    int ZufaelligerAusLager();
    int ZufaelligerAusFeld();


    // Abfragen der Figuren
    bool FigurImLager(int);      // �berpr�ft, ob eine Figur am jeweiligen Index im Lager ist.
    bool FigurAufSpielfeld(int); // �berpr�ft, ob eine Figur am jeweiligen Index auf dem Spielfeld ist.
    bool FigurImZiel(int);       // �berpr�ft, ob eine Figur am jeweiligen Index auf einem Zielfeld ist.

    bool AlleFigurenImLager();      // �berpr�ft, ob alle Spielfiguren im Lager sind
    bool AlleFigurenAufSpielfeld(); // �berpr�ft, ob alle Spielfiguren auf dem Spielfeld sind
    bool AlleFigurenImZiel();       // �berpr�ft, ob alle Spielfiguren im Ziel sind

    bool MindestensEineImLager(); //Uberprueft, ob mindestens eine Spielfigur im Lager ist.
    bool MindestensEineImSpielfeld(); //Uberprueft, ob mindestens eine Spielfigur im Lager ist.
    bool MindestensEineImZiel();
};