/**
 * \brief Kurzbeschreibung der Klasse
 *
 *
 * AusfÅhrliche Beschreibung der FunktionalitÑt
 * der Klasse und allem, was dazu gehîrt.
 *
 * @author Autor der Klasse
 * @see Verweis auf andere Klasse, die im Bezug steht.
 */

#include <iostream>
#include <string>
#include <vector>
#include <array>

class Spielfeld; // Vorher Bekanntmachung fuer Klasse Spielablauf
class Spieler;   // Vorher Bekanntmachung fuer Klasse Spielablauf

class Spielablauf
{
public:
    void EineRunde(Spieler, Spieler, Spieler, Spieler, Spielfeld);
    void Spielzug(int, Spieler, Spieler, Spieler, Spieler, Spielfeld);
    int BestimmeStartfeldIndex(int, Spieler, Spielfeld); //Bestimmt den Index des aktuellen Feldes einer Figur

    bool SpielEnde(Spieler, Spieler, Spieler, Spieler);

    void FigurBewegen(int, int, Spieler, Spieler, Spieler, Spieler, Spielfeld);

    void SpielerAufNeuemFeld(std::string, Spieler, Spieler, Spieler, Spieler, Spielfeld);
    std::string InFremdemZielfeld(int, int, int, std::string, Spieler, Spieler, Spieler, Spieler, Spielfeld); // Falls man sich in einem Fremden Zielfeld befindet, wird auf das Feld 4 draufgerechnet. Ansonsten wird das Feld zurueckgegeben, welches der Funktion uebergeben wurde.
    int EigeneFigurAufNeuemFeld(int, int, Spieler, Spielfeld);                                                   // Gibt den FigurenIndex der Figur zurueck, die auf dem neuen Feld steht. Falls keine dort steht, wird der Index der Figur die bewegt wird zurÅckgegeben.
    int UeberSpielfeldendeHinaus(int, int, Spieler, Spielfeld);                          // Ueberprueft, ob das neue Feld im Array "Spielbrett" drin ist. Wenn nicht, wird das neue Feld korrigiert, ansonsten wird das neue Feld einfahc zurueckgegeben.
    bool UebersZielHinaus(int, int, Spieler, Spielfeld);
    int SpielerAufStartfeld(int, Spieler); // Gibt den FigurenIndex der Figur zurueck, welche auf dem Startfeld steht. Wenn keine daraufsteht = "-1"
    bool Spielablauf::FigurenBewegbar(int, Spieler, Spielfeld);
};
