#include <iostream>
#include <string>
#include <vector>
#include <array>

#include "Spieler.hpp"
#include "Spielablauf.hpp"
#include "Spielfeld.hpp"
#include "Zufall.hpp"

// Datensaetze der Spieler
std::string Spieler1_Startfeld = "0";
std::array<std::string, 4> Spieler1_Zielfelder = {"0a", "0b", "0c", "0d"};
std::array<std::string, 4> Spieler1_aktuellesSpielfeld = {"X", "X", "X", "X"};
std::array<int, 4> Spieler1_Distanz = {0, 0, 0, 0};

std::string Spieler2_Startfeld = "10";
std::array<std::string, 4> Spieler2_Zielfelder = {"1a", "1b", "1c", "1d"};
std::array<std::string, 4> Spieler2_aktuellesSpielfeld = {"X", "X", "X", "X"};
std::array<int, 4> Spieler2_Distanz = {0, 0, 0, 0};

std::string Spieler3_Startfeld = "20";
std::array<std::string, 4> Spieler3_Zielfelder = {"2a", "2b", "2c", "2d"};
std::array<std::string, 4> Spieler3_aktuellesSpielfeld = {"X", "X", "X", "X"};
std::array<int, 4> Spieler3_Distanz = {0, 0, 0, 0};

std::string Spieler4_Startfeld = "30";
std::array<std::string, 4> Spieler4_Zielfelder = {"3a", "3b", "3c", "3d"};
std::array<std::string, 4> Spieler4_aktuellesSpielfeld = {"X", "X", "X", "X"};
std::array<int, 4> Spieler4_Distanz = {0, 0, 0, 0};

void Spielerausgabe(Spieler&,Spieler&,Spieler&,Spieler&);

int main()
{
    Spielablauf Mensch_Aergere_dich_nicht;                                                  //Initialisiert das Spielablaufobjekt "Mensch_Aergere_dich_nicht".
    Spielfeld Spielbrett; // Initialisiert das Spielfeldobjekt "Spielbrett".

    Spielbrett.InitialisiereSpiel(); // Führt die Methode "InitialisiereSpiel" des Spielfeldobjekt "Spielbrett" aus.

    Spieler Spieler1(Spieler1_Startfeld, Spieler1_Zielfelder, Spieler1_aktuellesSpielfeld, Spieler1_Distanz); // Erschafft ein Spielerobjekt "Spieler 1" mit den gegebenen Startwerten.
    Spieler Spieler2(Spieler2_Startfeld, Spieler2_Zielfelder, Spieler2_aktuellesSpielfeld, Spieler2_Distanz); // Erschafft ein Spielerobjekt "Spieler 2" mit den gegebenen Startwerten.
    Spieler Spieler3(Spieler3_Startfeld, Spieler3_Zielfelder, Spieler3_aktuellesSpielfeld, Spieler3_Distanz); // Erschafft ein Spielerobjekt "Spieler 3" mit den gegebenen Startwerten.
    Spieler Spieler4(Spieler4_Startfeld, Spieler4_Zielfelder, Spieler4_aktuellesSpielfeld, Spieler4_Distanz); // Erschafft ein Spielerobjekt "Spieler 4" mit den gegebenen Startwerten
        
    Mensch_Aergere_dich_nicht.EineRunde(Spieler1, Spieler2, Spieler3, Spieler4, Spielbrett);
    Spielerausgabe(Spieler1, Spieler2, Spieler3, Spieler4);
    Mensch_Aergere_dich_nicht.EineRunde(Spieler1, Spieler2, Spieler3, Spieler4, Spielbrett);
    //Mensch_Aergere_dich_nicht.EineRunde(Spieler1, Spieler2, Spieler3, Spieler4, Spielbrett);
    Spielerausgabe(Spieler1, Spieler2, Spieler3, Spieler4);

    /*while(!(Mensch_Aergere_dich_nicht.SpielEnde(Spieler1, Spieler2, Spieler3, Spieler4)))
    {
        Mensch_Aergere_dich_nicht.EineRunde(Spieler1, Spieler2, Spieler3, Spieler4 , Spielbrett);
    }*/
}

void Spielerausgabe(Spieler &Spieler1,Spieler &Spieler2,Spieler &Spieler3,Spieler &Spieler4)
{
    std::cout << std::endl << "--------- Spieler 1 ---------" << std::endl << std::endl;
    Spieler1.DatenAusgabe();
    std::cin.ignore();

    std::cout << std::endl << "--------- Spieler 2 ---------" << std::endl << std::endl;
    Spieler2.DatenAusgabe();
    std::cin.ignore();

    std::cout << std::endl << "--------- Spieler 3 ---------" << std::endl << std::endl;
    Spieler3.DatenAusgabe();
    std::cin.ignore();

    std::cout << std::endl << "--------- Spieler 4 ---------" << std::endl << std::endl;
    Spieler4.DatenAusgabe();
    std::cin.ignore();


}
