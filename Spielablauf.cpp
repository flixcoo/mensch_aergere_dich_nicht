#include <iostream>
#include <string>
#include <vector>
#include <array>

#include "Spieler.hpp"
#include "Spielfeld.hpp"
#include "Spielablauf.hpp"

void Spielablauf::EineRunde(Spieler SpielerObj1, Spieler SpielerObj2, Spieler SpielerObj3, Spieler SpielerObj4, Spielfeld SpielfeldObj) // Jeder Spieler ist einmal am Zug
{
    Spielzug(SpielerObj1, SpielerObj2, SpielerObj3, SpielerObj4, SpielfeldObj); // Runde von Spieler 1
    Spielzug(SpielerObj2, SpielerObj3, SpielerObj4, SpielerObj1, SpielfeldObj); // Runde von Spieler 2
    Spielzug(SpielerObj3, SpielerObj4, SpielerObj1, SpielerObj2, SpielfeldObj); // Runde von Spieler 3
    Spielzug(SpielerObj4, SpielerObj1, SpielerObj2, SpielerObj3, SpielfeldObj); // Runde von Spieler 4
}

void Spielablauf::Spielzug(Spieler SpielerObj1, Spieler SpielerObj2, Spieler SpielerObj3, Spieler SpielerObj4, Spielfeld SpielfeldObj) // Zug fÅr jeweils einen Spieler und seine Gegner
{
    /*int Wuerfelzahl = SpielerObj1.Wuerfeln();
    if(Wuerfelzahl ==6)
    {
        if(SpielerObj1.AlleFigurenAufSpielfeld())
        {
            int FigurIndex = SpielerObj1.ZufaelligerAusLager();   //Index der Spielfigure im Array aktuellesFeld
            int SFI = BestimmeStartfeldIndex(SpielerObj1,SpielfeldObj); //Index an welchem Sie das Startfeld im Array Spielbrett befindert
            FigurBewegen(Wuerfelzahl, SFI, FigurIndex,SpielerObj1, SpielerObj2, SpielerObj3, SpielerObj4, SpielfeldObj);
        }
        else if(!SpielerObj1.AlleFigurenAufSpielfeld() && )//
        {

        }
    }
    else
    {

    }*/
}

void Spielablauf::FigurBewegen(int Wuerfelzahl, int SFI, int FigurIndex, Spieler SpielerObj1, Spieler SpielerObj2, Spieler SpielerObj3, Spieler SpielerObj4, Spielfeld SpielfeldObj) // Bewegung der Figur
{
    int NeuesFeldIndex = SFI + Wuerfelzahl;                                   // Index des neuen Feldes auf Spielbrett, ergibt sich aus dem Index des Feldes wo man gestartet ist  (SFI) + der Wuerfelzahl
    std::string NeuesFeld = SpielfeldObj.get_Spielbrett().at(NeuesFeldIndex); // Das neue Feld wird aus dem Spielbrett gelesen

    UeberSpielfeldendeHinaus(NeuesFeldIndex, FigurIndex, NeuesFeld, SpielerObj1, SpielfeldObj);
    InFremdemZielfeld(Wuerfelzahl, SFI, NeuesFeldIndex, NeuesFeld, SpielerObj1, SpielerObj2, SpielerObj3, SpielerObj4, SpielfeldObj); // Bin ich in einem Zielfeld gelandet?
    SpielerAufNeuemFeld(NeuesFeld, SpielerObj1, SpielerObj2, SpielerObj3, SpielerObj4, SpielfeldObj);                                 // Ist ein anderer Spieler auf meinem neuen Feld?
    SpielerObj1.get_Distanz().at(FigurIndex) += Wuerfelzahl;                                                                          // Die Distanz wird erhoeht um die Wuerfelzahl.
    if (EigeneFigurAufNeuemFeld(FigurIndex, NeuesFeld, SpielerObj1) != FigurIndex)
    {
        int NewFigurIndex = EigeneFigurAufNeuemFeld(FigurIndex, NeuesFeld, SpielerObj1);
        FigurBewegen(Wuerfelzahl, SFI, NewFigurIndex, SpielerObj1, SpielerObj2, SpielerObj3, SpielerObj4, SpielfeldObj);
    }
    else
    {
        SpielerObj1.get_aktuellesFeld().at(FigurIndex) = NeuesFeld; // Das neue Feld wird der Spielfigur zugewiesen
    }
}

