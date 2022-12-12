#include <iostream>

#include "cube.h"

using namespace std;

Skewb skewb;

int main() {
    skewb.Init();
    skewb.Scramble(4);
    skewb.Print();
    skewb.Solve(0, "");
    skewb.Print();
}