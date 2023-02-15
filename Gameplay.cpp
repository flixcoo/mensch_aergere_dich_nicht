#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <iomanip>

#include "Player.hpp"
#include "Gameplay.hpp"
#include "gameboard.hpp"

void Spielablauf::playOneRound(Player &playerObj1, Player &playerObj2, Player &playerObj3, Player &playerObj4, Gameboard &gameboardObj) // Jeder Spieler ist einmal am Zug
{
    std::cout << "[playOneRound]: Spieler 1 ist an der Reihe, bitte bestaetige mit einer Taste." << std::endl;
    std::cin.ignore();
    int Wuerfelzahl;
    printBoard(playerObj1, playerObj2, playerObj3, playerObj4, gameboardObj);
    std::cout << "--------- Spieler 1 ---------" << std::endl;

    Wuerfelzahl = playerObj1.rollDice();
    PlayersTurn(Wuerfelzahl, playerObj1, playerObj2, playerObj3, playerObj4, gameboardObj); // Runde von Spieler 1

    std::cout << "[playOneRound]: Dein Zug ist beendet, Spieler 2 bestaetige mit einer Taste." << std::endl;
    std::cin.ignore();
    printBoard(playerObj2, playerObj3, playerObj4, playerObj1, gameboardObj);
    std::cout << "--------- Spieler 2 ---------" << std::endl;

    Wuerfelzahl = playerObj2.rollDice();
    PlayersTurn(Wuerfelzahl, playerObj2, playerObj3, playerObj4, playerObj1, gameboardObj); // Runde von Spieler 2

    std::cout << "[playOneRound]: Dein Zug ist beendet, Spieler 3 bestaetige mit einer Taste." << std::endl;
    std::cin.ignore();
    printBoard(playerObj3, playerObj4, playerObj1, playerObj2, gameboardObj);
    std::cout << "--------- Spieler 3 ---------" << std::endl;

    Wuerfelzahl = playerObj3.rollDice();
    PlayersTurn(Wuerfelzahl, playerObj3, playerObj4, playerObj1, playerObj2, gameboardObj); // Runde von Spieler 3

    std::cout << "[playOneRound]: Dein Zug ist beendet, Spieler 4 bestaetige mit einer Taste." << std::endl;
    std::cin.ignore();
    printBoard(playerObj4, playerObj1, playerObj2, playerObj3, gameboardObj);
    std::cout << "--------- Spieler 4 ---------" << std::endl;

    Wuerfelzahl = playerObj4.rollDice();
    PlayersTurn(Wuerfelzahl, playerObj4, playerObj1, playerObj2, playerObj3, gameboardObj); // Runde von Spieler 4

    printBoard(playerObj1, playerObj2, playerObj3, playerObj4, gameboardObj);
}