bool Spielablauf::UebersZielHinaus(int Wuerfelzahl, int FigurIndex, Spieler SpielerObj1, Spielfeld SpielfeldObj) // Schaut ob die gelaufene Distanz einer Figur groesser ist als 44 (zweite Runde) und uebergibt einen Wahrheitswert
{
    if ((SpielerObj1.get_Distanz().at(FigurIndex) + Wuerfelzahl > 44)) // Ist Figur an FigurIndex schon mehr als 44 Felder gelaufen?
    {
        return true; // Wenn ja, return true
    }
    else
    {
        return false; // wenn nein, return false
    }
}

int Spielablauf::SpielerAufStartfeld(int FigurIndex, Spieler SpielerObj1) // Ueberprueft, ob ein Spieler auf dem Startfeld steht und gibt die Figur zurueck, die beweg werden muss.
{
    for (unsigned int i = 0; i < SpielerObj1.get_aktuellesFeld().max_size(); i++) // Geht das AktuellesFeld Array durch
    {
        if (SpielerObj1.get_aktuellesFeld().at(i) == SpielerObj1.get_Startfeld()) // Spielfeld ist besetzt
        {
            return i; // Index von Spieler auf dem Startfeld, welche bewegt werden muss.
        }
    }
    return FigurIndex; // Index vom Urspr¸nglichen Spieler
}

std::string Spielablauf::UeberSpielfeldendeHinaus(int NeuesFeldIndex, int FigurIndex, std::string NeuesFeld, Spieler SpielerObj1, Spielfeld SpielfeldObj) // Ueberpr¸ft, ob ich ¸ber das Spielfeldarray hinaus bin
{
    if ((unsigned int)NeuesFeldIndex >= SpielfeldObj.get_Spielbrett().max_size()) // Ist mein FigurIndex groesser als mein Spielfeld
    {
        NeuesFeldIndex = -SpielfeldObj.get_Spielbrett().max_size();   // Groesse des Spielbrettes wird vom Index abgezogen
        NeuesFeld = SpielfeldObj.get_Spielbrett().at(NeuesFeldIndex); // Es wird das neue Feld herausgesucht
        return NeuesFeld;                                             // Das neues Feld, welches nun nicht mehr auﬂerhalb des Arrays Spielbrett ist, wird zurueckgegeben
    }
    else
    {
        return NeuesFeld; // Das neue Feld liegt im Array, also wird es einfach zurueckgegeben.
    }
}

std::string Spielablauf::InFremdemZielfeld(int Wuerfelzahl, int SFI, int NeuesFeldIndex, std::string NeuesFeld, Spieler SpielerObj1, Spieler SpielerObj2, Spieler SpielerObj3, Spieler SpielerObj4, Spielfeld SpielfeldObj) // Bin ich in einem fremden Zielfeld gelandet?
{
    for (unsigned int i = 0; i < SpielerObj2.get_Zielfelder().max_size(); i++)
    {
        if (SpielerObj2.get_Zielfelder().at(i) == NeuesFeld) // Ist das Neue Feld ein Zielfeld von Spieler2?
        {
            NeuesFeldIndex = SFI + Wuerfelzahl + 4;                       // Raus aus dem Bereich der Zielfelder von Spieler2
            NeuesFeld = SpielfeldObj.get_Spielbrett().at(NeuesFeldIndex); // NeuesFeld wird aktualisiert
        }
    }
    for (unsigned int i = 0; i < SpielerObj3.get_Zielfelder().max_size(); i++) // Ist das Neue Feld ein Zielfeld von Spieler3?
    {
        if (SpielerObj3.get_Zielfelder().at(i) == NeuesFeld)
        {
            NeuesFeldIndex = SFI + Wuerfelzahl + 4;                       // Raus aus dem Bereich der Zielfelder von Spieler3
            NeuesFeld = SpielfeldObj.get_Spielbrett().at(NeuesFeldIndex); // NeuesFeld wird aktualisiert
        }
    }
    for (unsigned int i = 0; i < SpielerObj4.get_Zielfelder().max_size(); i++) // Ist das Neue Feld ein Zielfeld von Spieler4?
    {
        if (SpielerObj4.get_Zielfelder().at(i) == NeuesFeld)
        {
            NeuesFeldIndex = SFI + Wuerfelzahl + 4;                       // Raus aus dem Bereich der Zielfelder von Spieler4
            NeuesFeld = SpielfeldObj.get_Spielbrett().at(NeuesFeldIndex); // NeuesFeld wird aktualisiert
        }
    }
    return NeuesFeld;
}

