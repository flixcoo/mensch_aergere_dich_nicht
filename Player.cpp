#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <iomanip>

#include "Player.hpp"
#include "System.hpp"

/**
 * @brief Konstruktor der Klasse "Player".
 * Der Konstruktor der Klasse initialisiert ein Objekt mit den  eingegebenen Parametern,
 * @param identifier Integer mit einem Identifikator für das Player-Objekt.
 * @param Storage Zeichen, anhand dessen das Programm erkennt, dass sich eine Figur im Lager befindet.
 * @param startingField String der das startingField des Spielers enthaelt.
 * @param currentField Array der Groesse 4 welches Strings mit den aktuellen Positionen der vier Spielfiguren enthaelt.
 * @param distance Array der Groesse 4 welches Integer mit der aktuell zurueckgelegten Distanz der jeweiligen Figuren enthaelt.
 * @param targetFields Array der Groesse 4 welches die vier targetFields enthaelt.
 * @pre Es müssen alle Argumente, mit denen das Player-Objekt erstellt werden, die richtigen Startwerte enthalten.
 * @post Ein Player-Objekt ist erstellt,
 * @since Version 1.0
 * @author Felix Kirchner
 */
Player::Player(int identifier, std::string startingField, std::array<std::string, 4> targetFields, std::array<std::string, 4> currentField, std::array<int, 4> distance) // Erschafft einen Spieler mit dem identifier, dem startingField, den targetFields, den currentFields und der distance als Eingabe. Dazu wird das Attribut auf "X" für das Lager gesetzt.
{
    this->identifier = identifier;
    Storage = "X";

    this->startingField = startingField;
    this->currentField = currentField;
    this->distance = distance;
    this->targetFields = targetFields;

    std::cout << "[System]: Spieler " << identifier << " initialisiert" << std::endl; // Konsolenausgabe
}

/**
 * @brief Destruktor der Klasse "Player".
 * Der Destruktor der Klasse beinhaltet nur eine Konsolenausgabe, da fuer den Spieler keine weiteren
 * Argumente beim vernichten vorgesehen sind.
 * @pre Es muss ein Player-Objekt geben.
 * @post Das Player-Objekt ist nun geloescht.
 * @since Version 1.0
 * @author Felix Kirchner
 */
Player::~Player()
{
    std::cout << "[System]: Spieler geloescht." << std::endl; // Konstruktor
}

/**
 * @brief Getter des Attributes "identifier".
 * Die Funktion gibt das private Attribut "identifier" zurueck, damit dieses von anderen Klassen benutzt werden kann.
 * @return Die Funktion gibt einen Integer zurueck, welches den identifier der Player-Klasse enthealt.
 * @pre Es muss ein Player-Objekt existieren.
 * @since Version 1.5
 * @author Felix Kirchner
 */
int Player::get_identifier()
{
    return identifier;
}

/**
 * @brief Getter des Attributes "startingField".
 * Die Funktion gibt das private Attribut "startingField" zurueck, damit dieses von anderen Klassen benutzt werden kann.
 * @return Die Funktion gibt ein Array vom Typ String zurueck, welches die Startfelder der Player-Klasse enthealt.
 * @pre Es muss ein Player-Objekt existieren.
 * @since Version 1.0
 * @author Felix Kirchner
 */
std::string Player::get_startingField() // Gibt den String "startingField" zurueck.
{
    return startingField;
}

/**
 * @brief Getter des Attributes "targetFields".
 * Die Funktion gibt das private Attribut "targetFields" zurueck, damit dieses von anderen Klassen benutzt werden kann.
 * @return Die Funktion gibt ein Array vom Typ String zurueck, welches die Zielfelder der Player-Klasse enthealt.
 * @pre Es muss ein Player-Objekt existieren.
 * @since Version 1.0
 * @author Felix Kirchner
 */
std::array<std::string, 4> Player::get_targetFields()
{
    return targetFields;
}

/**
 * @brief Getter des Attributes "currentField".
 * Die Funktion gibt das private Attribut "currentField" zurueck, damit dieses von anderen Klassen benutzt werden kann.
 * @return Die Funktion gibt ein Array vom Typ String zurueck, welches die aktuellen Felder der Figuren der Player-Klasse enthealt.
 * @pre Es muss ein Player-Objekt existieren.
 * @since Version 1.0
 * @author Felix Kirchner
 */
std::array<std::string, 4> &Player::get_currentField()
{
    return currentField;
}

