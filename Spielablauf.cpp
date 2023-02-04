#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <iomanip>

#include "Spieler.hpp"
#include "Spielfeld.hpp"
#include "Spielablauf.hpp"

void Spielablauf::EineRunde(Spieler &SpielerObj1, Spieler &SpielerObj2, Spieler &SpielerObj3, Spieler &SpielerObj4, Spielfeld &SpielfeldObj) // Jeder Spieler ist einmal am Zug
{
    std::cout << "[EineRunde]: Spieler 1 ist an der Reihe, bitte bestaetige mit einer Taste." << std::endl;
    std::cin.ignore();
    int Wuerfelzahl;
    SpielfeldDrucken(SpielerObj1, SpielerObj2, SpielerObj3, SpielerObj4, SpielfeldObj);
    std::cout << "--------- Spieler 1 ---------" << std::endl;

    Wuerfelzahl = SpielerObj1.Wuerfeln();
    Spielzug(Wuerfelzahl, SpielerObj1, SpielerObj2, SpielerObj3, SpielerObj4, SpielfeldObj); // Runde von Spieler 1

    std::cout << "[EineRunde]: Dein Zug ist beendet, Spieler 2 bestaetige mit einer Taste." << std::endl;
    std::cin.ignore();
    SpielfeldDrucken(SpielerObj2, SpielerObj3, SpielerObj4,SpielerObj1, SpielfeldObj);
    std::cout << "--------- Spieler 2 ---------" << std::endl;

    Wuerfelzahl = SpielerObj2.Wuerfeln();
    Spielzug(Wuerfelzahl, SpielerObj2, SpielerObj3, SpielerObj4, SpielerObj1, SpielfeldObj); // Runde von Spieler 2

    std::cout << "[EineRunde]: Dein Zug ist beendet, Spieler 3 bestaetige mit einer Taste." << std::endl;
    std::cin.ignore();
    SpielfeldDrucken(SpielerObj3, SpielerObj4, SpielerObj1, SpielerObj2, SpielfeldObj);
    std::cout << "--------- Spieler 3 ---------" << std::endl;

    Wuerfelzahl = SpielerObj3.Wuerfeln();
    Spielzug(Wuerfelzahl, SpielerObj3, SpielerObj4, SpielerObj1, SpielerObj2, SpielfeldObj); // Runde von Spieler 3

    std::cout << "[EineRunde]: Dein Zug ist beendet, Spieler 4 bestaetige mit einer Taste." << std::endl;
    std::cin.ignore(); 
    SpielfeldDrucken( SpielerObj4, SpielerObj1, SpielerObj2, SpielerObj3,SpielfeldObj);
    std::cout << "--------- Spieler 4 ---------" << std::endl;

    Wuerfelzahl = SpielerObj4.Wuerfeln();
    Spielzug(Wuerfelzahl, SpielerObj4, SpielerObj1, SpielerObj2, SpielerObj3, SpielfeldObj); // Runde von Spieler 4
   
    SpielfeldDrucken(SpielerObj1, SpielerObj2, SpielerObj3, SpielerObj4, SpielfeldObj);
}