int Spielablauf::EigeneFigurAufNeuemFeld(int FigurIndex, std::string NeuesFeld, Spieler SpielerObj1) // Ueberprueft, ob eine Figur des aktuellen Spielers auf dem neuen Feld steht
{
    for (unsigned int i = 0; i < SpielerObj1.get_aktuellesFeld().max_size(); i++)
    {
        if (SpielerObj1.get_aktuellesFeld().at(i) == SpielerObj1.get_aktuellesFeld().at(FigurIndex))
        {
            if (i != (unsigned int)FigurIndex)
            {
                return i; // Wenn ja, gib den Index der Figur zurueck, welche dann stattdesssen bewegt werden muss.
            }
        }
    }
    return FigurIndex; // Wenn ja, gib den Index der Figur zurueck, welche wir gerade schon bewegen.
}

void Spielablauf::SpielerAufNeuemFeld(std::string NeuesFeld, Spieler SpielerObj1, Spieler SpielerObj2, Spieler SpielerObj3, Spieler SpielerObj4, Spielfeld SpielfeldObj) // Ist eine andere Spielfigur auf meinem neuen Feld?
{
    for (unsigned int i = 0; i < SpielerObj2.get_aktuellesFeld().max_size(); i++)
    {
        if (SpielerObj2.get_aktuellesFeld().at(i) == NeuesFeld) // Ist auf dem neuen Feld eine Figur von Spieler 2?
        {
            SpielerObj2.get_aktuellesFeld().at(i) = "X"; // Spieler wird rausgekickt (Position der Figur auf X fuer Lager)
            SpielerObj2.get_Distanz().at(i) = 0;         // Distanz der Spielfigur wird zurueckgesetzt.
        }
    }
    for (unsigned int i = 0; i < SpielerObj3.get_aktuellesFeld().max_size(); i++) // Ist auf dem neuen Feld eine Figur von Spieler 3?
    {
        if (SpielerObj3.get_aktuellesFeld().at(i) == NeuesFeld)
        {
            SpielerObj3.get_aktuellesFeld().at(i) = "X"; // Spieler wird rausgekickt (Position der Figur auf X fuer Lager)
            SpielerObj3.get_Distanz().at(i) = 0;         // Distanz der Spielfigur wird zurueckgesetzt.
        }
    }
    for (unsigned int i = 0; i < SpielerObj4.get_aktuellesFeld().max_size(); i++) // Ist auf dem neuen Feld eine Figur von Spieler 4?
    {
        if (SpielerObj4.get_aktuellesFeld().at(i) == NeuesFeld)
        {
            SpielerObj4.get_aktuellesFeld().at(i) = "X"; // Spieler wird rausgekickt (Position der Figur auf X fÅr Lager).
            SpielerObj4.get_Distanz().at(i) = 0;         // Distanz der Spielfigur wird zurueckgesetzt.
        }
    }
}

int Spielablauf::BestimmeStartfeldIndex(Spieler SpielerObj, Spielfeld SpielfeldObj) // Bestimmt den Index auf dem Array Spielbrett, an welcher sich das Startfeld des eingegebenen Spielers befindet.
{
    int StartfeldIndex = -1;
    for (unsigned int i = 0; i < SpielfeldObj.get_Spielbrett().max_size(); i++)
    {
        if (SpielfeldObj.get_Spielbrett().at(i) == SpielerObj.get_Startfeld())
        {
            StartfeldIndex = i;
        }
    }
    return StartfeldIndex;
}

bool Spielablauf::SpielEnde(Spieler SpielerObj1, Spieler SpielerObj2, Spieler SpielerObj3, Spieler SpielerObj4) // Ueberprueft, ob mindestens ein Spieler alle Figuren im Ziel hat.
{
    if ((SpielerObj1.AlleFigurenImZiel() || SpielerObj2.AlleFigurenImZiel()) || (SpielerObj3.AlleFigurenImZiel() || SpielerObj4.AlleFigurenImZiel()))
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * \brief Kurzbeschreibung
 *
 * Langbeschriebung
 * @param parameter1 Funktion des Parameters 1
 * @param parameter2 Funktion des Parameters 2
 * @see Referenz auf andere Funktion, die ‰hnliches macht oder dazu gehˆrt
 * @return Beschreibung des R¸ckgabewertes
 * @pre Bedingungen, die vor dem Aufruf der Funktion erf¸llt sein m¸ssen
 * @post Bedingungen, die nach dem Aufruf der Funktion erf¸llt sind
 * @since Wann die Funktion eingef¸hrt wurde
 * @author Autor der Funktion
 */
