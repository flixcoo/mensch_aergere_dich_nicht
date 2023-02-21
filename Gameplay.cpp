#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <iomanip>
#include <unistd.h>

#include "Player.hpp"
#include "Gameplay.hpp"
#include "Gameboard.hpp"

/**
 * @brief Methode, die eine Runde des Spiels ausfuehrt.
 * Es werden diverse Konsolenausgaben zur Orientierung der Spieler ausgegeben und jeweils gewuerfelt und die jeweiligen Spieler drangenommen,
 * sodass quasi eine Runde des Spiels gespielt wird.
 * @param playerObj1 Player-Objekt des Spielers, der als erster am Zug ist.
 * @param playerObj2 Player-Objekt des Spielers, der als zweiter am Zug ist.
 * @param playerObj3 Player-Objekt des Spielers, der als dritter am Zug ist.
 * @param playerObj4 Player-Objekt des Spielers, der als vierter am Zug ist.
 * @param gameboardObj Gameboard-Objekt des Spielfeldes.
 * @see printBoard, playersTurn
 * @return Die Methode hat keinen Rueckgabewert.
 * @pre Es muss vier Player-Objekte und ein Gameboard-Objekt geben.
 * @since Version 1.2
 * @author Felix Kirchner
 */
void Gameplay::playOneRound(Player &playerObj1, Player &playerObj2, Player &playerObj3, Player &playerObj4, Gameboard &gameboardObj) // Jeder Spieler ist einmal am Zug
{
    std::cout << "[System]: Spieler 1 ist an der Reihe, bitte bestaetige mit Enter." << std::endl;
    std::cin.ignore();
    int diceNumber;
    printBoard(playerObj1, playerObj2, playerObj3, playerObj4, gameboardObj);
    std::cout << std::endl
              << "--------- Spieler 1 ---------" << std::endl
              << std::endl;

    diceNumber = playerObj1.rollDice();
    playersTurn(diceNumber, playerObj1, playerObj2, playerObj3, playerObj4, gameboardObj); // Runde von Spieler 1

    std::cout << "[System]: Dein Zug ist beendet, Spieler 2 bestaetige mit Enter." << std::endl;
    std::cin.ignore();
    printBoard(playerObj2, playerObj3, playerObj4, playerObj1, gameboardObj);
    std::cout << std::endl
              << "--------- Spieler 2 ---------" << std::endl
              << std::endl;

    diceNumber = playerObj2.rollDice();
    playersTurn(diceNumber, playerObj2, playerObj3, playerObj4, playerObj1, gameboardObj); // Runde von Spieler 2

    std::cout << "[System]: Dein Zug ist beendet, Spieler 3 bestaetige mit Enter." << std::endl;
    std::cin.ignore();
    printBoard(playerObj3, playerObj4, playerObj1, playerObj2, gameboardObj);
    std::cout << std::endl
              << "--------- Spieler 3 ---------" << std::endl
              << std::endl;

    diceNumber = playerObj3.rollDice();
    playersTurn(diceNumber, playerObj3, playerObj4, playerObj1, playerObj2, gameboardObj); // Runde von Spieler 3

    std::cout << "[System]: Dein Zug ist beendet, Spieler 4 bestaetige mit Enter." << std::endl;
    std::cin.ignore();
    printBoard(playerObj4, playerObj1, playerObj2, playerObj3, gameboardObj);
    std::cout << std::endl
              << "--------- Spieler 4 ---------" << std::endl
              << std::endl;

    diceNumber = playerObj4.rollDice();
    playersTurn(diceNumber, playerObj4, playerObj1, playerObj2, playerObj3, gameboardObj); // Runde von Spieler 4

    printBoard(playerObj1, playerObj2, playerObj3, playerObj4, gameboardObj);
}

/**
 * @brief Methode welche einen Spielzug mit einem aktiven  Spieler und drei passiven Spielern darstellt.
 * Es werden alle Faelle die bei einem Spieler eintreffen koennen behandelt, wobei es den aktiven Spieler und 3 weitere passive Spieler gibt.
 * Fuer den aktiven Spieler werden diverse Abfragen getroffen um sein moegliches Verhalten zu bestimmen.
 * @param diceNumber Die Wuerfelzahl.
 * @param playerObj1 Player-Objekt des ersten (aktiven) Spielers.
 * @param playerObj2 Player-Objekt des zweiten (passiven) Spielers.
 * @param playerObj3 Player-Objekt des dritten (passiven) Spielers.
 * @param playerObj4 Player-Objekt des vierten (passiven) Spielers.
 * @param gameboardObj Gameboard-Objekt des Spielfeldes.
 * @see minOneInStorage, moveToken, printBoard, randomFromStorage, get_identifier, rollDice, tokenMovable
 * @return Die Methode hat keinen Rueckggabewert.
 * @pre Es muss vier Player-Objekte und ein Gameboard-Objekt geben sowie muss die Wuerfelzahl positiv sein.
 * @since Version 1.2
 * @author Felix Kirchner
 */
