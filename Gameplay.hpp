#include <iostream>
#include <string>
#include <vector>
#include <array>

class Gameboard; // Vorher Bekanntmachung fuer Klasse Spielablauf
class Player;    // Vorher Bekanntmachung fuer Klasse Spielablauf

/**
 * @brief Kurzbeschreibung der Klasse
 * Ausfuehrliche Beschreibung der Funktionalitaet.
 *
 * @author Felix Kirchner
 * @see Spieler
 */
class Spielablauf
{
public:
    // Ablauf
    void playOneRound(Player &, Player &, Player &, Player &, Gameboard &); // Methode fuehrt viermal die Methode "Spielzug" aus, jeweils mit einem anderen Spieler am Zug.
    void printBoard(Player &, Player &, Player &, Player &, Gameboard &);
    void PlayersTurn(int, Player &, Player &, Player &, Player &, Gameboard &);    // Methode welche einen Spielzug mit einem aktiven  Spieler und drei passiven Spielern darstellt.
    void MoveToken(int, int, Player &, Player &, Player &, Player &, Gameboard &); // Methode, welche eine Figur bewegt und jedwede Korrekturen und Abfragen enthaelt.
    bool endOfGame(Player &, Player &, Player &, Player &);

    // Korrekturen
    void playerOnNewField(int, Player &, Player &, Player &, Player &, Gameboard &); // Methode, welche prueft, ob sich ein Spieler auf dem neuen Feld befindet und ihn zurueck ins Lager setzt.
    int determineStartingFieldIndex(int, Player &, Gameboard &);                     // Bestimmt den Index des aktuellen Feldes einer Figur der dann als Startfeld verwendet wird.
    int inForeignTargetField(int, int, Player, Player, Player, Player, Gameboard);   // Falls man sich beim Bewegen in einem Zielfeld der anderen Spieler befinden wuerde, korrigiert diese Methode das neue Feld.
    int ownTokenOnNewField(int, int, Player &, Gameboard &);                         // Gibt den FigurenIndex der Figur zurueck, die auf dem neuen Feld steht. Falls keine dort steht, wird der Index der Figur die bewegt wird zurÅckgegeben.
    int beyondGameboard(int, int, Player &, Gameboard &);                            // Ueberprueft, ob das neue Feld im Array "board" drin ist. Wenn nicht, wird das neue Feld korrigiert, ansonsten wird das neue Feld einfahc zurueckgegeben.
    int PlayerOnStartingField(int, Player &);                                        // Gibt den FigurenIndex der Figur zurueck, welche auf dem Startfeld steht. Wenn keine daraufsteht, wird der Index der aktuell bewegten Figur zurueckgegeben.
    int DetermineIndexOfStartingField(Player &, Gameboard &);                        // Methoode, welche den Index der Startfeld eines jeweiligen Spielers auf dem Spielbrett ausfindig macht und zurueckgibt.

    // Abfragen
    bool beyondTargetField(int, int, Player &, Gameboard &); // Ueberprueft, ob ein Spieler ueber seinen eigenen Zielfelder hinaus gehen wuerde und gibt dies als Wahrheitswert zurueck.
    bool FigurenBewegbar(int, Player &, Gameboard &);        // Ueberprueft, ob ein Spieler mit der aktuell gewuerfelten Zahl bewegbare Figuren hat
};