void Spielablauf::Spielzug(int Wuerfelzahl, Spieler &SpielerObj1, Spieler &SpielerObj2, Spieler &SpielerObj3, Spieler &SpielerObj4, Spielfeld &SpielfeldObj) // Zug fuer jeweils einen Spieler und seine Gegner
{
    
    if (Wuerfelzahl == 6) // 6 Gewuerfelt
    {
        std::cout << "[Spielzug]: Du hast eine 6 gewuerfelt! nice" << std::endl;
        std::cin.ignore();
        if (SpielerObj1.MindestensEineImLager()) // 6 gewuerfelt && alle sind im Lager
        {
            std::cout << "[Spielzug]: Es ist mindestens eine Figur im Lager." << std::endl;
            std::cin.ignore();
            int FigurIndex = SpielerObj1.ZufaelligerAusLager();
            FigurBewegen(Wuerfelzahl, FigurIndex, SpielerObj1, SpielerObj2, SpielerObj3, SpielerObj4, SpielfeldObj);

            SpielfeldDrucken(SpielerObj1, SpielerObj2, SpielerObj3, SpielerObj4, SpielfeldObj);

            std::cout << "[Spielzug]: Du hast eine 6 gewuerfelt und darfst deshalb nochmal wuerfeln" << std::endl;
            std::cin.ignore();
            int Wuerfelzahl = SpielerObj1.Wuerfeln();
            std::cout << "[FigurBewegen]: Du hast eine " << Wuerfelzahl << " gewuerfelt" << std::endl;
            std::cin.ignore();
            Spielzug(Wuerfelzahl, SpielerObj1, SpielerObj2, SpielerObj3, SpielerObj4, SpielfeldObj);
        }
        else // 6 Gewuerfelt && keiner ist im Lager
        {
            std::cout << "[Spielzug]: Es ist keine Figur im Lager." << std::endl;
            std::cin.ignore();
            if(FigurenBewegbar(Wuerfelzahl, SpielerObj1, SpielfeldObj))
            {
                std::cout << "[Spielzug]: Es ist ist mindestens eine Figur bewegbar." << std::endl << std::endl;
                std::cin.ignore();
                int FigurIndex = SpielerObj1.FigurAussuchen();
                FigurBewegen(Wuerfelzahl, FigurIndex, SpielerObj1, SpielerObj2, SpielerObj3, SpielerObj4, SpielfeldObj);
                
                std::cout << "[Spielzug]: Du hast eine 6 gewuerfelt und darfst deshalb nochmal wuerfeln" << std::endl;
                int Wuerfelzahl = SpielerObj1.Wuerfeln();
                std::cin.ignore();
                Spielzug(Wuerfelzahl, SpielerObj1, SpielerObj2, SpielerObj3, SpielerObj4, SpielfeldObj);
            }
            std::cout << "[Spielzug]: Das ist net so geil jetzt." << std::endl;

        }
    }
    else if (SpielerObj1.AlleFigurenImLager()) // Keine 6 gewuerfelt & alle sind im Lager
    {
        std::cout << "[Spielzug]: Du hast eine " << Wuerfelzahl << " gewuerfelt! ist oke nech" << std::endl;
        std::cin.ignore();
        std::cout << "[Spielzug]: Alle deiner Figuren sind noch im Lager." << std::endl;
        std::cin.ignore();
        std::cout << "[Spielzug]: Da du keine 6 gewuerfelt hast und alle deiner Spieler noch im Lager sind, darfst du noch 2 mal wuerfeln." << std::endl;
        std::cin.ignore();
        for (int i = 2; i > 0; i--)
        {
            int Wuerfelzahl = SpielerObj1.Wuerfeln();
            if (Wuerfelzahl == 6)
            {
                std::cout << "[Spielzug]: Du hast jetzt eine "<< Wuerfelzahl << " gewuerfelt" << std::endl;
                std::cin.ignore();
                Spielzug(6, SpielerObj1, SpielerObj2, SpielerObj3, SpielerObj4, SpielfeldObj);
                std::cout << "[Spielzug]: break" << std::endl << std::endl;
                std::cin.ignore();
                break;
            }
            else
            {
                std::cout << "[Spielzug]: Du hast eine " << Wuerfelzahl << " gewuerfelt. Du brauchst jedoch eine 6." << std::endl;
                std::cin.ignore();
                std::cout << "[Spielzug]: Weitere Versuche: " << i-1 << std::endl;
                std::cin.ignore();
            }
        }
    }
    else if (SpielerObj1.MindestensEineImSpielfeld() || SpielerObj1.MindestensEineImZiel()) // Keine 6 gewuerfelt & mindestens einen im Spielfeld
    {
        std::cout << "[Spielzug]: Du hast eine " << Wuerfelzahl << " gewuerfelt." << std::endl;
        std::cout << "[Spielzug]: Du hast mindestens einen Spieler im Spielfeld." << std::endl;
        std::cin.ignore();
        if(FigurenBewegbar(Wuerfelzahl, SpielerObj1, SpielfeldObj))
        {
            std::cout << "[Spielzug]: Du hast bewegbare Figuren." << std::endl;
            int FigurIndex = SpielerObj1.FigurAussuchen();
            
            while(SpielerObj1.get_aktuellesFeld().at(FigurIndex) == "X") //Ueberpruefung, ob die geweahlte Figur im Lager ist, waehrend man keine 6 gewuerfelt hat.
            {
                std::cout << "Die ausgew‰hlte Figur ist im Lager. Da du keine 6 gewuerfelt hast, kannst du diese Figur nicht bewegen." << std::endl;
                FigurIndex = SpielerObj1.FigurAussuchen();
            }
            
            FigurBewegen(Wuerfelzahl, FigurIndex, SpielerObj1, SpielerObj2, SpielerObj3, SpielerObj4, SpielfeldObj);
        }
        else
        {
            std::cout << "[Spielzug]: Kein Spieler Bewegbar" << std::endl << std::endl;
            std::cin.ignore();
            return;
        }
            
    }
    else //Wird zu dem dadrueber
    {
        std::cout << "[error]: common knowledge debugger triggered" << std::endl << std::endl;
        std::cin.ignore();
    }
}

