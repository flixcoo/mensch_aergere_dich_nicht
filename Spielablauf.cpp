#include <iostream>
#include <string>
#include <vector>
#include <array>

#include "Spieler.hpp"
#include "Spielfeld.hpp"
#include "Spielablauf.hpp"

void Spielablauf::EineRunde(Spieler SpielerObj1, Spieler SpielerObj2, Spieler SpielerObj3, Spieler SpielerObj4, Spielfeld SpielfeldObj) // Jeder Spieler ist einmal am Zug
{
    int Wuerfelzahl = SpielerObj1.Wuerfeln();
    Spielzug(Wuerfelzahl, SpielerObj1, SpielerObj2, SpielerObj3, SpielerObj4, SpielfeldObj); // Runde von Spieler 1

    int Wuerfelzahl = SpielerObj2.Wuerfeln();
    Spielzug(Wuerfelzahl, SpielerObj2, SpielerObj3, SpielerObj4, SpielerObj1, SpielfeldObj); // Runde von Spieler 2

    int Wuerfelzahl = SpielerObj3.Wuerfeln();
    Spielzug(Wuerfelzahl, SpielerObj3, SpielerObj4, SpielerObj1, SpielerObj2, SpielfeldObj); // Runde von Spieler 3

    int Wuerfelzahl = SpielerObj4.Wuerfeln();
    Spielzug(Wuerfelzahl, SpielerObj4, SpielerObj1, SpielerObj2, SpielerObj3, SpielfeldObj); // Runde von Spieler 4
}

void Spielablauf::Spielzug(int Wuerfelzahl, Spieler SpielerObj1, Spieler SpielerObj2, Spieler SpielerObj3, Spieler SpielerObj4, Spielfeld SpielfeldObj) // Zug fuer jeweils einen Spieler und seine Gegner
{
    
    if (Wuerfelzahl == 6) // 6 Gewuerfelt
    {
        std::cout << "Wuerfelzahl: 6" << std::endl;
        if (SpielerObj1.MindestensEineImLager()) // 6 gewuerfelt && alle sind im Lager
        {
            std::cout << "Es ist mindestens eine Figur im Lager." << std::endl;
            int FigurIndex = SpielerObj1.ZufaelligerAusLager();
            FigurBewegen(Wuerfelzahl, FigurIndex, SpielerObj1, SpielerObj2, SpielerObj3, SpielerObj4, SpielfeldObj);
        }
        else // 6 Gewuerfelt && keiner ist im Lager
        {
            std::cout << "Es ist keine Figur im Lager." << std::endl;
            if(FigurenBewegbar(Wuerfelzahl, SpielerObj1, SpielfeldObj))
            {
                std::cout << "Es ist ist mindestens eine Figur bewegbar." << std::endl << std::endl;
                int FigurIndex = SpielerObj1.FigurAussuchen();
                FigurBewegen(Wuerfelzahl, FigurIndex, SpielerObj1, SpielerObj2, SpielerObj3, SpielerObj4, SpielfeldObj);
            }
            else
            {
                std::cout << "Es ist keine Figur bewegbar" << std::endl << std::endl;
                return;
            }
            
        }
    }
    else if (SpielerObj1.AlleFigurenImLager()) // Keine 6 gewuerfelt & alle sind im Lager
    {
        std::cout << "Wuerfelzahl: " << Wuerfelzahl << std::endl;
        std::cout << "Alle deiner Figuren sind noch im Lager." << std::endl;
        int Versuche = 2;
        for (int i = 0; i >= Versuche; i++)
        {
            std::cout << "Da du keine 6 gewuerfelt hast, darfst du noch " << Versuche << " mal wuerfeln." << std::endl;
            int Wuerfelzahl = SpielerObj1.Wuerfeln();
            if (Wuerfelzahl == 6)
            {
                std::cout << "Du hast jetzt endlich eine "<< Wuerfelzahl << " gewuerfelt" << std::endl;
                Spielzug(6, SpielerObj1, SpielerObj2, SpielerObj3, SpielerObj4, SpielfeldObj);
                std::cout << "[system]: break" << std::endl << std::endl;
                break;
            }
        }
    }
    else if (SpielerObj1.MindestensEineImSpielfeld() || SpielerObj1.MindestensEineImZiel()) // Keine 6 gewuerfelt & mindestens einen im Spielfeld
    {
        std::cout << "Du hast mindestens einen Spieler im Spielfeld." << std::endl;
        if(FigurenBewegbar(Wuerfelzahl, SpielerObj1, SpielfeldObj))
        {
            std::cout << "Du hast bewegbare Figuren." << std::endl << std::endl;
            int FigurIndex = SpielerObj1.FigurAussuchen();
            FigurBewegen(Wuerfelzahl, FigurIndex, SpielerObj1, SpielerObj2, SpielerObj3, SpielerObj4, SpielfeldObj);
        }
        else
        {
            std::cout << "Kein Spieler Bewegbar" << std::endl << std::endl;
            return;
        }
            
    }
    else //Wird zu dem dadrueber
    {
        std::cout << "[error]: common knowledge debugger triggered" << std::endl << std::endl;
    }
}