void Spielablauf::PlayersTurn(int Wuerfelzahl, Player &playerObj1, Player &playerObj2, Player &playerObj3, Player &playerObj4, Gameboard &gameboardObj) // Zug fuer jeweils einen Spieler und seine Gegner
{

    if (Wuerfelzahl == 6) // 6 Gewuerfelt
    {
        std::cout << "[S" << playerObj1.get_identifier() << "]-"
                  << "[PlayersTurn]: Du hast eine 6 gewuerfelt! nice" << std::endl;
        std::cin.ignore();
        if (playerObj1.minOneInStorage()) // 6 gewuerfelt && alle sind im Lager
        {
            std::cout << "[S" << playerObj1.get_identifier() << "]-"
                      << "[PlayersTurn]: Es ist mindestens eine Figur im Lager." << std::endl;
            std::cin.ignore();
            int FigurIndex = playerObj1.randomFromStorage();
            std::cout << "[S" << playerObj1.get_identifier() << "]-"
                      << "[PlayersTurn]: Zufaelliger aus Lager ist " << FigurIndex << std::endl;
            MoveToken(Wuerfelzahl, FigurIndex, playerObj1, playerObj2, playerObj3, playerObj4, gameboardObj);

            printBoard(playerObj1, playerObj2, playerObj3, playerObj4, gameboardObj);

            std::cout << "[S" << playerObj1.get_identifier() << "]-"
                      << "[PlayersTurn]: Du hast eine 6 gewuerfelt und darfst deshalb nochmal rollDice" << std::endl;
            std::cin.ignore();
            int Wuerfelzahl = playerObj1.rollDice();
            std::cout << "[S" << playerObj1.get_identifier() << "]-"
                      << "[MoveToken]: Du hast eine " << Wuerfelzahl << " gewuerfelt" << std::endl;
            std::cin.ignore();
            PlayersTurn(Wuerfelzahl, playerObj1, playerObj2, playerObj3, playerObj4, gameboardObj);
        }
        else // 6 Gewuerfelt && keiner ist im Lager
        {
            std::cout << "[S" << playerObj1.get_identifier() << "]-"
                      << "[PlayersTurn]: Es ist keine Figur im Lager." << std::endl;
            std::cin.ignore();
            if (FigurenBewegbar(Wuerfelzahl, playerObj1, gameboardObj))
            {
                std::cout << "[S" << playerObj1.get_identifier() << "]-"
                          << "[PlayersTurn]: Es ist ist mindestens eine Figur bewegbar." << std::endl
                          << std::endl;
                std::cin.ignore();
                int FigurIndex = playerObj1.selectToken();
                MoveToken(Wuerfelzahl, FigurIndex, playerObj1, playerObj2, playerObj3, playerObj4, gameboardObj);

                std::cout << "[S" << playerObj1.get_identifier() << "]-"
                          << "[PlayersTurn]: Du hast eine 6 gewuerfelt und darfst deshalb nochmal rollDice" << std::endl;
                int Wuerfelzahl = playerObj1.rollDice();
                std::cin.ignore();
                PlayersTurn(Wuerfelzahl, playerObj1, playerObj2, playerObj3, playerObj4, gameboardObj);
            }
            std::cout << "[S" << playerObj1.get_identifier() << "]-"
                      << "[PlayersTurn]: Das ist net so geil jetzt." << std::endl;
        }
    }
    else if (playerObj1.allTokenInStorage()) // Keine 6 gewuerfelt & alle sind im Lager
    {
        std::cout << "[S" << playerObj1.get_identifier() << "]-"
                  << "[PlayersTurn]: Du hast eine " << Wuerfelzahl << " gewuerfelt! ist oke nech" << std::endl;
        std::cin.ignore();
        std::cout << "[S" << playerObj1.get_identifier() << "]-"
                  << "[PlayersTurn]: Alle deiner Figuren sind noch im Lager." << std::endl;
        std::cin.ignore();
        std::cout << "[S" << playerObj1.get_identifier() << "]-"
                  << "[PlayersTurn]: Da du keine 6 gewuerfelt hast und alle deiner Spieler noch im Lager sind, darfst du noch 2 mal rollDice." << std::endl;
        std::cin.ignore();
        for (int i = 2; i > 0; i--)
        {
            int Wuerfelzahl = playerObj1.rollDice();
            if (Wuerfelzahl == 6)
            {
                std::cout << "[S" << playerObj1.get_identifier() << "]-"
                          << "[PlayersTurn]: Du hast jetzt eine " << Wuerfelzahl << " gewuerfelt" << std::endl;
                std::cin.ignore();
                PlayersTurn(6, playerObj1, playerObj2, playerObj3, playerObj4, gameboardObj);
                std::cout << "[S" << playerObj1.get_identifier() << "]-"
                          << "[PlayersTurn]: break" << std::endl
                          << std::endl;
                std::cin.ignore();
                break;
            }
            else
            {
                std::cout << "[S" << playerObj1.get_identifier() << "]-"
                          << "[PlayersTurn]: Du hast eine " << Wuerfelzahl << " gewuerfelt. Du brauchst jedoch eine 6." << std::endl;
                std::cin.ignore();
                std::cout << "[S" << playerObj1.get_identifier() << "]-"
                          << "[PlayersTurn]: Weitere Versuche: " << i - 1 << std::endl;
                std::cin.ignore();
            }
        }
    }
    else if (playerObj1.minOneInArena() || playerObj1.minOneInTargetField()) // Keine 6 gewuerfelt & mindestens einen im gameboard
    {
        std::cout << "[S" << playerObj1.get_identifier() << "]-"
                  << "[PlayersTurn]: Du hast eine " << Wuerfelzahl << " gewuerfelt." << std::endl;
        std::cout << "[S" << playerObj1.get_identifier() << "]-"
                  << "[PlayersTurn]: Du hast mindestens einen Spieler im gameboard." << std::endl;
        std::cin.ignore();
        if (FigurenBewegbar(Wuerfelzahl, playerObj1, gameboardObj))
        {
            std::cout << "[S" << playerObj1.get_identifier() << "]-"
                      << "[PlayersTurn]: Du hast bewegbare Figuren." << std::endl;
            int FigurIndex = playerObj1.selectToken();

            while (playerObj1.get_aktuellesFeld().at(FigurIndex) == "X") // Ueberpruefung, ob die geweahlte Figur im Lager ist, waehrend man keine 6 gewuerfelt hat.
            {
                std::cout << "[S" << playerObj1.get_identifier() << "] "
                          << "Die ausgewaehlte Figur ist im Lager. Da du keine 6 gewuerfelt hast, kannst du diese Figur nicht bewegen." << std::endl;
                FigurIndex = playerObj1.selectToken();
            }

            MoveToken(Wuerfelzahl, FigurIndex, playerObj1, playerObj2, playerObj3, playerObj4, gameboardObj);
        }
        else
        {
            std::cout << "[S" << playerObj1.get_identifier() << "]-"
                      << "[PlayersTurn]: Kein Spieler Bewegbar" << std::endl
                      << std::endl;
            std::cin.ignore();
            return;
        }
    }
    else // Wird zu dem dadrueber
    {
        std::cout << "[error]: common knowledge debugger triggered" << std::endl
                  << std::endl;
        std::cin.ignore();
    }
}