void Spielablauf::FigurBewegen(int Wuerfelzahl, int FigurIndex, Spieler &SpielerObj1, Spieler &SpielerObj2, Spieler &SpielerObj3, Spieler &SpielerObj4, Spielfeld &SpielfeldObj) // Bewegung der Figur
{
    int SFI = BestimmeStartfeldIndex(FigurIndex, SpielerObj1, SpielfeldObj);
    std::cout << "[FigurBewegen]: StartfeldIndex ist " << SFI << std::endl;
    std::cin.ignore();
    int NFI = SFI + Wuerfelzahl; // Index des neuen Feldes auf Spielbrett, ergibt sich aus dem Index des Feldes wo man gestartet ist  (SFI) + der Wuerfelzahl
    std::cout << "[FigurBewegen]: NeuerFeldIndex ist " << NFI << std::endl;
    std::cin.ignore();

    NFI = UeberSpielfeldendeHinaus(NFI, FigurIndex, SpielerObj1, SpielfeldObj); //Korrektur NFI
    if (NFI != InFremdemZielfeld(Wuerfelzahl, SFI, NFI, SpielerObj1, SpielerObj2, SpielerObj3, SpielerObj4, SpielfeldObj)) //Korektur NFI
    {
        std::cout << "[Debug]: Figur ist in fremden Zielfeld" << std::endl;
        NFI = InFremdemZielfeld(Wuerfelzahl, SFI, NFI, SpielerObj1, SpielerObj2, SpielerObj3, SpielerObj4, SpielfeldObj);
        std::cout << "[Debug]: Neuer NFI ist " << NFI << std::endl;
        NFI = UeberSpielfeldendeHinaus(NFI, FigurIndex, SpielerObj1, SpielfeldObj); //Korrektur NFI nach InFremdenZield
        std::cout << "[Debug]: Nach erneuter NFI-Korrektur ist der NFI jetzt " << NFI << std::endl;
        std::cin.ignore(); 
    }
    else
    {
        std::cout << "[Debug]: Der NFI muss nicht geaendert werden" << std::endl;
        std::cout << "[Debug]: Der NFI ist " << NFI << ", das neue Feld ist "<< SpielfeldObj.get_Spielbrett().at(NFI) << std::endl;
    }
    if(UebersZielHinaus(Wuerfelzahl, FigurIndex, SpielerObj1, SpielfeldObj) ) //Bin ich ueber das Ziel hinaus?
    {
        std::cout << "[FigurBewegen]: Du bist ueber das Ziel hinaus." << std::endl;
        std::cin.ignore();
        int FigurIndex = SpielerObj1.FigurAussuchen();
        FigurBewegen( Wuerfelzahl, FigurIndex, SpielerObj1, SpielerObj2, SpielerObj3, SpielerObj4, SpielfeldObj);
        std::cout << "[FigurBewegen]: break" << std::endl << std::endl;
        return;
    }
     
    if(EigeneFigurAufNeuemFeld(FigurIndex, NFI, SpielerObj1, SpielfeldObj) != FigurIndex) //Ist eine Figur auf dem neuen Feld?
    {
        std::cout << "[FigurBewegen]: Deine eigene Figur steht auf dem Feld auf das du willst " << std::endl << std::endl;
        std::cin.ignore();
        SpielerObj1.FigurAussuchen();
        FigurBewegen( Wuerfelzahl, FigurIndex, SpielerObj1, SpielerObj2, SpielerObj3, SpielerObj4, SpielfeldObj);
        std::cout << "[FigurBewegen]: break" << std::endl << std::endl;
        return;
    }
    
    std::string neuesFeld = SpielfeldObj.get_Spielbrett().at(NFI); // Das neue Feld wird aus dem Spielbrett gelesen
    std::cout << "[FigurBewegen]: Das neue Feld ist nun " << neuesFeld << std::endl << std::endl;
    SpielerObj1.get_aktuellesFeld().at(FigurIndex) = neuesFeld; //Das neue Feld wird der Figur im Array zugewiesen
    std::cin.ignore();

    std::cout << "[FigurBewegen]: Distanz" << std::endl;
    std::cout << "[FigurBewegen]: " << SpielerObj1.get_Distanz().at(FigurIndex) << " + " << Wuerfelzahl << " = " << SpielerObj1.get_Distanz().at(FigurIndex) + Wuerfelzahl << std::endl;
    SpielerObj1.get_Distanz().at(FigurIndex) = SpielerObj1.get_Distanz().at(FigurIndex) + Wuerfelzahl; //Die Distanz wird erhoeht
    neuesFeld = SpielerObj1.get_aktuellesFeld().at(FigurIndex); // Das neue Feld wird aktualisiert
    std::cout << "[FigurBewegen]: Die Distanz ist nun " << SpielerObj1.get_Distanz().at(FigurIndex) << std::endl << std::endl;
    std::cin.ignore();
}