void Spielablauf::FigurBewegen(int Wuerfelzahl, int FigurIndex, Spieler SpielerObj1, Spieler SpielerObj2, Spieler SpielerObj3, Spieler SpielerObj4, Spielfeld SpielfeldObj) // Bewegung der Figur
{
    int SFI = BestimmeStartfeldIndex(FigurIndex, SpielerObj1, SpielfeldObj);
    std::cout << "StartfeldIndex ist " << SFI << std::endl;
    int NFI = SFI + Wuerfelzahl; // Index des neuen Feldes auf Spielbrett, ergibt sich aus dem Index des Feldes wo man gestartet ist  (SFI) + der Wuerfelzahl
    std::cout << "NeuerFeldIndex ist " << NFI << std::endl << std::endl;
    if(UeberSpielfeldendeHinaus(NFI, FigurIndex, SpielerObj1, SpielfeldObj) != NFI) //Korrektur NFI
    {
        std::cout << "Du bist ueber das Spielfeld hinaus." << std::endl;
        NFI = UeberSpielfeldendeHinaus(NFI, FigurIndex, SpielerObj1, SpielfeldObj);
        std::cout << "Der NeuerFeldIndex ist nun " << NFI << std::endl << std::endl;
    }
    
    if(UebersZielHinaus(Wuerfelzahl, FigurIndex, SpielerObj1, SpielfeldObj) ) //Bin ich ueber das Ziel hinaus?
    {
        std::cout << "Du bist ueber das Ziel hinaus." << std::endl;
        int FigurIndex = SpielerObj1.FigurAussuchen();
        FigurBewegen( Wuerfelzahl, FigurIndex, SpielerObj1, SpielerObj2, SpielerObj3, SpielerObj4, SpielfeldObj);
        std::cout << "[system]: break" << std::endl << std::endl;
        return;
    }
     
    if(EigeneFigurAufNeuemFeld(FigurIndex, NFI, SpielerObj1, SpielfeldObj) != FigurIndex) //Ist eine Figur auf dem neuen Feld?
    {
        std::cout << "Deine eigene Figur steht auf dem Feld auf das du willst " << std::endl << std::endl;
        SpielerObj1.FigurAussuchen();
        FigurBewegen( Wuerfelzahl, FigurIndex, SpielerObj1, SpielerObj2, SpielerObj3, SpielerObj4, SpielfeldObj);
        std::cout << "[system]: break" << std::endl << std::endl;
        return;
    }
    
    std::string NeuesFeld = SpielfeldObj.get_Spielbrett().at(NFI); // Das neue Feld wird aus dem Spielbrett gelesen
    std::cout << "Das neue Feld ist nun " << NeuesFeld << std::endl << std::endl;

    SpielerObj1.get_aktuellesFeld().at(FigurIndex) = NeuesFeld; //Das neue Feld wird der Figur im Array zugewiesen

    std::cout << "Stimmt " << NeuesFeld << " mit " << SpielerObj1.get_aktuellesFeld().at(FigurIndex) << "ueberein?" << std::endl << std::endl;
    SpielerObj1.get_Distanz().at(FigurIndex) += Wuerfelzahl; //Die Distanz wird erhˆht
    std::cout << "Die Distanz ist nun " << SpielerObj1.get_Distanz().at(FigurIndex) << std::endl << std::endl;
}

