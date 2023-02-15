#include <iostream>
#include <string>
#include <vector>
#include <array>

#include "Player.hpp"
#include "Gameplay.hpp"
#include "PlayingField.hpp"
#include "System.hpp"

// Datensaetze der Spieler
int player1_identifier = 1;
std::string player1_startingField = "0";
std::array<std::string, 4> player1_targetFields = {"0a", "0b", "0c", "0d"};
std::array<std::string, 4> player1_currentField = {"X", "X", "X", "X"};
std::array<int, 4> player1_distance = {0, 0, 0, 0};

int player2_identifier = 2;
std::string player2_startingField = "10";
std::array<std::string, 4> player2_targetFields = {"1a", "1b", "1c", "1d"};
std::array<std::string, 4> player2_currentField = {"X", "X", "X", "X"};
std::array<int, 4> player2_distance = {0, 0, 0, 0};

int player3_identifier = 3;
std::string player3_startingField = "20";
std::array<std::string, 4> player3_targetFields = {"2a", "2b", "2c", "2d"};
std::array<std::string, 4> player3_currentField = {"X", "X", "X", "X"};
std::array<int, 4> player3_distance = {0, 0, 0, 0};

int player4_identifier = 4;
std::string player4_startingField = "30";
std::array<std::string, 4> player4_targetFields = {"3a", "3b", "3c", "3d"};
std::array<std::string, 4> player4_currentField = {"X", "X", "X", "X"};
std::array<int, 4> player4_distance = {0, 0, 0, 0};

int main()
{
    Spielablauf Mensch_Aergere_dich_nicht; // Initialisiert das Spielablaufobjekt "Mensch_Aergere_dich_nicht".
    PlayingField Board;                       // Initialisiert das Spielfeldobjekt "Board".

    System::initialiseGame(); // Fuehrt die Methode "InitialisiereSpiel" des Spielfeldobjekt "Board" aus.

    Player player1(player1_identifier, player1_startingField, player1_targetFields, player1_currentField, player1_distance); // Erschafft ein Spielerobjekt "player1" mit den gegebenen Startwerten.
    Player player2(player2_identifier, player2_startingField, player2_targetFields, player2_currentField, player2_distance); // Erschafft ein Spielerobjekt "player2" mit den gegebenen Startwerten.
    Player player3(player3_identifier, player3_startingField, player3_targetFields, player3_currentField, player3_distance); // Erschafft ein Spielerobjekt "player3" mit den gegebenen Startwerten.
    Player player4(player4_identifier, player4_startingField, player4_targetFields, player4_currentField, player4_distance); // Erschafft ein Spielerobjekt "player4" mit den gegebenen Startwerten.

    while (!(Mensch_Aergere_dich_nicht.SpielEnde(player1, player2, player3, player4)))
    {
        Mensch_Aergere_dich_nicht.EineRunde(player1, player2, player3, player4, Board);
    }
    std::cout << "Das Spiel ist zu Ende!" << std::endl << std::endl;
}