void Spielablauf::MoveToken(int Wuerfelzahl, int FigurIndex, Player &playerObj1, Player &playerObj2, Player &playerObj3, Player &playerObj4, Gameboard &gameboardObj) // Bewegung der Figur
{
    int SFI = determineStartingFieldIndex(FigurIndex, playerObj1, gameboardObj);
    std::cout << "[S" << playerObj1.get_identifier() << "]-"
              << "[MoveToken]: StartfeldIndex ist " << SFI << std::endl;
    std::cin.ignore();
    int NFI;

    if (playerObj1.get_aktuellesFeld().at(FigurIndex) == "X" && Wuerfelzahl == 6) // Uenerpruefung, wenn die Figur im Lager ist und man eine 6 gewuerfelt hat.
    {

        if (ownTokenOnNewField(FigurIndex, SFI, playerObj1, gameboardObj) == FigurIndex) // Ist eine Figur auf dem neuen Feld (also dem Starfeld der Spielfigur) ?
        {
            std::cout << "Da die zu bewegende Figur im Lager ist, wird Sie auf das Startfeld gesetzt" << std::endl;
            NFI = SFI; // NFI bleibt SFI, da die Figur nur auf ihr erstes Feld geht.
            Wuerfelzahl = 0;
        }
        else if (ownTokenOnNewField(FigurIndex, SFI, playerObj1, gameboardObj) != FigurIndex)
        {
            std::cout << "Auf dem Startfeld steht deine eigene Figur" << std::endl;
            std::cout << "Diese Figur muss zuerst bewegt werden." << std::endl;
            std::cin.ignore();

            FigurIndex = ownTokenOnNewField(FigurIndex, SFI, playerObj1, gameboardObj);
            std::cout << "Figur " << FigurIndex << " wurde automatisch fuer dich ausgeweahlt." << std::endl;
            MoveToken(Wuerfelzahl, FigurIndex, playerObj1, playerObj2, playerObj3, playerObj4, gameboardObj);
            std::cout << "[System]: break" << std::endl;
            return;
        }
    }

    NFI = SFI + Wuerfelzahl; // Index des neuen Feldes auf Spielbrett, ergibt sich aus dem Index des Feldes wo man gestartet ist  (SFI) + der Wuerfelzahl
    std::cout << "[S" << playerObj1.get_identifier() << "]-"
              << "[MoveToken]: NeuerFeldIndex ist " << NFI << std::endl;
    std::cin.ignore();

    NFI = beyondGameboard(NFI, FigurIndex, playerObj1, gameboardObj); // Korrektur NFI

    if (NFI != inForeignTargetField(Wuerfelzahl, NFI, playerObj1, playerObj2, playerObj3, playerObj4, gameboardObj)) // Korektur NFI
    {
        std::cout << "[S" << playerObj1.get_identifier() << "]-"
                  << "[Debug]: Figur ist in fremden Zielfeld" << std::endl;
        NFI = inForeignTargetField(Wuerfelzahl, NFI, playerObj1, playerObj2, playerObj3, playerObj4, gameboardObj);
        std::cout << "[S" << playerObj1.get_identifier() << "]-"
                  << "[Debug]: Neuer NFI ist " << NFI << std::endl;
        NFI = beyondGameboard(NFI, FigurIndex, playerObj1, gameboardObj); // Korrektur NFI nach InFremdenZield
        std::cout << "[S" << playerObj1.get_identifier() << "]-"
                  << "[Debug]: Nach erneuter NFI-Korrektur ist der NFI jetzt " << NFI << std::endl;
        std::cin.ignore();
    }
    else if (Wuerfelzahl > 4) // Wenn nicht Korrigiert wird, gucke ob die hinteren Felder ein Zielfeld waren
    {
        std::cout << "Wuerfelzahl > 4" << std::endl;

        for (int i = 1; i < Wuerfelzahl; i++) // For-Schleife fuer die Wuerfelzahl
        {
            std::cout << "i ist " << i << std::endl;
            if (NFI - i != inForeignTargetField(Wuerfelzahl, NFI - i, playerObj1, playerObj2, playerObj3, playerObj4, gameboardObj)) // Ist der NFI - i (1,...,Wuerfelzahl) ein Zielfeld?
            {
                std::cout << "NFI ist nicht gleich " << NFI << " - " << i << std::endl;
                NFI = NFI + 4;                                                    // NFI wird korrigiert, da man ansonsten die Zielfelder als regulaere gameboarder zaehlen wuerde.
                NFI = beyondGameboard(NFI, FigurIndex, playerObj1, gameboardObj); // Korrektur NFI falls noetig
            }
        }
    }

    if (beyondTargetField(Wuerfelzahl, FigurIndex, playerObj1, gameboardObj)) // Bin ich ueber das Ziel hinaus?
    {
        std::cout << "[S" << playerObj1.get_identifier() << "]-"
                  << "[MoveToken]: Du bist ueber das Ziel hinaus." << std::endl;
        std::cin.ignore();
        int FigurIndex = playerObj1.selectToken();
        MoveToken(Wuerfelzahl, FigurIndex, playerObj1, playerObj2, playerObj3, playerObj4, gameboardObj);
        std::cout << "[S" << playerObj1.get_identifier() << "]-"
                  << "[MoveToken]: break" << std::endl
                  << std::endl;
        return;
    }

    if (ownTokenOnNewField(FigurIndex, NFI, playerObj1, gameboardObj) != FigurIndex) // Ist eine Figur auf dem neuen Feld?
    {
        std::cout << "[S" << playerObj1.get_identifier() << "]-"
                  << "[MoveToken]: Deine eigene Figur steht auf dem Feld auf das du willst " << std::endl
                  << std::endl;
        std::cin.ignore();
        int FigurIndex = playerObj1.selectToken();
        MoveToken(Wuerfelzahl, FigurIndex, playerObj1, playerObj2, playerObj3, playerObj4, gameboardObj);
        std::cout << "[S" << playerObj1.get_identifier() << "]-"
                  << "[MoveToken]: break" << std::endl
                  << std::endl;
        return;
    }

    playerOnNewField(NFI, playerObj1, playerObj2, playerObj3, playerObj4, gameboardObj); // Spieler werden ggf. wieder zurueck ins Lager gesetzt.

    std::string neuesFeld = gameboardObj.get_board().at(NFI); // Das neue Feld wird aus dem Spielbrett gelesen
    std::cout << "[S" << playerObj1.get_identifier() << "]-"
              << "[MoveToken]: Das neue Feld ist nun " << neuesFeld << std::endl
              << std::endl;
    playerObj1.get_aktuellesFeld().at(FigurIndex) = neuesFeld; // Das neue Feld wird der Figur im Array zugewiesen
    std::cin.ignore();

    std::cout << "[S" << playerObj1.get_identifier() << "]-"
              << "[MoveToken]: Distanz" << std::endl;
    std::cout << "[S" << playerObj1.get_identifier() << "]-"
              << "[MoveToken]: " << playerObj1.get_distance().at(FigurIndex) << " + " << Wuerfelzahl << " = " << playerObj1.get_distance().at(FigurIndex) + Wuerfelzahl << std::endl;

    playerObj1.get_distance().at(FigurIndex) += Wuerfelzahl;   // Die Distanz wird erhoeht
    neuesFeld = playerObj1.get_aktuellesFeld().at(FigurIndex); // Das neue Feld wird aktualisiert

    std::cout << "[S" << playerObj1.get_identifier() << "]-"
              << "[MoveToken]: Die Distanz ist nun " << playerObj1.get_distance().at(FigurIndex) << std::endl
              << std::endl;
    std::cin.ignore();
}

