#include <iostream>
#include <string>
#include <vector>
#include <array>

#include "Spieler.hpp"
#include "Zufall.hpp"

// Konstruktor
Spieler::Spieler(std::string Startfeld, std::array<std::string, 4> Zielfelder, std::array<std::string, 4> aktuellesFeld, std::array<int, 4> Distanz) // Erschafft einen Spieler mit dem Startfeld, den Zielfeldern und den aktuellen Feldern als Eingabe.
{
    this->Startfeld = Startfeld;         // String der das Startfeld des Spielers enthaelt
    this->Zielfelder = Zielfelder;       // Array der Groesse 4 welches die vier Zielfelder enthaelt
    this->aktuellesFeld = aktuellesFeld; // Array der Groesse 4 welches Strings mit den aktuellen Positionen der vier Spielfiguren enthaelt
    this->Distanz = Distanz;
    Lager = "X"; // Zeichen, anhand dessen das Programm erkennt, dass sich eine Figur im Lager befindet.

    std::cout << "[System]: Spieler initialisiert" << std::endl; // Konsolenausgabe
}

// Destruktor
Spieler::~Spieler()
{
    std::cout << "[System]: Spieler geloescht." << std::endl; // Konstruktor
}

// Getter der Klasse
std::string Spieler::get_Startfeld() // Gibt den String "Startfeld" zurueck.
{
    return Startfeld;
}

std::array<std::string, 4> Spieler::get_Zielfelder() // Gibt das Array "Zielfelder" zurueck.
{
    return Zielfelder;
}

std::array<std::string, 4> & Spieler::get_aktuellesFeld() // Gibt das Array "aktuellesFeld" zurueck.
{
    return aktuellesFeld;
}

std::array<int, 4> & Spieler::get_Distanz() // Gibt das Array "aktuellesFeld" zurueck.
{
    return Distanz;
}

void Spieler::DatenAusgabe() // Funktion gibt das Startfeld, die Zielfelder und die aktuellen Positionen der Figuren eines Spielers aus.
{
    std::cout << "Starfeld des Spielers: " << Startfeld << std::endl
              << std::endl; // Konsoleausgabe: Startfeld des Spielers

    std::cout << "Zielfelder des Spielers: " << std::endl; // Konsolenausgabe
    for (int i = 0; i < (int)Zielfelder.max_size(); i++)   // Durchgehen des Arrays
    {
        std::cout << Zielfelder.at(i) << std::endl; // Gib die Werte der Zielfelder zurueck
    }

    std::cout << "Aktuelle Felder der Spielfiguren: " << std::endl; // Konsolenausgabe
    for (unsigned int i = 0; i < aktuellesFeld.max_size(); i++)     // Array wird abgegangen
    {
        std::cout << aktuellesFeld.at(i) << std::endl; // Gib die Werte der aktuellen Felder zurueck
    }

    std::cout << "Distanz der Spielfiguren: " << std::endl; // Konsolenausgabe
    for (unsigned int i = 0; i < Distanz.max_size(); i++)   // Array wird abgegangen
    {
        std::cout << Distanz.at(i) << std::endl; /// Gib die Werte der Distanz zurueck
    }
}

int Spieler::Wuerfeln() // Zufallszahl zwischen eins - sechs.
{
    return Zufall::Zufallsgenerator(6);
}

