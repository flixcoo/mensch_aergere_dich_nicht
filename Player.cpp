#include <iostream>
#include <string>
#include <vector>
#include <array>

#include "Player.hpp"
#include "System.hpp"

// Konstruktor
Player::Player(int identifier, std::string startingField, std::array<std::string, 4> targetFields, std::array<std::string, 4> aktuellesFeld, std::array<int, 4> distance) // Erschafft einen Spieler mit dem startingField, den targetFieldsn und den aktuellen Feldern als Eingabe.
{
    this->identifier = identifier;       // Integer mit einem identifier für den Spieler.
    this->startingField = startingField; // String der das startingField des Spielers enthaelt.
    this->targetFields = targetFields;   // Array der Groesse 4 welches die vier targetFields enthaelt.
    this->aktuellesFeld = aktuellesFeld; // Array der Groesse 4 welches Strings mit den aktuellen Positionen der vier Spielfiguren enthaelt.
    this->distance = distance;           // Array der Groesse 4 welches Integer mit der aktuell zurueckgelegten Distanz der jeweiligen Figuren enthaelt.
    Lager = "X";                         // Zeichen, anhand dessen das Programm erkennt, dass sich eine Figur im Lager befindet.

    std::cout << "[System]: Spieler " << identifier << " initialisiert" << std::endl; // Konsolenausgabe
}

// Destruktor
Player::~Player()
{
    std::cout << "[System]: Spieler geloescht." << std::endl; // Konstruktor
}

// Getter der Klasse
int Player::get_identifier()
{
    return identifier;
}

std::string Player::get_startingField() // Gibt den String "startingField" zurueck.
{
    return startingField;
}

std::array<std::string, 4> Player::get_targetFields() // Gibt das Array "targetFields" zurueck.
{
    return targetFields;
}

std::array<std::string, 4> &Player::get_aktuellesFeld() // Gibt das Array "aktuellesFeld" zurueck.
{
    return aktuellesFeld;
}

std::array<int, 4> &Player::get_distance() // Gibt das Array "aktuellesFeld" zurueck.
{
    return distance;
}

void Player::printData() // Funktion gibt das startingField, die targetFields und die aktuellen Positionen der Figuren eines Spielers aus.
{
    std::cout << "Starfeld des Spielers: " << startingField << std::endl
              << std::endl; // Konsoleausgabe: startingField des Spielers

    std::cout << "targetFields des Spielers: " << std::endl; // Konsolenausgabe
    for (int i = 0; i < (int)targetFields.max_size(); i++)   // Durchgehen des Arrays
    {
        std::cout << targetFields.at(i) << std::endl; // Gib die Werte der targetFields zurueck
    }

    std::cout << "Aktuelle Felder der Spielfiguren: " << std::endl; // Konsolenausgabe
    for (unsigned int i = 0; i < aktuellesFeld.max_size(); i++)     // Array wird abgegangen
    {
        std::cout << aktuellesFeld.at(i) << std::endl; // Gib die Werte der aktuellen Felder zurueck
    }

    std::cout << "distance der Spielfiguren: " << std::endl; // Konsolenausgabe
    for (unsigned int i = 0; i < distance.max_size(); i++)   // Array wird abgegangen
    {
        std::cout << distance.at(i) << std::endl; /// Gib die Werte der distance zurueck
    }
}

int Player::rollDice() // Zufallszahl zwischen eins - sechs.
{
    return System::randomizer(6);
}

int Player::selectToken()
{
    std::cout << std::endl;
    std::cout << "[FigurAussuchen]: Waehle eine Figur, die du Bewegen willst: " << std::endl;
    std::cout << "[0] - Figur 0" << std::endl;
    std::cout << "[1] - Figur 1" << std::endl;
    std::cout << "[2] - Figur 2" << std::endl;
    std::cout << "[3] - Figur 3" << std::endl;
    int FigurIndex;
    std::cin >> FigurIndex; // Spieler wählt Index

    while (std::cin.fail() || FigurIndex > 3 || FigurIndex < 0) // Solange die Eingabe falsch ist.
    {
        if (FigurIndex > 3 || FigurIndex < 0) //
        {
            std::cout << "[FigurAussuchen]: Figur " << FigurIndex << " existiert nicht" << std::endl;
            std::cout << "[FigurAussuchen]: Bitte geben Sie eine existierende Figur ein:" << std::endl;
            std::cin.clear();
            std::cin >> FigurIndex; // Spieler wählt Index
            std::cin.ignore();
        }
        else if (std::cin.fail())
        {
            std::cout << "[FigurAussuchen]: Eingabe konnte nicht erkannt werden." << std::endl;
            std::cout << "[FigurAussuchen]: Bitte geben Sie die Figur erneut ein:" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> FigurIndex; // Spieler wählt Index
            std::cin.ignore();
        }
    };
    return FigurIndex;
}