/**
 * @brief Getter des Attributes "distance".
 * Die Funktion gibt das private Attribut "distance" zurueck, damit dieses von anderen Klassen benutzt werden kann.
 * @return Die Funktion gibt ein Array vom Typ Integer zurueck, welches die aktuelle Distanz der Figuren der Player-Klasse enthealt.
 * @pre Es muss ein Player-Objekt existieren.
 * @since Version 1.0
 * @author Felix Kirchner
 */
std::array<int, 4> &Player::get_distance()
{
    return distance;
}

/**
 * @brief Methode, welche eine Zufallszahl zwischen eins und sechs zurueckgibt.
 * Es wird die Methode randomizer der System-Klasse mit einer oberen Grenze von 6 ausgefuehrt.
 * @see randomizer
 * @return Es wird ein zufaelliger Integer zwischen eins und sechs zurueckgegeben
 * @pre Es muss ein Player-Objekt geben.
 * @post Es gibt eine Wuerfelzahl, welche von anderen Klassen verwendet werden kann
 * @since Version 1.0
 * @author Felix Kirchner
 */
int Player::rollDice() // Zufallszahl zwischen eins - sechs.
{
    return System::randomizer(6);
}

/**
 * @brief Methode, welche den Benutzer eine Spielfigur auswaehlen laesst.
 * Die Figuren 0 - 3 werden mit dem aktuellen Feld und der Distanz zum Ziel ausgegeben.
 * Die Formulierung ändert sich, je nach dem, wie viele Felder es noch zum Ziel sind.
 * Des weiteren gibt es eine Ueberpruefung des Inputs, welcher nur ein Integer zwischen 0 und 3 sein darf.
 * @see PlayersTurn
 * @return Es wird der Index der Figur zurueckgegeben, welche ausgewaehlt wurde.
 * @pre Es muss ein Player-Objekt geben.
 * @since Version 1.3
 * @author Felix Kirchner
 */
int Player::selectToken()
{
    std::cout << std::endl;
    std::cout << "[System]: Waehle eine Figur, die du Bewegen willst: " << std::endl;
    for (int i = 0; i < 4; i++)
    {
        std::cout << "[" << i << "] - Figur " << i << " [Feld:" << std::setw(3) << currentField.at(i);
        if (40 - distance.at(i) < 0)
            std::cout << " | Noch 0 Feld/-er bis ins Ziel]" << std::endl;
        else if (40 - distance.at(i) == 1)
            std::cout << " | Noch " << 40 - distance.at(i) << " Feld bis ins Ziel]" << std::endl;
        else
            std::cout << " | Noch " << 40 - distance.at(i) << " Felder bis ins Ziel]" << std::endl;
    }

    int FigurIndex;
    std::cin >> FigurIndex; // Spieler wählt Index

    while (std::cin.fail() || FigurIndex > 3 || FigurIndex < 0) // Solange die Eingabe falsch ist.
    {
        if (FigurIndex > 3 || FigurIndex < 0) //
        {
            std::cout << "[System]: Figur " << FigurIndex << " existiert nicht" << std::endl;
            std::cout << "[System]: Bitte geben Sie eine existierende Figur ein:" << std::endl;
            std::cin.clear();
            std::cin >> FigurIndex; // Spieler wählt Index
            std::cin.ignore();
        }
        else if (std::cin.fail())
        {
            std::cout << "[System]: Eingabe konnte nicht erkannt werden." << std::endl;
            std::cout << "[System]: Bitte geben Sie die Figur erneut ein:" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin >> FigurIndex; // Spieler wählt Index
            std::cin.ignore();
        }
    };
    return FigurIndex;
}

/**
 * @brief Methode, welche eine zufaellige Figur aus dem Lager auswaehlt und den Index dieser Figur zurueckgibt.
 * Es wird ein temporaerer Vektor erstellt, an welchen alle Indezes der Figuren angehaengt werden, welche sich im Lager befinden.
 * Es wird dann ein zufaelliger Index des Vektors ausgewaehlt und der sich an dieser Stelle befindende Figur-Index wird zurueckgegeben.
 * @see randomizer
 * @return Es wird ein Integer zurueckgegeben, welcher den Figur-Index der zufaellig ausgewaehlten Figur darstellt.
 * @pre Es muessen Figuren im Lager vorhanden sein.
 * @since Version 1.0
 * @author Felix Kirchner
 */
int Player::randomFromStorage()
{
    std::vector<int> tempVec;
    for (unsigned int i = 0; i < currentField.max_size(); i++) // Geht die Positionen der 4 Spielfiguren eines Spielers durch.
        if (tokenInStorage(i)) // Checkt ob die Spielfigur sich im Lager befindet
            tempVec.push_back(i); // Fuegt den Index der startingFieldfiguren in ein Veektor ein.
    return tempVec.at((System::randomizer(tempVec.size())) - 1); // DOC WIP
}