bool Spielablauf::FigurenBewegbar(int Wuerfelzahl,  Spieler &SpielerObj1, Spielfeld &SpielfeldObj) //Sind die Figuren eines Spielers bewegbar
{
    std::cout << "[FigurenBewegbar]: Figur Bewegbar Ueberpruefung" << std::endl;
    std::cin.ignore();
    for(unsigned int FigurIndex = 0; FigurIndex < SpielerObj1.get_aktuellesFeld().max_size();FigurIndex++)
    {
        if(! (SpielerObj1.get_aktuellesFeld().at(FigurIndex) == "X" ) || Wuerfelzahl == 6) //Wenn die angegebene Figur nicht im Lager ist oder man eine 6 gewuerfelt hat
        {
            std::cout << "[FigurenBewegbar]: Figur an Stelle " << FigurIndex << std::endl;
            std::cin.ignore();

            int SFI = BestimmeStartfeldIndex(FigurIndex, SpielerObj1, SpielfeldObj);
            int NFI = SFI + Wuerfelzahl; // Index des neuen Feldes auf Spielbrett, ergibt sich aus dem Index des Feldes wo man gestartet ist  (SFI) + der Wuerfelzahl
            std::cout << "[FigurenBewegbar]:  SFI: " << SFI << ", NFI: " << NFI << std::endl;
            if(UeberSpielfeldendeHinaus(NFI, FigurIndex, SpielerObj1, SpielfeldObj) != NFI) //Ist die Figur
            {
                NFI = UeberSpielfeldendeHinaus(NFI, FigurIndex, SpielerObj1, SpielfeldObj);
            }
        
            if(UebersZielHinaus(Wuerfelzahl, FigurIndex, SpielerObj1, SpielfeldObj))
            {
                std::cout << "[FigurBewegbar]: Figur kommt uebers Ziel hinaus." << NFI << std::endl;
                return false;
            }
            if(EigeneFigurAufNeuemFeld(FigurIndex, NFI, SpielerObj1, SpielfeldObj) != (int) FigurIndex)
            {
                std::cout << "[FigurBewegbar]: Eigene Figur ist auf neuem Feld" << std::endl;
                return false;        
            }
            if(SpielerObj1.FigurImLager(FigurIndex) && Wuerfelzahl != 6)
            {
                std::cout << "[FigurBewegbar]: Du hast eine Figur ausgewaehlt, die im Lager steh, obwohl du keine 6 hast." << std::endl;
                return false;
            }
        }
        std::cout << "[FigurBewegbar]: Deine Figur ist Bewegbar." << std::endl;
        
    }
    return true;
}

bool Spielablauf::UebersZielHinaus(int Wuerfelzahl, int FigurIndex, Spieler &SpielerObj1, Spielfeld &SpielfeldObj) // Schaut ob die gelaufene Distanz einer Figur groesser ist als 44 (zweite Runde) und uebergibt einen Wahrheitswert
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

int Spielablauf::SpielerAufStartfeld(int FigurIndex, Spieler &SpielerObj1) // Ueberprueft, ob ein Spieler auf dem Startfeld steht und gibt die Figur zurueck, die beweg werden muss.
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

