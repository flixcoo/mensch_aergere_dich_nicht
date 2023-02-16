#include <iostream>

class Gameboard; // Vorher Bekanntmachung fuer Klasse Spielablauf
class Player;    // Vorher Bekanntmachung fuer Klasse Spielablauf

/**
 * @brief Die Klasse regelt den Ablauf des Spiels
 * Die Klasse hat nur Methoden, welche verschiedenste Spielverlaufe abdecken und ggf. Attribute der Spielerklasse korrigieren.
 * @author Felix Kirchner
 * @see Spieler
 */
class Gameplay
{
public:
    // Ablauf
    void playOneRound(Player &, Player &, Player &, Player &, Gameboard &);        // Methode, die eine Runde des Spiels ausfuehrt.
    void printBoard(Player &, Player &, Player &, Player &, Gameboard &);          // Methode, welche das Spielfeld mit den aktuellen Positionen der Spielfiguren in der Konsole ausgibt.
    void playersTurn(int, Player &, Player &, Player &, Player &, Gameboard &);    // Methode welche einen Spielzug mit einem aktiven  Spieler und drei passiven Spielern darstellt.
    void moveToken(int, int, Player &, Player &, Player &, Player &, Gameboard &); // Methode, welche die Spielfigur bewegt und dabei alle Faelle und Situationen beachtet.
    bool endOfGame(Player &, Player &, Player &, Player &);                        // Methode, die fuer alle vier Spieler ueberorueft, ob mindestens einer von ihnen alle Spielfiguren in den Zielfeldern hat.
    int winner(Player &, Player &, Player &, Player &);                            // Methode, die das "identifier"-Attribut des Spielers zurueckgibt, der gewonnen hat.

    // Korrekturen
    void playerOnNewField(int, Player &, Player &, Player &, Player &, Gameboard &);    // Methode, welche prueft, ob sich ein Spieler auf dem neuen Feld befindet und ihn zurueck ins Lager setzt.
    int determineStartingFieldIndex(int, Player &, Gameboard &);                        // Methode, welche den Index des aktuellen Feldes einer Figur, der dann als Startfeld verwendet wird, bestimmt.
    int inForeignTargetField(int, Player &, Player &, Player &, Player &, Gameboard &); // Methode, welche ueberprueft, ob ein Spieler in einem der Zielfelder der anderen Spieler gelandet ist.
    int ownTokenOnNewField(int, int, Player &, Gameboard &);                            // Methode, welche auf eigene Spieler auf dem neuen Feld ueberprueft.
    int beyondGameboard(int, Gameboard &);                                              // Methode, welche ueberprueft, ob ein Spieler ueber das Spielbrett hinaus gegangen ist.
    int determineIndexOfStartingField(Player &, Gameboard &);                           // Methode, welche den Index des aktuellen Feldes einer Figur, der dann als Startfeld verwendet wird, bestimmt.

    // Abfragen
    bool beyondTargetField(int, int, Player &, Gameboard &); // Methode, die ueberprueft, ob eine Spielfigur ueber ihre Zielfelder hinaus gelaufen ist.
    bool tokenMovable(int, Player &, Gameboard &);           // Methode, die ueberprueft, ob ein Spieler mit der aktuell gewuerfelten Zahl bewegbare Figuren hat
    bool isTargetField(int, Player &, Gameboard &);          // Methode, welche untersucht, ob das Feld an FieldIndex ein Zielfeld vom Player-Objekt ist.
};