void Gameplay::playersTurn(int diceNumber, Player &playerObj1, Player &playerObj2, Player &playerObj3, Player &playerObj4, Gameboard &gameboardObj) // Zug fuer jeweils einen Spieler und seine Gegner
{

    if (diceNumber == 6) // 6 Gewuerfelt
    {
        std::cout << "[S" << playerObj1.get_identifier() << "]: Du hast eine 6 gewuerfelt, WOW!" << std::endl;
        std::cin.ignore();
        if (playerObj1.minOneInStorage()) // 6 gewuerfelt && alle sind im Lager
        {
            std::cout << "[S" << playerObj1.get_identifier() << "]: Es ist mindestens eine Figur im Lager." << std::endl;
            std::cin.ignore();
            int TokenIndex = playerObj1.randomFromStorage();
            std::cout << "[S" << playerObj1.get_identifier() << "]: Figur " << TokenIndex << " wurde zufaellig bestimmt." << std::endl;
            moveToken(diceNumber, TokenIndex, playerObj1, playerObj2, playerObj3, playerObj4, gameboardObj);

            printBoard(playerObj1, playerObj2, playerObj3, playerObj4, gameboardObj);

            std::cout << "[S" << playerObj1.get_identifier() << "]: Du hast eine 6 gewuerfelt und darfst deshalb nochmal wuerfeln." << std::endl;
            std::cin.ignore();
            int diceNumber = playerObj1.rollDice();
            if (diceNumber != 6)
            {
                std::cout << "[S" << playerObj1.get_identifier() << "]: Du hast eine " << diceNumber << " gewuerfelt." << std::endl;
            }
            std::cin.ignore();
            playersTurn(diceNumber, playerObj1, playerObj2, playerObj3, playerObj4, gameboardObj);
        }
        else // 6 Gewuerfelt && keiner ist im Lager
        {
            std::cout << "[S" << playerObj1.get_identifier() << "]: Es ist keine Figur im Lager." << std::endl;
            std::cin.ignore();
            if (tokenMovable(diceNumber, playerObj1, gameboardObj))
            {
                std::cin.ignore();
                int TokenIndex = playerObj1.selectToken();
                moveToken(diceNumber, TokenIndex, playerObj1, playerObj2, playerObj3, playerObj4, gameboardObj);

                std::cout << "[S" << playerObj1.get_identifier() << "]: Du hast eine 6 gewuerfelt und darfst deshalb nochmal wuerfeln" << std::endl;
                int diceNumber = playerObj1.rollDice();
                std::cin.ignore();
                playersTurn(diceNumber, playerObj1, playerObj2, playerObj3, playerObj4, gameboardObj);
            }
            std::cout << "[S" << playerObj1.get_identifier() << "]: Keiner deiner Spieler ist bewegbar. Dein Zug wird abgebrochen." << std::endl;
        }
    }
    else if (playerObj1.allTokenInStorage()) // Keine 6 gewuerfelt & alle sind im Lager
    {
        std::cout << "[S" << playerObj1.get_identifier() << "]: Du hast eine " << diceNumber << " gewuerfelt." << std::endl;
        std::cin.ignore();
        std::cout << "[S" << playerObj1.get_identifier() << "]: Alle deiner Figuren sind noch im Lager." << std::endl;
        std::cin.ignore();
        std::cout << "[S" << playerObj1.get_identifier() << "]: Da du keine 6 gewuerfelt hast und alle deiner Spieler noch im Lager sind, darfst du noch 2 weitere male wuerfeln." << std::endl;
        std::cin.ignore();
        for (int i = 2; i > 0; i--)
        {
            int diceNumber = playerObj1.rollDice();
            if (diceNumber == 6)
            {
                playersTurn(6, playerObj1, playerObj2, playerObj3, playerObj4, gameboardObj);
                break;
            }
            else
            {
                std::cout << "[S" << playerObj1.get_identifier() << "]: Du hast eine " << diceNumber << " gewuerfelt." << std::endl;
                std::cin.ignore();
                std::cout << "[S" << playerObj1.get_identifier() << "]: Weitere Versuche: " << i - 1 << std::endl;
                std::cin.ignore();
            }
        }
    }
    else if (playerObj1.minOneInArena() || playerObj1.minOneInTargetField()) // Keine 6 gewuerfelt & mindestens einen im Spielfeld
    {
        std::cout << "[S" << playerObj1.get_identifier() << "]: Du hast eine " << diceNumber << " gewuerfelt." << std::endl;
        std::cout << "[S" << playerObj1.get_identifier() << "]: Du hast mindestens einen Spieler im Spielfeld." << std::endl;
        std::cin.ignore();
        if (tokenMovable(diceNumber, playerObj1, gameboardObj))
        {
            int TokenIndex = playerObj1.selectToken();

            while (playerObj1.get_currentField().at(TokenIndex) == "X") // Ueberpruefung, ob die geweahlte Figur im Lager ist, waehrend man keine 6 gewuerfelt hat.
            {
                std::cout << "[S" << playerObj1.get_identifier() << "] "
                          << "Die ausgewaehlte Figur ist im Lager. Da du keine 6 gewuerfelt hast, kannst du diese Figur nicht bewegen." << std::endl;
                TokenIndex = playerObj1.selectToken();
            }

            moveToken(diceNumber, TokenIndex, playerObj1, playerObj2, playerObj3, playerObj4, gameboardObj);
        }
        else
        {
            std::cout << "[S" << playerObj1.get_identifier() << "]: Keiner deiner Spieler ist bewegbar. Dein Zug wird abgebrochen." << std::endl
                      << std::endl;
            std::cin.ignore();
            return;
        }
    }
    else // Wird zu dem dadrueber
    {
        std::cout << "[Debug]: diceNumber: " << diceNumber << std::endl;
        std::cout << "[Debug]: minOneinTargetField: " << playerObj1.minOneInTargetField() << std::endl;
        std::cout << "[Debug]: minOneInArena: " << playerObj1.minOneInArena() << std::endl;
        std::cout << "[error]: 404. Case missing. >:(" << std::endl
                  << std::endl;
        std::cin.ignore();
    }
}