bool Spielablauf::FigurenBewegbar(int Wuerfelzahl, Player &playerObj, Gameboard &gameboardObj) // Sind die Figuren eines Spielers bewegbar
{
    std::cout << "[S" << playerObj.get_identifier() << "]-"
              << "[FigurenBewegbar]: Figur Bewegbar Ueberpruefung" << std::endl;
    std::cin.ignore();
    int AnzahlBewegbar = 0;
    for (unsigned int FigurIndex = 0; FigurIndex < playerObj.get_aktuellesFeld().max_size(); FigurIndex++)
    {
        if (!(playerObj.get_aktuellesFeld().at(FigurIndex) == "X") || Wuerfelzahl == 6) // Wenn die angegebene Figur nicht im Lager ist oder man eine 6 gewuerfelt hat
        {
            std::cout << "[S" << playerObj.get_identifier() << "]-"
                      << "[FigurenBewegbar]: Figur an Stelle " << FigurIndex << std::endl;
            std::cin.ignore();

            int SFI = determineStartingFieldIndex(FigurIndex, playerObj, gameboardObj);
            int NFI = SFI + Wuerfelzahl; // Index des neuen Feldes auf Spielbrett, ergibt sich aus dem Index des Feldes wo man gestartet ist  (SFI) + der Wuerfelzahl
            std::cout << "[S" << playerObj.get_identifier() << "]-"
                      << "[FigurenBewegbar]:  SFI: " << SFI << ", NFI: " << NFI << std::endl;
            if (beyondGameboard(NFI, FigurIndex, playerObj, gameboardObj) != NFI) // Ist die Figur
            {
                NFI = beyondGameboard(NFI, FigurIndex, playerObj, gameboardObj);
            }

            if (beyondTargetField(Wuerfelzahl, FigurIndex, playerObj, gameboardObj))
            {
                std::cout << "[S" << playerObj.get_identifier() << "]-"
                          << "[tokenMovable]: Figur " << FigurIndex << "kommt uebers Ziel hinaus." << NFI << std::endl;
            }
            else if (ownTokenOnNewField(FigurIndex, NFI, playerObj, gameboardObj) != (int)FigurIndex)
            {
                std::cout << "[S" << playerObj.get_identifier() << "]-"
                          << "[tokenMovable]: Eigene Figur ist auf neuem Feld von Figur " << FigurIndex << std::endl;
            }
            else if (playerObj.tokenInStorage(FigurIndex) && Wuerfelzahl != 6)
            {
                std::cout << "[S" << playerObj.get_identifier() << "]-"
                          << "[tokenMovable]: Du hast eine Figur ausgewaehlt, die im Lager steh, obwohl du keine 6 hast." << std::endl;
            }
            else
            {
                AnzahlBewegbar++;
                std::cout << "[S" << playerObj.get_identifier() << "]-"
                          << "[tokenMovable]: Anzahl Bewegbar: " << AnzahlBewegbar << std::endl;
            }
            std::cout << "[S" << playerObj.get_identifier() << "]-"
                      << "[tokenMovable]: Figur " << FigurIndex << ", Feld " << playerObj.get_aktuellesFeld().at(FigurIndex) << std::endl;
        }
    }
    std::cout << "[S" << playerObj.get_identifier() << "]-"
              << "[tokenMovable]: Anzahl Bewegbar: " << AnzahlBewegbar << std::endl;
    if (AnzahlBewegbar > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Spielablauf::beyondTargetField(int Wuerfelzahl, int FigurIndex, Player &playerObj1, Gameboard &gameboardObj) // Schaut ob die gelaufene Distanz einer Figur groesser ist als 44 (zweite Runde) und uebergibt einen Wahrheitswert
{
    if ((playerObj1.get_distance().at(FigurIndex) + Wuerfelzahl > 44)) // Ist Figur an FigurIndex schon mehr als 44 Felder gelaufen?
    {
        return true; // Wenn ja, return true
    }
    else
    {
        return false; // wenn nein, return false
    }
}

int Spielablauf::PlayerOnStartingField(int FigurIndex, Player &playerObj1) // Ueberprueft, ob ein Spieler auf dem Startfeld steht und gibt die Figur zurueck, die beweg werden muss.
{
    for (unsigned int i = 0; i < playerObj1.get_aktuellesFeld().max_size(); i++) // Geht das AktuellesFeld Array durch
    {
        if (playerObj1.get_aktuellesFeld().at(i) == playerObj1.get_startingField()) // Spielfeld ist besetzt
        {
            return i; // Index von Spieler auf dem Startfeld, welche bewegt werden muss.
        }
    }
    return FigurIndex; // Index vom Urspruenglichen Spieler
}

int Spielablauf::beyondGameboard(int NFI, int FigurIndex, Player &playerObj1, Gameboard &gameboardObj) // Ueberprueft, ob ich ueber das Spielfeld-Array hinaus bin
{

    if ((unsigned int)NFI >= gameboardObj.get_board().max_size()) // Ist mein FigurIndex groesser als mein Spielfeld
    {
        NFI = NFI - 56; // Groesse des Spielbrettes wird vom Index abgezogen

        return NFI; // Das neues Feld, welches nun nicht mehr ausserhalb des Arrays Spielbrett ist, wird zurueckgegeben
    }
    else
    {
        return NFI; // Das neue Feld liegt im Array, also wird es einfach zurueckgegeben.
    }
}

int Spielablauf::inForeignTargetField(int Wuerfelzahl, int NFI, Player playerObj1, Player playerObj2, Player playerObj3, Player playerObj4, Gameboard gameboardObj) // Bin ich in einem fremden Zielfeld gelandet?
{
    std::cout << "[S" << playerObj1.get_identifier() << "]-"
              << "[inForeignTargetField]: Ueberpruefung" << std::endl;

    for (unsigned int i = 0; i < playerObj2.get_targetFields().max_size(); i++)
    {

        std::cout << "[S" << playerObj1.get_identifier() << "]-"
                  << "[Debug]: Zielfeld von Spieler 2: " << playerObj2.get_targetFields().at(i) << std::endl; // Debugging
        std::cout << "[S" << playerObj1.get_identifier() << "]-"
                  << "[Debug]: Neues Feld: " << gameboardObj.get_board().at(NFI) << std::endl; // Debugging

        if (playerObj2.get_targetFields().at(i) == gameboardObj.get_board().at(NFI)) // Ist das Neue Feld ein Zielfeld von Spieler2?
        {
            std::cout << "[S" << playerObj1.get_identifier() << "]-"
                      << "[inForeignTargetField]: Du bist in einem fremden Zielfeld gelandet." << std::endl;
            std::cin.ignore();
            NFI = NFI + 4; // Raus aus dem Bereich der Zielfelder von Spieler2
            std::cout << "[S" << playerObj1.get_identifier() << "]-"
                      << "[inForeignTargetField]: NFI ist jetzt " << NFI << std::endl;
            return NFI;
        }
    }
    for (unsigned int i = 0; i < playerObj3.get_targetFields().max_size(); i++) // Ist das Neue Feld ein Zielfeld von Spieler3?
    {
        std::cout << "[S" << playerObj1.get_identifier() << "]-"
                  << "[Debug]: Zielfeld von Spieler 3: " << playerObj3.get_targetFields().at(i) << std::endl; // Debugging
        std::cout << "[S" << playerObj1.get_identifier() << "]-"
                  << "[Debug]: Neues Feld: " << gameboardObj.get_board().at(NFI) << std::endl; // Debugging

        if (playerObj3.get_targetFields().at(i) == gameboardObj.get_board().at(NFI))
        {
            std::cout << "[S" << playerObj1.get_identifier() << "]-"
                      << "[inForeignTargetField]: Du bist in einem fremden Zielfeld gelandet." << std::endl;
            std::cin.ignore();
            NFI = NFI + 4; // Raus aus dem Bereich der Zielfelder von Spieler3
            std::cout << "[S" << playerObj1.get_identifier() << "]-"
                      << "[inForeignTargetField]: NFI ist jetzt " << NFI << std::endl;
            return NFI;
        }
    }
    for (unsigned int i = 0; i < playerObj4.get_targetFields().max_size(); i++) // Ist das Neue Feld ein Zielfeld von Spieler4?
    {
        std::cout << "[S" << playerObj1.get_identifier() << "]-"
                  << "[Debug]: Zielfeld von Spieler 4: " << playerObj4.get_targetFields().at(i) << std::endl; // Debugging
        std::cout << "[S" << playerObj1.get_identifier() << "]-"
                  << "[Debug]: Neues Feld: " << gameboardObj.get_board().at(NFI) << std::endl; // Debugging

        if (playerObj4.get_targetFields().at(i) == gameboardObj.get_board().at(NFI))
        {
            std::cout << "[S" << playerObj1.get_identifier() << "]-"
                      << "[inForeignTargetField]: Du bist in einem fremden Zielfeld gelandet." << std::endl;
            std::cin.ignore();
            NFI = NFI + 4; // Raus aus dem Bereich der Zielfelder von Spieler3
            std::cout << "[S" << playerObj1.get_identifier() << "]-"
                      << "[inForeignTargetField]: NFI ist jetzt " << NFI << std::endl;
            return NFI;
        }
    }
    return NFI;
}

int Spielablauf::ownTokenOnNewField(int FigurIndex, int NFI, Player &playerObj, Gameboard &gameboardObj) // Ueberprueft, ob eine Figur des aktuellen Spielers auf dem neuen Feld steht
{
    std::string NeuesFeld = gameboardObj.get_board().at(NFI);
    for (int i = 0; i < (int)playerObj.get_aktuellesFeld().max_size(); i++)
    {
        if (playerObj.get_aktuellesFeld().at(i) == NeuesFeld)
        {
            std::cout << "[S" << playerObj.get_identifier() << "] "
                      << "Wenn " << i << " ungleich " << FigurIndex << " ist, muss Figur " << i << " bewegt werden." << std::endl;
            if (i != (int)FigurIndex)
            {
                std::cout << "[S" << playerObj.get_identifier() << "]-"
                          << "[ownTokenOnNewField]: Figur " << i << " muss bewegt werden, da du sonst deine eigene Figur schlagen wuerdest" << std::endl;
                return i; // Wenn ja, gib den Index der Figur zurueck, welche dann stattdesssen bewegt werden muss.
            }
        }
    }
    std::cout << "[S" << playerObj.get_identifier() << "]-"
              << "[ownTokenOnNewField]: Passt alles soweit" << std::endl;
    return FigurIndex; // Wenn ja, gib den Index der Figur zurueck, welche wir gerade schon bewegen.
}

void Spielablauf::playerOnNewField(int NFI, Player &playerObj1, Player &playerObj2, Player &playerObj3, Player &playerObj4, Gameboard &gameboardObj) // Ist eine andere Spielfigur auf meinem neuen Feld?
{
    for (unsigned int i = 0; i < playerObj2.get_aktuellesFeld().max_size(); i++)
    {
        if (playerObj2.get_aktuellesFeld().at(i) == gameboardObj.get_board().at(NFI)) // Ist auf dem neuen Feld eine Figur von Spieler 2?
        {
            playerObj2.get_aktuellesFeld().at(i) = "X"; // Spieler wird rausgekickt (Position der Figur auf X fuer Lager)

            std::cout << "[S" << playerObj1.get_identifier() << "] "
                      << "Du hast die Figur " << i << " von Spieler " << playerObj2.get_identifier() << " geschlagen." << std::endl;
            std::cin.ignore();

            playerObj2.get_distance().at(i) = 0; // Distanz der Spielfigur wird zurueckgesetzt.

            std::cout << "[S" << playerObj1.get_identifier() << "]-"
                      << "[playerOnNewField]: Die Figur von Spieler " << playerObj2.get_identifier() << " ist nun wieder im Lager." << std::endl;
        }
    }
    for (unsigned int i = 0; i < playerObj3.get_aktuellesFeld().max_size(); i++) // Ist auf dem neuen Feld eine Figur von Spieler 3?
    {
        if (playerObj3.get_aktuellesFeld().at(i) == gameboardObj.get_board().at(NFI))
        {
            playerObj3.get_aktuellesFeld().at(i) = "X"; // Spieler wird rausgekickt (Position der Figur auf X fuer Lager)

            std::cout << "[S" << playerObj1.get_identifier() << "] "
                      << "Du hast die Figur " << i << " von Spieler " << playerObj3.get_identifier() << " geschlagen." << std::endl;
            std::cin.ignore();

            playerObj3.get_distance().at(i) = 0; // Distanz der Spielfigur wird zurueckgesetzt.

            std::cout << "[S" << playerObj1.get_identifier() << "]-"
                      << "[playerOnNewField]: Die Figur von Spieler " << playerObj3.get_identifier() << " ist nun wieder im Lager." << std::endl;
        }
    }
    for (unsigned int i = 0; i < playerObj4.get_aktuellesFeld().max_size(); i++) // Ist auf dem neuen Feld eine Figur von Spieler 4?
    {
        if (playerObj4.get_aktuellesFeld().at(i) == gameboardObj.get_board().at(NFI))
        {
            playerObj4.get_aktuellesFeld().at(i) = "X"; // Spieler wird rausgekickt (Position der Figur auf X fuer Lager).

            std::cout << "[S" << playerObj1.get_identifier() << "] "
                      << "Du hast die Figur " << i << " von Spieler " << playerObj4.get_identifier() << " geschlagen." << std::endl;
            std::cin.ignore();

            playerObj4.get_distance().at(i) = 0; // Distanz der Spielfigur wird zurueckgesetzt.

            std::cout << "[S" << playerObj1.get_identifier() << "]-"
                      << "[playerOnNewField]: Die Figur von Spieler " << playerObj4.get_identifier() << " ist nun wieder im Lager." << std::endl;
        }
    }
}

int Spielablauf::determineStartingFieldIndex(int FigurIndex, Player &playerObj, Gameboard &gameboardObj) // Bestimmt den Index auf dem Array Spielbrett, an welcher sich das Startfeld des eingegebenen Spielers befindet.
{
    if (playerObj.tokenInStorage(FigurIndex)) // Wenn das aktuelle Feld der Figur "X" ist
    {
        for (unsigned int i = 0; i < gameboardObj.get_board().max_size(); i++) // Gehe das Spielfeld durch
        {
            if (gameboardObj.get_board().at(i) == playerObj.get_startingField()) // Ueberpruefe, ob das Feld an Index i gleich dem Startfeld des Spielers ist
            {
                return i; // Wenn ja, gib den Index vom Startfeld zurueck
            }
        }
    }
    else // Wenn das aktuelle Feld der Figur nicht "X" ist
    {
        for (unsigned int i = 0; i < gameboardObj.get_board().max_size(); i++) // Gehe das Spielfeld durch
        {
            if (gameboardObj.get_board().at(i) == playerObj.get_aktuellesFeld().at(FigurIndex)) // Ueberpruefe, ob das Feld an Index i gleich dem aktuellen Feld des Spielers ist
            {
                return i; // Wenn ja, gib den index dieses Feldes zurueck
            }
        }
    }
    std::cout << "[S" << playerObj.get_identifier() << "]-"
              << "[error]: Startfeld der Figur " << FigurIndex << " konnte nicht gefunden werden." << std::endl;
    return 0;
}

bool Spielablauf::endOfGame(Player &playerObj1, Player &playerObj2, Player &playerObj3, Player &playerObj4) // Ueberprueft, ob mindestens ein Spieler alle Figuren im Ziel hat.
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

int Spielablauf::DetermineIndexOfStartingField(Player &playerObj, Gameboard &gameboardObj)
{
    for (unsigned int i = 0; i < gameboardObj.get_board().max_size(); i++) // Gehe das Spielfeld durch
    {
        if (gameboardObj.get_board().at(i) == playerObj.get_startingField()) // Ueberpruefe, ob das Feld an Index i gleich dem Startfeld des Spielers ist
        {
            return i; // Wenn ja, gib den Index vom Startfeld zurueck
        }
    }
    return 0;
}

void Spielablauf::printBoard(Player &playerObj1, Player &playerObj2, Player &playerObj3, Player &playerObj4, Gameboard &gameboardObj)
{
    std::cout << "[S" << playerObj1.get_identifier() << "]-"
              << "Das gameboard wird ausgegeben, bitte besteatige mit Enter.";
    std::cin.ignore();

    std::cout << std::endl
              << "--------- gameboard ---------" << std::endl;

    for (int i = 0; i < (int)gameboardObj.get_board().max_size(); i++)
    {
        if (i == DetermineIndexOfStartingField(playerObj1, gameboardObj)) // Wenn das Feld 0 (Startfeld Spieler 1) ausgegeben werden soll
        {
            std::cout << "Lager S" << playerObj1.get_identifier() << ": ";
            for (unsigned int i = 0; i < playerObj1.get_aktuellesFeld().max_size(); i++)
                if (playerObj1.get_aktuellesFeld().at(i) == "X") // Gucke, ob Figuren von Spieler 1 noch im Lager sind
                {
                    std::cout << "Figur" << i << " "; // Wenn ja, gib diese aus
                }
            std::cout << std::endl;
        }

        if (i == DetermineIndexOfStartingField(playerObj2, gameboardObj)) // Wenn das Feld 10 (Startfeld Spieler 2) ausgegeben werden soll
        {
            std::cout << "Lager S" << playerObj2.get_identifier() << ": ";
            for (unsigned int i = 0; i < playerObj2.get_aktuellesFeld().max_size(); i++)
                if (playerObj2.get_aktuellesFeld().at(i) == "X") // Gucke, ob Figuren von Spieler 2 noch im Lager sind
                {
                    std::cout << "Figur" << i << " "; // Wenn ja, gib diese aus
                }
            std::cout << std::endl;
        }

        if (i == DetermineIndexOfStartingField(playerObj3, gameboardObj)) // Wenn das Feld 20 (Startfeld Spieler 3) ausgegeben werden soll
        {
            std::cout << "Lager S" << playerObj3.get_identifier() << ": ";
            for (unsigned int i = 0; i < playerObj3.get_aktuellesFeld().max_size(); i++)
                if (playerObj3.get_aktuellesFeld().at(i) == "X") // Gucke, ob Figuren von Spieler 3 noch im Lager sind
                {
                    std::cout << "Figur" << i << " "; // Wenn ja, gib diese aus
                }
            std::cout << std::endl;
        }

        if (i == DetermineIndexOfStartingField(playerObj4, gameboardObj)) // Wenn das Feld 30 (Startfeld Spieler 4) ausgegeben werden soll
        {
            std::cout << "Lager S" << playerObj4.get_identifier() << ": ";
            for (unsigned int i = 0; i < playerObj4.get_aktuellesFeld().max_size(); i++)
                if (playerObj4.get_aktuellesFeld().at(i) == "X") // Gucke, ob Figuren von Spieler 4 noch im Lager sind
                {
                    std::cout << "Figur" << i << " "; // Wenn ja, gib diese aus
                }
            std::cout << std::endl;
        }

        std::cout << std::setw(2) << "(" << gameboardObj.get_board().at(i) << ")"
                  << " ";

        for (unsigned int j = 0; j < playerObj1.get_aktuellesFeld().max_size(); j++)
        {
            if (playerObj1.get_aktuellesFeld().at(j) == gameboardObj.get_board().at(i))
            {
                std::cout << "< Spieler " << playerObj1.get_identifier() << ", Figur " << j;
            }

            if (playerObj2.get_aktuellesFeld().at(j) == gameboardObj.get_board().at(i))
            {
                std::cout << "< Spieler " << playerObj2.get_identifier() << ", Figur " << j;
            }

            if (playerObj3.get_aktuellesFeld().at(j) == gameboardObj.get_board().at(i))
            {
                std::cout << "< Spieler " << playerObj3.get_identifier() << ", Figur " << j;
            }

            if (playerObj4.get_aktuellesFeld().at(j) == gameboardObj.get_board().at(i))
            {
                std::cout << "< Spieler " << playerObj4.get_identifier() << ", Figur " << j;
            }
        }
        std::cout << std::endl;
    }
}