int Spielablauf::UeberSpielfeldendeHinaus(int NFI, int FigurIndex, Spieler &SpielerObj1, Spielfeld &SpielfeldObj) // Ueberpr¸ft, ob ich ¸ber das Spielfeldarray hinaus bin
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

int Spielablauf::InFremdemZielfeld(int Wuerfelzahl, int SFI, int NFI, Spieler SpielerObj1, Spieler SpielerObj2, Spieler SpielerObj3, Spieler SpielerObj4, Spielfeld SpielfeldObj) // Bin ich in einem fremden Zielfeld gelandet?
{
    std::cout << "[InFremdemZielfeld]: Ueberpruefung" << std::endl;
    
    for (unsigned int i = 0; i < SpielerObj2.get_Zielfelder().max_size(); i++)
    {
        
        std::cout << "[Debug]: Zielfeld von Spieler 2: " << SpielerObj2.get_Zielfelder().at(i) << std::endl; //Debugging
        std::cout << "[Debug]: Neues Feld: " << SpielfeldObj.get_Spielbrett().at(NFI) << std::endl; //Debugging

        if (SpielerObj2.get_Zielfelder().at(i) == SpielfeldObj.get_Spielbrett().at(NFI)) // Ist das Neue Feld ein Zielfeld von Spieler2?
        {
            std::cout << "[InFremdemZielfeld]: Du bist in einem fremden Zielfeld gelandet." << std::endl;
            std::cin.ignore();
            NFI = NFI + 4; // Raus aus dem Bereich der Zielfelder von Spieler2
            std::cout << "[InFremdemZielfeld]: NFI ist jetzt " << NFI << std::endl;
            return NFI;
        }
    }
    for (unsigned int i = 0; i < SpielerObj3.get_Zielfelder().max_size(); i++) // Ist das Neue Feld ein Zielfeld von Spieler3?
    {
        std::cout << "[Debug]: Zielfeld von Spieler 3: " << SpielerObj3.get_Zielfelder().at(i) << std::endl; //Debugging
        std::cout << "[Debug]: Neues Feld: " << SpielfeldObj.get_Spielbrett().at(NFI) << std::endl; //Debugging

        if (SpielerObj3.get_Zielfelder().at(i) == SpielfeldObj.get_Spielbrett().at(NFI)) 
        {
            std::cout << "[InFremdemZielfeld]: Du bist in einem fremden Zielfeld gelandet." << std::endl;
            std::cin.ignore();
            NFI = NFI + 4; // Raus aus dem Bereich der Zielfelder von Spieler3
            std::cout << "[InFremdemZielfeld]: NFI ist jetzt " << NFI << std::endl;
            return NFI;
        }
    }
    for (unsigned int i = 0; i < SpielerObj4.get_Zielfelder().max_size(); i++) // Ist das Neue Feld ein Zielfeld von Spieler4?
    {
        std::cout << "[Debug]: Zielfeld von Spieler 4: " << SpielerObj4.get_Zielfelder().at(i) << std::endl; //Debugging
        std::cout << "[Debug]: Neues Feld: " << SpielfeldObj.get_Spielbrett().at(NFI) << std::endl; //Debugging

        if (SpielerObj4.get_Zielfelder().at(i) == SpielfeldObj.get_Spielbrett().at(NFI)) 
        {
            std::cout << "[InFremdemZielfeld]: Du bist in einem fremden Zielfeld gelandet." << std::endl;
            std::cin.ignore();
            NFI = NFI +4; // Raus aus dem Bereich der Zielfelder von Spieler3
            std::cout << "[InFremdemZielfeld]: NFI ist jetzt " << NFI << std::endl;
            return NFI;
        }
    }
    return NFI;
}

int Spielablauf::EigeneFigurAufNeuemFeld(int FigurIndex, int NFI, Spieler &SpielerObj, Spielfeld &SpielfeldObj) // Ueberprueft, ob eine Figur des aktuellen Spielers auf dem neuen Feld steht
{
    std::string NeuesFeld = SpielfeldObj.get_Spielbrett().at(NFI);
    for (int i = 0; i < (int)SpielerObj.get_aktuellesFeld().max_size(); i++)
    {
        if (SpielerObj.get_aktuellesFeld().at(i) == NeuesFeld)
        {
            std::cout << "Wenn " << i << " ungleich " << FigurIndex << " ist, muss Figur " << i << " bewegt werden." << std::endl;
            if (i != (int)FigurIndex)
            {
                std::cout << "[EigeneFigurAufNeuemFeld]: Figur " << i << " muss bewegt werden, da du sonst deine eigene Figur schlagen wuerdest" << std::endl;
                return i; // Wenn ja, gib den Index der Figur zurueck, welche dann stattdesssen bewegt werden muss.
            }
        }
    }
    std::cout << "[EigeneFigurAufNeuemFeld]: Passt alles soweit" << std::endl;
    return FigurIndex; // Wenn ja, gib den Index der Figur zurueck, welche wir gerade schon bewegen.
}