/**
 * @brief Methode, welche die Spielfigur bewegt und dabei alle Faelle und Situationen beachtet.
 * Es werden der Index des Startfeldes und des neuen Feldes gesetzt.
 * Dann wird in die Faelle unterschieden, ob die zu bewegende Figur im Lager ist und eine sechs gewuerfelt wurde oder nicht.
 * Danach werden diverse Ueberpruefungen angewandt um die Hindernisse der Spielfigur zu erkennen.
 * @param diceNumber Die gewuerfelte Zahl.
 * @param TokenIndex Die zu bewegende Spielfigur.
 * @param playerObj1 Player-Objekt des ersten (aktiven) Spielers.
 * @param playerObj2 Player-Objekt des zweiten (passiven) Spielers.
 * @param playerObj3 Player-Objekt des dritten (passiven) Spielers.
 * @param playerObj4 Player-Objekt des vierten (passiven) Spielers.
 * @param gameboardObj Gameboard-Objekt des Spielfeldes.
 * @see Referenz auf andere Funktion, die „hnliches macht oder dazu geh”rt
 * @return Die Methode hat keinen Rueckggabewert.
 * @pre Die gegebene Figur muss bewegbar sein.
 * @since Version 1.3
 * @author Felix Kirchner
 */
void Gameplay::moveToken(int diceNumber, int TokenIndex, Player &playerObj1, Player &playerObj2, Player &playerObj3, Player &playerObj4, Gameboard &gameboardObj) // Bewegung der Figur
{
    int SFI = determineStartingFieldIndex(TokenIndex, playerObj1, gameboardObj); // StartingFieldIndex
    int NFI;                                                                     // NewFieldIndex

    if (playerObj1.get_currentField().at(TokenIndex) == "X" && diceNumber == 6) // Ueberpruefung, wenn die Figur im Lager ist und man eine 6 gewuerfelt hat.
    {

        if (ownTokenOnNewField(TokenIndex, SFI, playerObj1, gameboardObj) == TokenIndex) // Ist eine Figur auf dem neuen Feld (also dem Starfeld der Spielfigur)?
        {
            std::cout << "[S" << playerObj1.get_identifier() << "]: Figur " << TokenIndex << " wird auf dein Startfeld gesetzt." << std::endl;
            std::cin.ignore();
            NFI = SFI; // NFI bleibt SFI, da die Figur nur auf ihr erstes Feld geht.
            diceNumber = 0;
        }
        else if (ownTokenOnNewField(TokenIndex, SFI, playerObj1, gameboardObj) != TokenIndex)
        {
            std::cout << "[S" << playerObj1.get_identifier() << "]: Auf deinem Startfeld steht deine eigene Figur!" << std::endl;
            std::cout << "[S" << playerObj1.get_identifier() << "]: Diese Figur muss zuerst bewegt werden." << std::endl;
            std::cin.ignore();

            TokenIndex = ownTokenOnNewField(TokenIndex, SFI, playerObj1, gameboardObj);
            std::cout << "[S" << playerObj1.get_identifier() << "]: Figur " << TokenIndex << " wurde automatisch fuer dich ausgeweahlt." << std::endl;
            moveToken(diceNumber, TokenIndex, playerObj1, playerObj2, playerObj3, playerObj4, gameboardObj);

            return;
        }
    }

    NFI = SFI + diceNumber;                   // Index des neuen Feldes auf Spielbrett, ergibt sich aus dem Index des Feldes wo man gestartet ist  (SFI) + der diceNumber
    NFI = beyondGameboard(NFI, gameboardObj); // Korrektur NFI

    if (NFI != inForeignTargetField(NFI, playerObj1, playerObj2, playerObj3, playerObj4, gameboardObj)) // Korektur NFI
    {
        NFI = inForeignTargetField(NFI, playerObj1, playerObj2, playerObj3, playerObj4, gameboardObj);
        NFI = beyondGameboard(NFI, gameboardObj); // Korrektur NFI nach InFremdenZield
    }
    else if (diceNumber > 4) // Wenn nicht Korrigiert wird, gucke ob die hinteren Felder ein Zielfeld waren
    {
        for (int i = 1; i < diceNumber; i++) // For-Schleife fuer die diceNumber
        {
            std::cout << "i ist " << i << std::endl;
            if (NFI - i != inForeignTargetField(NFI - i, playerObj1, playerObj2, playerObj3, playerObj4, gameboardObj)) // Ist der NFI - i (1,...,diceNumber) ein Zielfeld?
            {
                NFI = NFI + 4;                            // NFI wird korrigiert, da man ansonsten die Zielfelder als regulaere gameboarder zaehlen wuerde.
                NFI = beyondGameboard(NFI, gameboardObj); // Korrektur NFI falls noetig
            }
        }
    }
    if (beyondTargetField(diceNumber, TokenIndex, playerObj1, gameboardObj)) // Bin ich ueber das Ziel hinaus?
    {
        std::cin.ignore();
        int TokenIndex = playerObj1.selectToken();
        moveToken(diceNumber, TokenIndex, playerObj1, playerObj2, playerObj3, playerObj4, gameboardObj);
        return;
    }

    if (ownTokenOnNewField(TokenIndex, NFI, playerObj1, gameboardObj) != TokenIndex) // Ist eine Figur auf dem neuen Feld?
    {
        std::cout << "[S" << playerObj1.get_identifier() << "]: Deine eigene Figur steht auf dem Feld auf das du willst." << std::endl
                  << std::endl;
        std::cin.ignore();
        int TokenIndex = playerObj1.selectToken();
        moveToken(diceNumber, TokenIndex, playerObj1, playerObj2, playerObj3, playerObj4, gameboardObj);
        return;
    }

    playerOnNewField(NFI, playerObj1, playerObj2, playerObj3, playerObj4, gameboardObj); // Spieler werden ggf. wieder zurueck ins Lager gesetzt.
    std::string newField = gameboardObj.get_board().at(NFI);                             // Das neue Feld wird aus dem Spielbrett gelesen
    playerObj1.get_currentField().at(TokenIndex) = newField;                             // Das neue Feld wird der Figur im Array zugewiesen
    playerObj1.get_distance().at(TokenIndex) += diceNumber;                              // Die Distanz wird erhoeht
    newField = playerObj1.get_currentField().at(TokenIndex);                             // Das neue Feld wird aktualisiert
}