/**
 * @brief // Methode, welche eine zufaellige Figur aus dem Spielfeld auswaehlt und den Index dieser Figur zurueckgibt.
 * Es wird ein temporaerer Vektor erstellt, an welchen alle Indezes der Figuren angehaengt werden, welche sich im Spielfeld befinden.
 * Es wird dann ein zufaelliger Index des Vektors ausgewaehlt und der sich an dieser Stelle befindende Figur-Index wird zurueckgegeben.
 * @see randomizer
 * @return Es wird ein Integer zurueckgegeben, welcher den Figur-Index der zufaellig ausgewaehlten Figur darstellt.
 * @pre Es muessen Figuren im Spielfeld sein.
 * @since Version 1.1
 * @author Felix Kirchner
 */
int Player::randomFromArena()
{
    std::vector<int> tempVec;
    for (unsigned int i = 0; i < currentField.max_size(); i++) // Geht die Positionen der 4 Spielfiguren eines Spielers durch.
    {
        if (!tokenInStorage(i) && tokenInTargetField(i)) // Überprüft ob die Figur an Index i nicht im Lager und nicht im Ziel ist (also im Spielfeld ist)
        {
            tempVec.push_back(i);
        }
    }
    return tempVec.at((System::randomizer(tempVec.size())) - 1); // Die Groesse des Vektors wird als obere Grenze für eine Zufallsgenerator startend bei 1 benutzt, welche durch "-1" als Index des currentField-Arrays dient
}

/**
 * @brief Methode, welche ueberprüft, ob eine Figur am jeweiligen Index im Lager ist.
 * Es wird geprueft, ob das aktuelle Feld der Figur an Index i den gleichen Feldwert hat, wie das Lager.
 * @param i Index der Figur, fuer welche ueberprueft wird.
 * @return Wahrheitswert der im Falle, dass die Figur sich im Lager befindet true ist, andernfalls false.
 * @pre Es muss ein Player-Objekt geben.
 * @since Version 1.1
 * @author Felix Kirchner
 */
bool Player::tokenInStorage(int i)
{
    if (currentField.at(i) == Storage)
        return true;
    return false;
}

/**
 * @brief Methode, welche ueberprüft, ob eine Figur am jeweiligen Index auf dem Spielfeld ist.
 * Es wird geprueft, ob das aktuelle Feld der Figur an Index i nicht kein Zielfeld und nicht das Lager ist.
 * @param i Index der Figur, fuer welche ueberprueft wird.
 * @see tokenInTargetField, tokenInStorage
 * @return Wahrheitswert der im Falle, dass die Figur sich im Spielfeld befindet true ist, andernfalls false.
 * @pre Es muss ein Player-Objekt geben.
 * @since Version 1.0
 * @author Felix Kirchner
 */
bool Player::tokenInArena(int i)
{
    if (!(tokenInTargetField(i)) && !(tokenInStorage(i)))
        return true;
    return false;
}

/**
 * @brief Methode, welche ueberprüft, ob eine Figur am jeweiligen Index in einem der Zielfelder ist.
 * Es wird geprueft, ob das aktuelle Feld der Figur an Index i eines der Zielfelder ist.
 * @param i Index der Figur, fuer welche ueberprueft wird.
 * @see tokenInTargetField, tokenInStorage
 * @return Wahrheitswert der im Falle, dass die Figur sich in einem der Zielfelder befindet true ist, andernfalls false.
 * @pre Es muss ein Player-Objekt geben.
 * @since Version 1.0
 * @author Felix Kirchner
 */
bool Player::tokenInTargetField(int i)
{
    if ((currentField.at(i) == targetFields.at(0)) ||
        (currentField.at(i) == targetFields.at(1)) ||
        (currentField.at(i) == targetFields.at(2)) ||
        (currentField.at(i) == targetFields.at(3)))
        return true;
    return false;
}

/**
 * @brief Methode, welche ueberprüft, ob alle Spielfiguren im Lager sind.
 * Es wird die Methode "tokenInStorage" fuer alle vier Indizes der Spielfiguren ausgefuehrt.
 * @see tokenInStorage
 * @return Wahrheitswert der im Falle, dass sich alle Figuren im Lager befinden true ist, andernfalls false.
 * @pre Es muss ein Player-Objekt geben.
 * @since Version 1.0
 * @author Felix Kirchner
 */
bool Player::allTokenInStorage()
{
    if (tokenInStorage(0) &&
        tokenInStorage(1) &&
        tokenInStorage(2) &&
        tokenInStorage(3))
        return true;
    return false;
}