void Spielablauf::SpielerAufNeuemFeld(std::string NeuesFeld, Spieler &SpielerObj1, Spieler &SpielerObj2, Spieler &SpielerObj3, Spieler &SpielerObj4, Spielfeld &SpielfeldObj) // Ist eine andere Spielfigur auf meinem neuen Feld?
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
            SpielerObj4.get_aktuellesFeld().at(i) = "X"; // Spieler wird rausgekickt (Position der Figur auf X fùr Lager).
            SpielerObj4.get_Distanz().at(i) = 0;         // Distanz der Spielfigur wird zurueckgesetzt.
        }
    }
}

int Spielablauf::BestimmeStartfeldIndex(int FigurIndex, Spieler &SpielerObj, Spielfeld &SpielfeldObj) // Bestimmt den Index auf dem Array Spielbrett, an welcher sich das Startfeld des eingegebenen Spielers befindet.
{
    if (SpielerObj.FigurImLager(FigurIndex)) // Wenn das aktuelle Feld der Figur "X" ist
    {
        for (unsigned int i = 0; i < SpielfeldObj.get_Spielbrett().max_size(); i++) // Gehe das Spielfeld durch
        {
            if (SpielfeldObj.get_Spielbrett().at(i) == SpielerObj.get_Startfeld()) // Ueberpruefe, ob das Feld an Index i gleich dem Startfeld des Spielers ist
            {
                return i; // Wenn ja, gib den Index vom Startfeld zurueck
            }
        }
    }
    else // Wenn das aktuelle Feld der Figur nicht "X" ist
    {
        for (unsigned int i = 0; i < SpielfeldObj.get_Spielbrett().max_size(); i++) // Gehe das Spielfeld durch
        {
            if (SpielfeldObj.get_Spielbrett().at(i) == SpielerObj.get_aktuellesFeld().at(FigurIndex)) // Ueberpruefe, ob das Feld an Index i gleich dem aktuellen Feld des Spielers ist
            {
                return i; // Wenn ja, gib den index dieses Feldes zurueck
            }
        }
    }
    std::cout << "[error]: Startfeld der Figur " << FigurIndex << " konnte nicht gefunden werden." << std::endl;
    return 0;
}

bool Spielablauf::SpielEnde(Spieler &SpielerObj1, Spieler &SpielerObj2, Spieler &SpielerObj3, Spieler &SpielerObj4) // Ueberprueft, ob mindestens ein Spieler alle Figuren im Ziel hat.
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

int Spielablauf::BestimmeIndexDesStartfelds(Spieler &SpielerObj, Spielfeld &SpielfeldObj)
{
    for (unsigned int i = 0; i < SpielfeldObj.get_Spielbrett().max_size(); i++) // Gehe das Spielfeld durch
        {
            if (SpielfeldObj.get_Spielbrett().at(i) == SpielerObj.get_Startfeld()) //Ueberpruefe, ob das Feld an Index i gleich dem Startfeld des Spielers ist
            {
                return i; // Wenn ja, gib den Index vom Startfeld zurueck
            }
        }
    return 0;
}