/**
 * @brief Methode, die ueberprueft, ob ein Spieler mit der aktuell gewuerfelten Zahl bewegbare Figuren hat
 * Es wird geschaut, ob eine Figur bewegbar ist, anhand verschiedener Operationen.
 * Wenn keine dieser Abfragen zutrifft, wird die Anzahl der Figuren die bewegbar sind um eine erhoeht.
 * Wenn am Ende, nachdem alle Figuren abgegangen wurden, die Anzahl der bewegbaren Figuren groesser als 0 ist, wird wahr zurueckgegeben, ansonsten falsch.
 * @param diceNumber Funktion des Parameters 1
 * @param playerObj1 Player-Objekt des ersten (aktiven) Spielers.
 * @param gameboardObj Gameboard-Objekt des Spielfeldes.
 * @see beyondGameboard, ownTokenOnNewField, beyondTargetField, tokenInStorage
 * @return Es wird ein Wahrheitswert fuer die Aussage, ob es bewegbare Figuren gibt, zurueckgegeben.
 * @pre Es sollte bewegbare Figuren geben.
 * @since Version 1.4
 * @author Felix Kirchner
 */
bool Gameplay::tokenMovable(int diceNumber, Player &playerObj, Gameboard &gameboardObj) // Sind die Figuren eines Spielers bewegbar
{
    int movableCount = 0;
    for (unsigned int TokenIndex = 0; TokenIndex < playerObj.get_currentField().max_size(); TokenIndex++)
    {
        if (!(playerObj.get_currentField().at(TokenIndex) == "X") || diceNumber == 6) // Wenn die angegebene Figur nicht im Lager ist oder man eine 6 gewuerfelt hat
        {
            int SFI = determineStartingFieldIndex(TokenIndex, playerObj, gameboardObj);
            int NFI = SFI + diceNumber; // Index des neuen Feldes auf Spielbrett, ergibt sich aus dem Index des Feldes wo man gestartet ist  (SFI) + der diceNumber
            if (beyondGameboard(NFI, gameboardObj) != NFI)
                NFI = beyondGameboard(NFI, gameboardObj);
            if (beyondTargetField(diceNumber, TokenIndex, playerObj, gameboardObj))
            {
                // Figur nicht bewegbar
            }
            else if (ownTokenOnNewField(TokenIndex, NFI, playerObj, gameboardObj) != (int)TokenIndex)
            {
                // Figur nicht bewegbar
            }
            else if (playerObj.tokenInStorage(TokenIndex) && diceNumber != 6)
            {
                // Figur nicht bewegbar
            }
            else
            {
                movableCount++;
            }
        }
    }
    if (movableCount > 0)
        return true;
    return false;
}

/**
 * @brief Methode, die ueberprueft, ob eine Spielfigur ueber ihre Zielfelder hinaus gelaufen ist.
 * Es wird geprueft, ob die Distanz einer Figur addiert der gewuerfelten Zahl groeáer als 43 (der maximalen Distanz einesr Figur) ist.
 * Es wird wahr zurueckgegeben, wenn diese Aussage zutrifft und falsch, wenn Sie nicht zutrifft.
 * @param diceNumber Funktion des Parameters 1
 * @param TokenIndex Funktion des Parameters 2
 * @param playerObj Player-Objekt des aktiven Spielers.
 * @param gameboardObj Gameboard-Objekt des Spielfeldes.
 * @see get_distance
 * @return Wahrheitswert der Aussage, ob die Distanz der Figur addiert der gewuerfelten Zahl groesser 43 ist.
 * @pre Die Distanz der Figur muss korrekt sein.
 * @since Version 1.2
 * @author Felix Kirchner
 */
bool Gameplay::beyondTargetField(int diceNumber, int TokenIndex, Player &playerObj, Gameboard &gameboardObj) // Schaut ob die gelaufene Distanz einer Figur groesser ist als 44 (zweite Runde) und uebergibt einen Wahrheitswert
{
    if ((playerObj.get_distance().at(TokenIndex) + diceNumber > 43)) // Ist Figur an TokenIndex schon mehr als 44 Felder gelaufen?
        return true;                                                 // Wenn ja, return true
    return false;                                                    // wenn nein, return false
}

/**
 * @brief Methode, welche ueberprueft, ob ein Spieler ueber das Spielbrett hinaus gegangen ist.
 * Die Methode ueberprueft, ob der NFI groeáer ist als die Groeáe des board-Arrays.
 * Wenn das der Fall ist, wird 56 vom NFI abgezogen, damit der Spieler quasi wieder von unten in das Spielfeld reinlaeuft.
 * @param NFI Index des neuen Feldes
 * @param gameboardObj Gameboard-Objekt des Spielfeldes.
 * @see get_board
 * @return Zurrueckgegeben wird der NFI, entweder in korrigierter Form oder wie urspruenglich eingegeben.
 * @pre Das Spielfeld muss 56 Zeichen gross sein.
 * @since Version 1.2
 * @author Felix Kirchner
 */
int Gameplay::beyondGameboard(int NFI, Gameboard &gameboardObj) // Ueberprueft, ob ich ueber das Spielfeld-Array hinaus bin
{

    if ((unsigned int)NFI >= gameboardObj.get_board().max_size()) // Ist mein TokenIndex groesser als mein Spielfeld
        return NFI - 56; // Groesse des Spielbrettes wird vom Index abgezogen
    else
        return NFI; // Das neue Feld liegt im Array, also wird es einfach zurueckgegeben.
}

