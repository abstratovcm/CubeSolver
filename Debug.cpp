#include <iostream>
#include <time.h>

#include "Cube.h"

using namespace std;

int main()
{
    Cube skewb("skewb");
    skewb.Scramble(3);
    skewb.MoveSequence(skewb.Solution());
    skewb.Print();
}