/**
 * @brief Methode, welche ueberprüft, ob alle Spielfiguren im Spielfeld sind.
 * Es wird die Methode "tokenInArena" fuer alle vier Indizes der Spielfiguren ausgefuehrt.
 * @see tokenInArena
 * @return Wahrheitswert der im Falle, dass sich alle Figuren im Spielfeld befinden true ist, andernfalls false.
 * @pre Es muss ein Player-Objekt geben.
 * @since Version 1.0
 * @author Felix Kirchner
 */
bool Player::allTokenInArena()
{
    if (tokenInArena(0) &&
        tokenInArena(1) &&
        tokenInArena(2) &&
        tokenInArena(3))
        return true;
    return false;
}

/**
 * @brief Methode, welche ueberprüft, ob alle Spielfiguren in einem der Zielfelder sind.
 * Es wird die Methode "tokenInTargetField" fuer alle vier Indizes der Spielfiguren ausgefuehrt.
 * @see tokenInArena
 * @return Wahrheitswert der im Falle, dass sich alle Figuren im Spielfeld befinden true ist, andernfalls false.
 * @pre Es muss ein Player-Objekt geben.
 * @since Version 1.0
 * @author Felix Kirchner
 */
bool Player::allTokenInTargetField()
{
    if (tokenInTargetField(0) &&
        tokenInTargetField(1) &&
        tokenInTargetField(2) &&
        tokenInTargetField(3))
        return true;
    return false;
}

/**
 * @brief Methode, welche ueberprueft, ob mindestens eine Spielfigur im Lager ist.
 * Es wird anhand der "tokenInStorage" fuer alle vier Spielfiguren ueberprueft, ob sie sich im Lager befinden.
 * Sobald die erste Spielfigur gefunden wurde, wird true zurueckgegeben.
 * Wenn fuer keine Spielfigur festgestellt wird, dass sie sich im Lager befindet, wird false zurueckgegeben.
 * @see tokenInStorage
 * @return Wahrheitswert der im Falle, dass sich mindestens eine Figur im Spielfeld befinden true ist, andernfalls false.
 * @pre Es muss ein Player-Objekt geben.
 * @since Version 1.2
 * @author Felix Kirchner
 */
bool Player::minOneInStorage()
{
    for (unsigned int i = 0; i < currentField.max_size(); i++)
        if (tokenInStorage(i))
            return true;
    return false;
}

/**
 * @brief Methode, welche ueberprueft, ob mindestens eine Spielfigur im Spielfeld ist.
 * Es wird geprueft, ob die Figur an Index i weder in einem Zielfeld noch im Lager ist. Dieses wird fuer alle Figuren aus dem currentField-Array probiert.
 * Sobald die erste Spielfigur gefunden wurde, wird true zurueckgegeben.
 * Wenn fuer keine Spielfigur festgestellt wird, dass sie sich im Spielfeld befindet, wird false zurueckgegeben.
 * @see tokenInTargetField, tokenInStorage
 * @return Wahrheitswert der im Falle, dass sich mindestens eine Figur im Spielfeld befinden true ist, andernfalls false.
 * @pre Es muss ein Player-Objekt geben.
 * @since Version 1.2
 * @author Felix Kirchner
 */
bool Player::minOneInArena()
{
    for (unsigned int i = 0; i < currentField.max_size(); i++) // Geht das currentField-Array durch
        if (!(tokenInTargetField(i)) && !(tokenInStorage(i)))  // Ist Figur nicht im Ziel und nicht im Lager
            return true;
    return false;
}

/**
 * @brief Methode, welche ueberprueft, ob mindestens eine Spielfigur in einem der Zielfelder ist.
 * Es wird anhand der "tokenInTargetField" fuer alle vier Spielfiguren ueberprueft, ob sie sich in einem der Zielfelder befinden.
 * Sobald die erste Spielfigur gefunden wird, wird true zurueckgegeben.
 * Wenn fuer keine Spielfigur festgestellt wird, dass sie sich im Lager befindet, wird false zurueckgegeben.
 * @see tokenInTargetField
 * @return Wahrheitswert der im Falle, dass sich mindestens eine Figur in einem der Zielfelder befinden true ist, andernfalls false.
 * @pre Es muss ein Player-Objekt geben.
 * @since Version 1.2
 * @author Felix Kirchner
 */
bool Player::minOneInTargetField()
{
    if (tokenInTargetField(0) ||
        tokenInTargetField(1) ||
        tokenInTargetField(2) ||
        tokenInTargetField(3))
        return true;
    return false;
}