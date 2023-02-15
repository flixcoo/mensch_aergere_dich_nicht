#include <iostream>
#include <string>
#include <vector>
#include <array>

class PlayingField; // Vorher Bekanntmachung fuer Klasse Spielablauf
class Player;       // Vorher Bekanntmachung fuer Klasse Spielablauf

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
    void EineRunde(Player &, Player &, Player &, Player &, PlayingField &);             // Methode fuehrt viermal die Methode "Spielzug" aus, jeweils mit einem anderen Spieler am Zug.
    void SpielfeldDrucken(Player &, Player &, Player &, Player &, PlayingField &);
    void Spielzug(int, Player &, Player &, Player &, Player &, PlayingField &);          // Methode welche einen Spielzug mit einem aktiven  Spieler und drei passiven Spielern darstellt.
    void FigurBewegen(int, int, Player &, Player &, Player &, Player &, PlayingField &); // Methode, welche eine Figur bewegt und jedwede Korrekturen und Abfragen enthaelt.
    bool SpielEnde(Player &, Player &, Player &, Player &);

    // Korrekturen
    void SpielerAufNeuemFeld(int, Player &, Player &, Player &, Player &, PlayingField &); // Methode, welche prueft, ob sich ein Spieler auf dem neuen Feld befindet und ihn zurueck ins Lager setzt.
    int BestimmeStartfeldIndex(int, Player &, PlayingField &);                             // Bestimmt den Index des aktuellen Feldes einer Figur der dann als Startfeld verwendet wird.
    int InFremdemZielfeld(int, int, Player, Player, Player, Player, PlayingField);         // Falls man sich beim Bewegen in einem Zielfeld der anderen Spieler befinden wuerde, korrigiert diese Methode das neue Feld.
    int EigeneFigurAufNeuemFeld(int, int, Player &, PlayingField &);                       // Gibt den FigurenIndex der Figur zurueck, die auf dem neuen Feld steht. Falls keine dort steht, wird der Index der Figur die bewegt wird zurÅckgegeben.
    int UeberSpielfeldendeHinaus(int, int, Player &, PlayingField &);                      // Ueberprueft, ob das neue Feld im Array "board" drin ist. Wenn nicht, wird das neue Feld korrigiert, ansonsten wird das neue Feld einfahc zurueckgegeben.
    int SpielerAufStartfeld(int, Player &);                                                // Gibt den FigurenIndex der Figur zurueck, welche auf dem Startfeld steht. Wenn keine daraufsteht, wird der Index der aktuell bewegten Figur zurueckgegeben.
    int BestimmeIndexDesStartfelds(Player &, PlayingField &);                              // Methoode, welche den Index der Startfeld eines jeweiligen Spielers auf dem Spielbrett ausfindig macht und zurueckgibt.

    // Abfragen
    bool UebersZielHinaus(int, int, Player &, PlayingField &);                              // Ueberprueft, ob ein Spieler ueber seinen eigenen Zielfelder hinaus gehen wuerde und gibt dies als Wahrheitswert zurueck.
    bool FigurenBewegbar(int, Player &, PlayingField &);                                    // Ueberprueft, ob ein Spieler mit der aktuell gewuerfelten Zahl bewegbare Figuren hat
};