/**
 * @brief Methode, welche ueberprueft, ob ein Spieler in einem der Zielfelder der anderen Spieler gelandet ist.
 * Fuer jeden der passiven Spieler wird geschaut, ob das neue Feld des ersten aktiven Spielers eines der Zielfelder der anderen Spieler ist.
 * Wenn dies der Fall ist, wird der Index des neuen Feldes um vier erhoeht.
 * Zurueckgegeben wird der korrigierte NFI. Falls dieser nicht korrigiert wird im Verlauf der Methode, wird die vorherige Eignabe des NFIs zurueckgegeben.
 * @param diceNumber Die gewuerfelte Zahl.
 * @param NFI Der Index des neuen Feldes (NewFieldIndex)
 * @param playerObj1 Player-Objekt des ersten (aktiven) Spielers.
 * @param playerObj2 Player-Objekt des zweiten (passiven) Spielers.
 * @param playerObj3 Player-Objekt des dritten (passiven) Spielers.
 * @param playerObj4 Player-Objekt des vierten (passiven) Spielers.
 * @param gameboardObj Gameboard-Objekt des Spielfeldes.
 * @see get_targetFields, get_board
 * @return Der NFI als Integer, dessen Wert das neue Feld des Spielers bestimmt.
 * @pre Der NFI muss sich im Spielfeld befinden.
 * @since Version 1.3
 * @author Felix Kirchner
 */
int Gameplay::inForeignTargetField(int NFI, Player &playerObj1, Player &playerObj2, Player &playerObj3, Player &playerObj4, Gameboard &gameboardObj) // Bin ich in einem fremden Zielfeld gelandet?
{
    for (unsigned int i = 0; i < playerObj2.get_targetFields().max_size(); i++)
    {
        if (playerObj2.get_targetFields().at(i) == gameboardObj.get_board().at(NFI)) // Ist das Neue Feld ein Zielfeld von Spieler2?
        {
            std::cin.ignore();
            NFI = NFI + 4; // Raus aus dem Bereich der Zielfelder von Spieler2
            return NFI;
        }
    }
    for (unsigned int i = 0; i < playerObj3.get_targetFields().max_size(); i++) // Ist das Neue Feld ein Zielfeld von Spieler3?
    {
        if (playerObj3.get_targetFields().at(i) == gameboardObj.get_board().at(NFI))
        {
            NFI = NFI + 4; // Raus aus dem Bereich der Zielfelder von Spieler3
            return NFI;
        }
    }
    for (unsigned int i = 0; i < playerObj4.get_targetFields().max_size(); i++) // Ist das Neue Feld ein Zielfeld von Spieler4?
    {
        if (playerObj4.get_targetFields().at(i) == gameboardObj.get_board().at(NFI))
        {
            NFI = NFI + 4; // Raus aus dem Bereich der Zielfelder von Spieler3
            return NFI;
        }
    }
    return NFI;
}

/**
 * @brief Methode, welche auf eigene Spieler auf dem neuen Feld ueberprueft.
 * Es wird geprueft, ob das Feld an der Stelle NewFieldIndex (NFI) das gleiche ist, wie an einem der Felder auf dem sich die Spielfiguren befinde.
 * Zurueckgegeben wird der Index der Figur die auf diesem Feld steht. Entweder ist es der i - Wert der Vorschleife oder der anfangs eingegebene TokenIndex des zu bewegenden Spielers.
 * @param TokenIndex Index des Spielers, welcher bewegt werden soll.
 * @param playerObj Player-Objekt des aktiven Spielers
 * @param gameboardObj Gameboard-Objekt des Spielfeldes.
 * @see get_board, get_currentField, get_identifier
 * @return Gibt den TokenIndex der Figur, die sich auf dem neuen Feld befindet, zurueck.
 * @pre Alle Spieler muessen auf einem Spielfeld stehen.
 * @since Version 1.3
 * @author Felix Kirchner
 */
int Gameplay::ownTokenOnNewField(int TokenIndex, int NFI, Player &playerObj, Gameboard &gameboardObj) // Ueberprueft, ob eine Figur des aktuellen Spielers auf dem neuen Feld steht
{
    std::string newField = gameboardObj.get_board().at(NFI);
    for (int i = 0; i < (int)playerObj.get_currentField().max_size(); i++)
    {
        if (playerObj.get_currentField().at(i) == newField)
        {
            if (i != (int)TokenIndex)
            {
                std::cout << "[S" << playerObj.get_identifier() << "]: Figur " << i << " muss bewegt werden, da du sonst deine eigene Figur schlagen wuerdest" << std::endl;
                return i; // Wenn ja, gib den Index der Figur zurueck, welche dann stattdesssen bewegt werden muss.
            }
        }
    }
    /*std::cout << "[S" << playerObj.get_identifier() << "]-"
              << "[ownTokenOnNewField]: Passt alles soweit" << std::endl;*/
    return TokenIndex; // Wenn ja, gib den Index der Figur zurueck, welche wir gerade schon bewegen.
}

/**
 * @brief Methode, welche prueft, ob sich ein Spieler auf dem neuen Feld befindet und ihn zurueck ins Lager setzt.
 * Es wird fuer jeden Spieler zwei bis vier geschaut, ob er sich auf dem Index des neuen Feldes von Spieler eins befindet.
 * Wenn das der Fall ist, wird die Figur des Spielers zurueck ins Lager gesetzt und es gibt eine Konsolenausgabe.
 * @param NFI NewFieldIndex: Index des neuen Feldes von Spieler 1
 * @param playerObj1 Player-Objekt des ersten (aktiven) Spielers.
 * @param playerObj2 Player-Objekt des zweiten (passiven) Spielers.
 * @param playerObj3 Player-Objekt des dritten (passiven) Spielers.
 * @param playerObj4 Player-Objekt des vierten (passiven) Spielers.
 * @param gameboardObj Gameboard-Objekt des Spielfeldes.
 * @see get_currentField, get_identifier, get_board
 * @return Die Methode hat keinen Rueckggabewert.
 * @pre NFI muss im board liegen.
 * @since Version 1.2
 * @author Felix Kirchner
 */