int Player::randomFromStorage() // Prueft, welche Spielfiguren im Lager stehen und wählt zufällig eine dieser aus.
{
    std::vector<int> tempVec;
    for (unsigned int i = 0; i < aktuellesFeld.max_size(); i++) // Geht die Positionen der 4 Spielfiguren eines Spielers durch.
    {
        if (tokenInStorage(i)) // Checkt ob die Spielfigur sich im Lager befindet
        {
            tempVec.push_back(i); // Fuegt den Index der startingFieldfiguren in ein Veektor ein.
        }
    }
    return tempVec.at((System::randomizer(tempVec.size())) - 1); // DOC WIP
}

int Player::randomFromArena() // Prueft, welche Spielfiguren auf dem Spielfeld stehen und wählt zufällig eine dieser aus.
{
    std::vector<int> tempVec;
    for (unsigned int i = 0; i < aktuellesFeld.max_size(); i++) // Geht die Positionen der 4 Spielfiguren eines Spielers durch.
    {
        if (!tokenInStorage(i) && tokenInTargetField(i)) // Überprüft ob die Figur an Index i nicht im Lager und nicht im Ziel ist (also im Spielfeld ist)
        {
            tempVec.push_back(i);
        }
    }
    return tempVec.at((System::randomizer(tempVec.size())) - 1); // Die Groesse des Vektors wird als obere Grenze für eine Zufallsgenerator startend bei 1 benutzt, welche durch "-1" als Index des aktuellesFeld-Arrays dient
}

bool Player::tokenInStorage(int i) // Prueft, ob die Figur an Index i sich im Lager befindet.
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

bool Player::tokenInArena(int i) // Prueft, ob die Figur an Index i sich auf dem Spielfeld befindet.
{
    if ((tokenInTargetField(i)) && !(tokenInStorage(i)))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Player::tokenInTargetField(int i) // Prueft, ob die Figur an Index i sich in einem der targetFields befindet.
{
    if ((aktuellesFeld.at(i) == targetFields.at(0)) ||
        (aktuellesFeld.at(i) == targetFields.at(1)) ||
        (aktuellesFeld.at(i) == targetFields.at(2)) ||
        (aktuellesFeld.at(i) == targetFields.at(3)))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Player::allTokenInStorage() // Prüft ob alle Figuren im Lager sind
{
    if (tokenInStorage(0) && tokenInStorage(1) && tokenInStorage(2) && tokenInStorage(3))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Player::allTokenInArena() // Prueft, ob sich alle Figuren eines Spielers sich auf dem Spielfeld befinden.
{
    if (tokenInArena(0) && tokenInArena(1) && tokenInArena(2) && tokenInArena(3))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Player::allTokenInTargetField() // Prueft, ob sich alle Figuren eines Spielers sich im Ziel befinden.
{
    if ((tokenInTargetField(0)) &&
        (tokenInTargetField(1)) &&
        (tokenInTargetField(2)) &&
        (tokenInTargetField(3)))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Player::minOneInStorage() // Uberprueft, ob mindestens eine Spielfigur im Lager ist.
{
    for (unsigned int i = 0; i < aktuellesFeld.max_size(); i++)
    {
        if (tokenInStorage(i))
        {
            return true;
        }
    }
    return false;
}

bool Player::minOneInArena() // Uberprueft, ob mindestens eine Spielfigur im Lager ist.
{
    for (unsigned int i = 0; i < aktuellesFeld.max_size(); i++) // Geht das aktuellesFeld-Array durch
    {
        if (!(tokenInTargetField(i)) && !(tokenInStorage(i))) // Ist Figur nicht im Ziel und nicht im Lager
        {
            return true;
        }
    }
    return false;
}

bool Player::minOneInTargetField() // Uberprueft, ob mindestens eine Spielfigur im Lager ist.
{
    for (unsigned int i = 0; i < aktuellesFeld.max_size(); i++) // Geht das aktuellesFeld-Array durch
    {
        if (!(tokenInArena(i)) && !(tokenInStorage(i))) // Ist Figur nicht im Ziel und nicht im Lager
        {
            return true;
        }
    }
    return false;
}