bool Spieler::FigurImLager(int i) // Prueft, ob die Figur an Index i sich im Lager befindet.
{
    if (aktuellesFeld.at(i) == Lager)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Spieler::AlleFigurenImLager() // Prüft ob alle Figuren im Lager sind
{
    if (FigurImLager(0) && FigurImLager(1) && FigurImLager(2) && FigurImLager(3))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Spieler::FigurImZiel(int i) // Prueft, ob die Figur an Index i sich in einem der Zielfelder befindet.
{
    if ((aktuellesFeld.at(i) == Zielfelder.at(0)) &&
        (aktuellesFeld.at(i) == Zielfelder.at(1)) &&
        (aktuellesFeld.at(i) == Zielfelder.at(2)) &&
        (aktuellesFeld.at(i) == Zielfelder.at(3)))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Spieler::AlleFigurenImZiel() // Prueft, ob sich alle Figuren eines Spielers sich im Ziel befinden.
{
    if ((FigurImZiel(0)) &&
        (FigurImZiel(1)) &&
        (FigurImZiel(2)) &&
        (FigurImZiel(3)))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Spieler::FigurAufSpielfeld(int i) // Prueft, ob die Figur an Index i sich auf dem Spielfeld befindet.
{
    if ((FigurImZiel(i)) && !(FigurImLager(i)))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Spieler::AlleFigurenAufSpielfeld() // Prueft, ob sich alle Figuren eines Spielers sich auf dem Spielfeld befinden.
{
    if (FigurAufSpielfeld(0) && FigurAufSpielfeld(1) && FigurAufSpielfeld(2) && FigurAufSpielfeld(3))
    {
        return true;
    }
    else
    {
        return false;
    }
}

int Spieler::ZufaelligerAusLager() // Prueft, welche Spielfiguren im Lager stehen und wählt zufällig eine dieser aus.
{
    std::vector<int> tempVec;
    for (unsigned int i = 0; i < aktuellesFeld.max_size(); i++) // Geht die Positionen der 4 Spielfiguren eines Spielers durch.
    {
        if (FigurImLager(i)) // Checkt ob die Spielfigur sich im Lager befindet
        {
            tempVec.push_back(i); // Fuegt den Index der Startfeldfiguren in ein Veektor ein.
        }
    }
    return tempVec.at((Zufall::Zufallsgenerator(tempVec.size())) - 1); // DOC WIP
}

int Spieler::ZufaelligerAusFeld() // Prueft, welche Spielfiguren auf dem Spielfeld stehen und wählt zufällig eine dieser aus.
{
    std::vector<int> tempVec;
    for (unsigned int i = 0; i < aktuellesFeld.max_size(); i++) // Geht die Positionen der 4 Spielfiguren eines Spielers durch.
    {
        if (!FigurImLager(i) && FigurImZiel(i)) // Überprüft ob die Figur an Index i nicht im Lager und nicht im Ziel ist (also im Spielfeld ist)
        {
            tempVec.push_back(i);
        }
    }
    return tempVec.at((Zufall::Zufallsgenerator(tempVec.size())) - 1); // Die Groesse des Vektors wird als obere Grenze für eine Zufallsgenerator startend bei 1 benutzt, welche durch "-1" als Index des aktuellesFeld-Arrays dient
}

bool Spieler::MindestensEineImLager() // Uberprueft, ob mindestens eine Spielfigur im Lager ist.
{
    for (unsigned int i = 0; i < aktuellesFeld.max_size(); i++)
    {
        if (FigurImLager(i))
        {
            return true;
        }
    }
    return false;
}

bool Spieler::MindestensEineImSpielfeld() // Uberprueft, ob mindestens eine Spielfigur im Lager ist.
{
    for (unsigned int i = 0; i < aktuellesFeld.max_size(); i++) // Geht das aktuellesFeld-Array durch
    {
        if (!(FigurImZiel(i)) && !(FigurImLager(i))) // Ist Figur nicht im Ziel und nicht im Lager
        {
            return true;
        }
    }
    return false;
}

bool Spieler::MindestensEineImZiel() // Uberprueft, ob mindestens eine Spielfigur im Lager ist.
{
    for (unsigned int i = 0; i < aktuellesFeld.max_size(); i++) // Geht das aktuellesFeld-Array durch
    {
        if (!(FigurAufSpielfeld(i)) && !(FigurImLager(i))) // Ist Figur nicht im Ziel und nicht im Lager
        {
            return true;
        }
    }
    return false;
}

int Spieler::FigurAussuchen()
{
    std::cout << "Waehle eine Figur, die du Bewegen willst: ";
    int FigurIndex;
    std::cin >> FigurIndex; //Spieler wählt Index
    return FigurIndex;
}