void Gameplay::playerOnNewField(int NFI, Player &playerObj1, Player &playerObj2, Player &playerObj3, Player &playerObj4, Gameboard &gameboardObj) // Ist eine andere Spielfigur auf meinem neuen Feld?
{
    for (unsigned int i = 0; i < playerObj2.get_currentField().max_size(); i++)
    {
        if (playerObj2.get_currentField().at(i) == gameboardObj.get_board().at(NFI)) // Ist auf dem neuen Feld eine Figur von Spieler 2?
        {
            playerObj2.get_currentField().at(i) = "X"; // Spieler wird rausgekickt (Position der Figur auf X fuer Lager)

            std::cout << "[S" << playerObj1.get_identifier() << "] "
                      << "Du hast die Figur " << i << " von Spieler " << playerObj2.get_identifier() << " geschlagen." << std::endl;
            std::cin.ignore();

            playerObj2.get_distance().at(i) = 0; // Distanz der Spielfigur wird zurueckgesetzt.

            std::cout << "[S" << playerObj1.get_identifier() << "]: Die Figur von Spieler " << playerObj2.get_identifier() << " ist nun wieder im Lager." << std::endl;
        }
    }
    for (unsigned int i = 0; i < playerObj3.get_currentField().max_size(); i++) // Ist auf dem neuen Feld eine Figur von Spieler 3?
    {
        if (playerObj3.get_currentField().at(i) == gameboardObj.get_board().at(NFI))
        {
            playerObj3.get_currentField().at(i) = "X"; // Spieler wird rausgekickt (Position der Figur auf X fuer Lager)

            std::cout << "[S" << playerObj1.get_identifier() << "] "
                      << "Du hast die Figur " << i << " von Spieler " << playerObj3.get_identifier() << " geschlagen." << std::endl;
            std::cin.ignore();

            playerObj3.get_distance().at(i) = 0; // Distanz der Spielfigur wird zurueckgesetzt.

            std::cout << "[S" << playerObj1.get_identifier() << "]: Die Figur von Spieler " << playerObj3.get_identifier() << " ist nun wieder im Lager." << std::endl;
        }
    }
    for (unsigned int i = 0; i < playerObj4.get_currentField().max_size(); i++) // Ist auf dem neuen Feld eine Figur von Spieler 4?
    {
        if (playerObj4.get_currentField().at(i) == gameboardObj.get_board().at(NFI))
        {
            playerObj4.get_currentField().at(i) = "X"; // Spieler wird rausgekickt (Position der Figur auf X fuer Lager).

            std::cout << "[S" << playerObj1.get_identifier() << "] "
                      << "Du hast die Figur " << i << " von Spieler " << playerObj4.get_identifier() << " geschlagen." << std::endl;
            std::cin.ignore();

            playerObj4.get_distance().at(i) = 0; // Distanz der Spielfigur wird zurueckgesetzt.

            std::cout << "[S" << playerObj1.get_identifier() << "]: Die Figur von Spieler " << playerObj4.get_identifier() << " ist nun wieder im Lager." << std::endl;
        }
    }
}

/**
 * @brief Methode, welche den Index des aktuellen Feldes einer Figur, der dann als Startfeld verwendet wird, bestimmt.
 * Es wird zuerst ueberprueft, ob eine Figur im Lager steht. In diesem Fall wird das Startfeld des Spielers zurueckgegeben.
 * Wenn das nicht der Fall ist, wird nach dem Index des Feldes im "board"-Attribut des Gameboard-Objektes gesucht und dieser Index zurueckgegeben
 * Wenn dies auch nicht der Fall ist, wird ein Fehler in der Konsole ausgegeben und 404 zurueckgegeben.
 * @param TokenIndex Die Figur, dessen Startfeld bestimmt werden sollen.
 * @param playerObj Player-Objekt des betroffenen Spielers.
 * @param gameboardObj Gameboard-Objekt des Spielfeldes.
 * @see determineIndexOfStartingField, get_board, get_currentField
 * @return Gibt den Index der Startfeldes zurueck.
 * @pre Das Spielerobjekt muss fuer die Figur ein Feld enthalten
 * @since Version 1.2
 * @author Felix Kirchner
 */
int Gameplay::determineStartingFieldIndex(int TokenIndex, Player &playerObj, Gameboard &gameboardObj) // Bestimmt den Index auf dem Array Spielbrett, an welcher sich das Startfeld des eingegebenen Spielers befindet.
{
    if (playerObj.tokenInStorage(TokenIndex)) // Wenn das aktuelle Feld der Figur "X" ist
    {
        return determineIndexOfStartingField(playerObj, gameboardObj); // Gebe das Startfeld zurueck
    }
    else // Wenn das aktuelle Feld der Figur nicht "X" ist
    {
        for (unsigned int i = 0; i < gameboardObj.get_board().max_size(); i++) // Gehe das Spielfeld durch
        {
            if (gameboardObj.get_board().at(i) == playerObj.get_currentField().at(TokenIndex)) // Ueberpruefe, ob das Feld an Index i gleich dem aktuellen Feld des Spielers ist
            {
                return i; // Wenn ja, gib den index dieses Feldes zurueck
            }
        }
    }
    std::cout << "[S" << playerObj.get_identifier() << "]-"
              << "[error]: Start field of token " << TokenIndex << " could not be found" << std::endl;
    return 404;
}
/**
 * @brief Methode, die fuer alle vier Spieler ueberprueft, ob mindestens einer von ihnen alle Spielfiguren in den Zielfeldern hat.
 * Fuer alle vier Spieler wird abgefragt, ob Sie alle Spielfiguren in den Zielfeldern haben.
 * Wenn mindestens einer diese Bedingung erfuellt ist, wird true zurueckgegeben, ansonsten false.
 * @param playerObj1 Player-Objekt des ersten Spielers.
 * @param playerObj2 Player-Objekt des zweiten Spielers.
 * @param playerObj3 Player-Objekt des dritten Spielers.
 * @param playerObj4 Player-Objekt des vierten Spielers.
 * @see allTokenInTargetField
 * @return Wahrheitswert, ueber die Aussage, ob mindestens einer der Spieler alle Spielfiguren im Ziel hat.
 * @pre Es muss vier Spielerobjekte geben.
 * @since Version 1.5
 * @author Felix Kirchner
 */