void Spielablauf::SpielfeldDrucken(Spieler &SpielerObj1, Spieler &SpielerObj2, Spieler &SpielerObj3, Spieler &SpielerObj4, Spielfeld &SpielfeldObj)
{
    std::cout << "Das Spielfeld wird ausgegeben, bitte besteatige mit Enter.";
    std::cin.ignore();
    
    std::cout << std::endl << "--------- Spielfeld ---------" << std::endl;
    
    for(int i = 0; i < (int) SpielfeldObj.get_Spielbrett().max_size();i++)
    {        
        if(i == BestimmeIndexDesStartfelds(SpielerObj1, SpielfeldObj)) //Wenn das Feld 0 (Startfeld Spieler 1) ausgegeben werden soll
        {
            std::cout << "Lager S" << SpielerObj1.get_Kennzeichner() << ": ";
            for(unsigned int i = 0; i < SpielerObj1.get_aktuellesFeld().max_size();i++)
            if(SpielerObj1.get_aktuellesFeld().at(i) == "X") //Gucke, ob Figuren von Spieler 1 noch im Lager sind
            {
                std::cout << "Figur" << i << " "; //Wenn ja, gib diese aus
            }
            std::cout << std::endl;
        }

        if(i == BestimmeIndexDesStartfelds(SpielerObj2, SpielfeldObj)) //Wenn das Feld 10 (Startfeld Spieler 2) ausgegeben werden soll
        {
            std::cout << "Lager S" << SpielerObj2.get_Kennzeichner() << ": ";
            for(unsigned int i = 0; i < SpielerObj2.get_aktuellesFeld().max_size();i++)
            if(SpielerObj2.get_aktuellesFeld().at(i) == "X") //Gucke, ob Figuren von Spieler 2 noch im Lager sind
            {
                std::cout << "Figur" << i << " "; //Wenn ja, gib diese aus
            }
            std::cout << std::endl;
        }
        
        if(i == BestimmeIndexDesStartfelds(SpielerObj3, SpielfeldObj)) //Wenn das Feld 20 (Startfeld Spieler 3) ausgegeben werden soll
        {
            std::cout << "Lager S" << SpielerObj3.get_Kennzeichner() << ": ";
            for(unsigned int i = 0; i < SpielerObj3.get_aktuellesFeld().max_size();i++)
            if(SpielerObj3.get_aktuellesFeld().at(i) == "X") //Gucke, ob Figuren von Spieler 3 noch im Lager sind
            {
                std::cout << "Figur" << i << " "; //Wenn ja, gib diese aus
            }
            std::cout << std::endl;
        }

        if(i == BestimmeIndexDesStartfelds(SpielerObj4, SpielfeldObj)) //Wenn das Feld 30 (Startfeld Spieler 4) ausgegeben werden soll
        {
            std::cout << "Lager S" << SpielerObj4.get_Kennzeichner() << ": ";
            for(unsigned int i = 0; i < SpielerObj4.get_aktuellesFeld().max_size();i++)
            if(SpielerObj4.get_aktuellesFeld().at(i) == "X") //Gucke, ob Figuren von Spieler 4 noch im Lager sind
            {
                std::cout << "Figur" << i << " "; //Wenn ja, gib diese aus
            }
            std::cout << std::endl;
        }

        std::cout << std::setw(2) << "(" << SpielfeldObj.get_Spielbrett().at(i) << ")" << " ";
        for(unsigned int j = 0; j < SpielerObj1.get_aktuellesFeld().max_size();j++)
        {
           if(SpielerObj1.get_aktuellesFeld().at(j) == SpielfeldObj.get_Spielbrett().at(i))
            {
                std::cout << "< Spieler " << SpielerObj1.get_Kennzeichner() << ", Figur " << j;
            }

            if(SpielerObj2.get_aktuellesFeld().at(j) == SpielfeldObj.get_Spielbrett().at(i))
            {
                std::cout << "< Spieler " << SpielerObj2.get_Kennzeichner() << ", Figur " << j;
            }
            
            if(SpielerObj3.get_aktuellesFeld().at(j) == SpielfeldObj.get_Spielbrett().at(i))
            {
                std::cout << "< Spieler " << SpielerObj3.get_Kennzeichner() << ", Figur " << j;
            }
            
            if(SpielerObj4.get_aktuellesFeld().at(j) == SpielfeldObj.get_Spielbrett().at(i))
            {
                std::cout << "< Spieler " << SpielerObj4.get_Kennzeichner() << ", Figur " << j;
            }
        }
        std::cout << std::endl;
    }
}

/*
  \brief Kurzbeschreibung
 
  Langbeschriebung
  @param parameter1 Funktion des Parameters 1
  @param parameter2 Funktion des Parameters 2
  @see Referenz auf andere Funktion, die ‰hnliches macht oder dazu gehˆrt
  @return Beschreibung des R¸ckgabewertes
  @pre Bedingungen, die vor dem Aufruf der Funktion erf¸llt sein m¸ssen
  @post Bedingungen, die nach dem Aufruf der Funktion erf¸llt sind
  @since Wann die Funktion eingef¸hrt wurde
  @author Autor der Funktion
 */