bool Spielablauf::FigurenBewegbar(int Wuerfelzahl,  Spieler SpielerObj1, Spielfeld SpielfeldObj) //Sind die Figuren eines Spielers bewegbar
{
    for(int FigurIndex = 0; FigurIndex < SpielerObj1.get_aktuellesFeld().max_size();FigurIndex++)
    {
        int SFI = BestimmeStartfeldIndex(FigurIndex, SpielerObj1, SpielfeldObj);
        int NFI = SFI + Wuerfelzahl; // Index des neuen Feldes auf Spielbrett, ergibt sich aus dem Index des Feldes wo man gestartet ist  (SFI) + der Wuerfelzahl

        if(UeberSpielfeldendeHinaus(NFI, FigurIndex, SpielerObj1, SpielfeldObj) != NFI) //Ist die Figur
        {
            NFI = UeberSpielfeldendeHinaus(NFI, FigurIndex, SpielerObj1, SpielfeldObj);
        }
        
        if(UebersZielHinaus(Wuerfelzahl, FigurIndex, SpielerObj1, SpielfeldObj) )
        {
            if(EigeneFigurAufNeuemFeld(FigurIndex, NFI, SpielerObj1, SpielfeldObj) == FigurIndex)
            {
                return true;        
            }     
        }   
    }
    return false;
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

int Spielablauf::UeberSpielfeldendeHinaus(int NFI, int FigurIndex, Spieler SpielerObj1, Spielfeld SpielfeldObj) // Ueberpr¸ft, ob ich ¸ber das Spielfeldarray hinaus bin
{
    if ((unsigned int)NFI >= SpielfeldObj.get_Spielbrett().max_size()) // Ist mein FigurIndex groesser als mein Spielfeld
    {
        NFI = -SpielfeldObj.get_Spielbrett().max_size();   // Groesse des Spielbrettes wird vom Index abgezogen
        
        return NFI;                                             // Das neues Feld, welches nun nicht mehr auﬂerhalb des Arrays Spielbrett ist, wird zurueckgegeben
    }
    else
    {
        return NFI; // Das neue Feld liegt im Array, also wird es einfach zurueckgegeben.
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

int Spielablauf::EigeneFigurAufNeuemFeld(int FigurIndex, int NFI, Spieler SpielerObj1, Spielfeld SpielfeldObj) // Ueberprueft, ob eine Figur des aktuellen Spielers auf dem neuen Feld steht
{
    std::string NeuesFeld = SpielfeldObj.get_Spielbrett().at(NFI);
    for (unsigned int i = 0; i < SpielerObj1.get_aktuellesFeld().max_size(); i++)
    {
        if (SpielerObj1.get_aktuellesFeld().at(i) == NeuesFeld)
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

int Spielablauf::BestimmeStartfeldIndex(int FigurIndex, Spieler SpielerObj, Spielfeld SpielfeldObj) // Bestimmt den Index auf dem Array Spielbrett, an welcher sich das Startfeld des eingegebenen Spielers befindet.
{
    int SFI;                                 // StartFeldIndex, Zahl zum rechnen
    if (SpielerObj.FigurImLager(FigurIndex)) // Wenn das aktuelle Feld der Figur "X" ist
    {
        for (int i = 0; i < SpielfeldObj.get_Spielbrett().max_size(); i++) // Gehe das Spielfeld durch
        {
            if (SpielfeldObj.get_Spielbrett().at(i) == SpielerObj.get_Startfeld()) // Ueberpruefe, ob das Feld an Index i gleich dem Startfeld des Spielers ist
            {
                return i; // Wenn ja, gib den Index vom Startfeld zurueck
            }
        }
    }
    else // Wenn das aktuelle Feld der Figur nicht "X" ist
    {
        for (int i = 0; i < SpielfeldObj.get_Spielbrett().max_size(); i++) // Gehe das Spielfeld durch
        {
            if (SpielfeldObj.get_Spielbrett().at(i) == SpielerObj.get_aktuellesFeld().at(FigurIndex)) // Ueberpruefe, ob das Feld an Index i gleich dem aktuellen Feld des Spielers ist
            {
                return i; // Wenn ja, gib den index dieses Feldes zurueck
            }
        }
    }
    std::cout << "[error]: Startfeld der Figur " << FigurIndex << " konnte nicht gefunden werden." << std::endl;
    return NULL;
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