bool Gameplay::endOfGame(Player &playerObj1, Player &playerObj2, Player &playerObj3, Player &playerObj4) // Ueberprueft, ob mindestens ein Spieler alle Figuren im Ziel hat.
{
    if ((playerObj1.allTokenInTargetField() || playerObj2.allTokenInTargetField()) || (playerObj3.allTokenInTargetField() || playerObj4.allTokenInTargetField()))
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * @brief Methode, die das "identifier"-Attribut des Spielers zurueckgibt, der gewonnen hat.
 * Es wird geprueft, ob fuer jeweils Spieler 1 - 4 alle Figuren im Ziel sind.
 * Wenn das der Fall ist, wird fuer den jeweiligen Spieler das "identifier"-Attribut zurueckgegeben.
 * Wird kein Gewinner gefunden, wird 404 zurueckgegeben
 * @param playerObj1 Player-Objekt des ersten Spielers.
 * @param playerObj2 Player-Objekt des zweiten Spielers.
 * @param playerObj3 Player-Objekt des dritten Spielers.
 * @param playerObj4 Player-Objekt des vierten Spielers.
 * @see allTokenInTargetField, get_identifier
 * @return "identifier"-Attribut vom Typ Integer des Spielers der gewonnen hat oder 404 falls kein Spieler ermittelt werden konnte
 * @pre Ein Spieler muss alle vier Spielfiguren in seinen Zielfeldern haben.
 * @since Version 1.0
 * @author Felix Kirchner
 */
int Gameplay::winner(Player &playerObj1, Player &playerObj2, Player &playerObj3, Player &playerObj4)
{
    if (playerObj1.allTokenInTargetField())
    {
        return playerObj1.get_identifier();
    }
    if (playerObj2.allTokenInTargetField())
    {
        return playerObj2.get_identifier();
    }
    if (playerObj3.allTokenInTargetField())
    {
        return playerObj3.get_identifier();
    }
    if (playerObj4.allTokenInTargetField())
    {
        return playerObj4.get_identifier();
    }
    std::cout << "[system]: Winner could not be found" << std::endl;
    return 404;
}

/**
 * @brief Methode, welche den Index der Startfeld eines jeweiligen Spielers auf dem Spielbrett ausfindig macht und zurueckgibt.
 * Es wird das Spielbrett abgegangen und an jedem Index von 0 bis zur max_size des Gameboard-Objektes ueberprueft, ob das aktuelle Feld das Startfeld des Player-Objektes ist.
 * @param playerObj Player-Objekt des Spielers, dessen Startfeld gefunden werden soll.
 * @param gameboardObj Gameboard-Objekt des Spielfeldes Spielers.
 * @see get_board, get_startingField
 * @return Der Index auf dem Gameboard-Objekt, an dem sich das Startfeld befindet bzw. 0, falls er nicht gefunden werden konnte.
 * @pre Das Startfeld muss sich auf dem "board"-Attribut des "Gameboard-Objektes" befinden
 * @post Es gibt das Startfeld des Spielers auf dem Spielfeld.
 * @since Version 1.2
 * @author Felix Kirchner
 */
int Gameplay::determineIndexOfStartingField(Player &playerObj, Gameboard &gameboardObj)
{
    for (unsigned int i = 0; i < gameboardObj.get_board().max_size(); i++) // Gehe das Spielfeld durch
    {
        if (gameboardObj.get_board().at(i) == playerObj.get_startingField()) // Ueberpruefe, ob das Feld an Index i gleich dem Startfeld des Spielers ist
        {
            return i; // Wenn ja, gib den Index vom Startfeld zurueck
        }
    }
    return 404;
}

/**
 * @brief Methode, welche untersucht, ob das Feld an FieldIndex ein Zielfeld vom Player-Objekt ist.
 * Es wird durch die Zielfelder gegangen und fuer jedes Zielfeld ueberprueft ob das Feld an der Stelle FeldIndex im Gameboard-Objekt ein Zielfeld vom Spieler-Objekt ist.
 * Wenn eines der Zielfelder an der Stelle FieldIndex erkannt wird, wird true zurueckgegeben. Wenn das Feld an der Stelle FieldIndex keines der Zielfelder ist, wird false zurueckgegeben.
 * @param FieldIndex Integer, der den Index des untersuchten Feldes darstellt.
 * @param playerObj Player-Objekt des Spielers, auf dessen Zielfelder untersucht wird.
 * @param gameboardObj Gameboard-Objekt des Spielfeldes Spielers.
 * @see get_targetFields, get_board
 * @return Wahrheitswert, der fuer den Spieler wahr ausgibt, wenn das Feld an der Stell FieldIndex eines der Zielfelder des Spielers ist
 * @pre Das Player-Objekt muss Zielfelder enthalten.
 * @since Version 1.6
 * @author Felix Kirchner
 */
bool Gameplay::isTargetField(int FieldIndex, Player &playerObj, Gameboard &gameboardObj) // Guckt ob ein Feld an einem bestimmten Index das Zielfeld des Spielers ist.
{
    for (unsigned int i = 0; i < playerObj.get_targetFields().max_size(); i++)
    {
        if (gameboardObj.get_board().at(FieldIndex) == playerObj.get_targetFields().at(i))
        {
            return true;
        }
    }
    return false;
}

/**
 * @brief Methode, welche das Spielfeld mit den aktuellen Positionen der Spielfiguren in der Konsole ausgibt.
 * Die Methode gibt in der Konsole fuer jedes Feld auf dem Gameboard-Array jeweils die dort sich befindlichen Spieler aus.
 * Normale Felder werden dabei in runde Klammern gesetzt, Zielfelder in geschweifte Klammern.
 * Vor dem Startfeld eines Spielers wird das Lager mit den sich dort befindlichen Figuren ausgegeben.
 * @param playerObj1 Player-Objekt des ersten Spielers.
 * @param playerObj2 Player-Objekt des zweiten Spielers.
 * @param playerObj3 Player-Objekt des dritten Spielers.
 * @param playerObj4 Player-Objekt des vierten Spielers.
 * @param gameboardObj Gameboard-Objekt des Spielfeldes.
 * @see determineIndexOfStartingField, isTargetField, get_currentField, get_board
 * @return Die Methode hat keinen Rueckggabewert.
 * @pre Es muss vier Player-Objekte und ein Gameboard-Objekt geben
 * @since Version 1.6
 * @author Felix Kirchner
 */
void Gameplay::printBoard(Player &playerObj1, Player &playerObj2, Player &playerObj3, Player &playerObj4, Gameboard &gameboardObj)
{
    std::cout << "[System]: Das Spielfeld wird ausgegeben, bitte besteatige mit Enter.";
    std::cin.ignore();

    std::cout << std::endl
              << "--------- Spielfeld ---------" << std::endl;

    for (int i = 0; i < (int)gameboardObj.get_board().max_size(); i++)
    {
        if (i == determineIndexOfStartingField(playerObj1, gameboardObj)) // Wenn das Feld 0 (Startfeld Spieler 1) ausgegeben werden soll
        {
            std::cout << "Lager S" << playerObj1.get_identifier() << ": ";
            for (unsigned int i = 0; i < playerObj1.get_currentField().max_size(); i++)
                if (playerObj1.get_currentField().at(i) == "X") // Gucke, ob Figuren von Spieler 1 noch im Lager sind
                {
                    std::cout << "Figur" << i << " "; // Wenn ja, gib diese aus
                }
            std::cout << std::endl;
        }

        if (i == determineIndexOfStartingField(playerObj2, gameboardObj)) // Wenn das Feld 10 (Startfeld Spieler 2) ausgegeben werden soll
        {
            std::cout << "Lager S" << playerObj2.get_identifier() << ": ";
            for (unsigned int i = 0; i < playerObj2.get_currentField().max_size(); i++)
                if (playerObj2.get_currentField().at(i) == "X") // Gucke, ob Figuren von Spieler 2 noch im Lager sind
                {
                    std::cout << "Figur" << i << " "; // Wenn ja, gib diese aus
                }
            std::cout << std::endl;
        }

        if (i == determineIndexOfStartingField(playerObj3, gameboardObj)) // Wenn das Feld 20 (Startfeld Spieler 3) ausgegeben werden soll
        {
            std::cout << "Lager S" << playerObj3.get_identifier() << ": ";
            for (unsigned int i = 0; i < playerObj3.get_currentField().max_size(); i++)
                if (playerObj3.get_currentField().at(i) == "X") // Gucke, ob Figuren von Spieler 3 noch im Lager sind
                {
                    std::cout << "Figur" << i << " "; // Wenn ja, gib diese aus
                }
            std::cout << std::endl;
        }

        if (i == determineIndexOfStartingField(playerObj4, gameboardObj)) // Wenn das Feld 30 (Startfeld Spieler 4) ausgegeben werden soll
        {
            std::cout << "Lager S" << playerObj4.get_identifier() << ": ";
            for (unsigned int i = 0; i < playerObj4.get_currentField().max_size(); i++)
                if (playerObj4.get_currentField().at(i) == "X") // Gucke, ob Figuren von Spieler 4 noch im Lager sind
                {
                    std::cout << "Figur" << i << " "; // Wenn ja, gib diese aus
                }
            std::cout << std::endl;
        }

        if (isTargetField(i, playerObj1, gameboardObj) || isTargetField(i, playerObj2, gameboardObj) || isTargetField(i, playerObj3, gameboardObj) || isTargetField(i, playerObj4, gameboardObj))
        {
            std::cout << std::setw(2) << "{" << gameboardObj.get_board().at(i) << "}"
                      << " ";
        }
        else
        {
            std::cout << std::setw(2) << "(" << gameboardObj.get_board().at(i) << ")"
                      << " ";
        }

        for (unsigned int j = 0; j < playerObj1.get_currentField().max_size(); j++)
        {
            if (playerObj1.get_currentField().at(j) == gameboardObj.get_board().at(i))
            {
                std::cout << "< Spieler " << playerObj1.get_identifier() << ", Figur " << j;
            }

            if (playerObj2.get_currentField().at(j) == gameboardObj.get_board().at(i))
            {
                std::cout << "< Spieler " << playerObj2.get_identifier() << ", Figur " << j;
            }

            if (playerObj3.get_currentField().at(j) == gameboardObj.get_board().at(i))
            {
                std::cout << "< Spieler " << playerObj3.get_identifier() << ", Figur " << j;
            }

            if (playerObj4.get_currentField().at(j) == gameboardObj.get_board().at(i))
            {
                std::cout << "< Spieler " << playerObj4.get_identifier() << ", Figur " << j;
            }
        }
        std::cout << std::endl;
    }
}