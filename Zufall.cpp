#include <random>
#include <time.h>

#include "Zufall.hpp"

int Zufall::Zufallsgenerator(int x) // Berechnet eine zufaellige Zahl von 1 bis x
{
        srand(time(NULL));
        int roll = 0;
        roll = rand() % x + 1;
        return roll;
}