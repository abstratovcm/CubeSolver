#include <vector>
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <numeric>

#include "Moves.h"

using namespace std;

class Cube
{

private:
    Moves moves;
    vector<int> position;

public:
    Cube(const string type)
    {
        if (type.compare("skewb") == 0)
            ResizeCube(30);
        DefineMoves(type);
    }

    void ResizeCube(int size)
    {
        if (size < 1)
            throw("ERROR: (Cube::ResizeCube) wrong size");

        position.resize(size);
        for (int i = 0; i < size; i++)
            position[i] = i;
    }

    void Print()
    {
        cout << endl;
        for (int i = 0; i < position.size(); i++)
        {
            cout << position[i] << " ";
        }
        cout << endl;
    }

    bool IsSolved()
    {
        for (int i = 0; i < position.size(); i++)
            if (position[i] != i)
                return false;
        return true;
    }

    void DefineMoves(const string type)
    {
        if (type.compare("skewb") == 0)
        {
            moves.Set("NL", {{20, 15, 0}, {24, 18, 1}, {22, 17, 2}, {21, 19, 3}, {14, 28, 6}}, 30);
            moves.Set("NO", {{29, 16, 0}, {27, 17, 2}, {28, 18, 3}, {26, 15, 4}, {11, 20, 9}}, 30);
            moves.Set("SL", {{8, 26, 0}, {15, 23, 11}, {17, 22, 12}, {16, 20, 13}, {19, 24, 14}}, 30);
            moves.Set("SO", {{5, 24, 3}, {19, 28, 10}, {16, 26, 11}, {17, 27, 12}, {18, 25, 14}}, 30);
        }
    }

    void Move(const string name)
    {
        if (moves.Find(name))
        {
            vector<int> *m = &moves.Get(name);
            for (int i = 0; i < position.size(); i++)
                position[i] = (*m)[position[i]];
        }
    }

    void MoveSequence(vector<string> moves)
    {
        for (int i = 0; i < moves.size(); i++)
        {
            Move(moves[i]);
        }
    }

    bool Find(const string name)
    {
        if (moves.Find(name))
            return true;
        else
            return false;
    }

    void Scramble(int number)
    {
        int moveAux;

        for (int i = 0; i < number; i++)
        {
            moveAux = rand() % 4;
            if (moveAux == 0)
                Move("NO");
            else if (moveAux == 1)
                Move("NL");
            else if (moveAux == 2)
                Move("SO");
            else if (moveAux == 3)
                Move("SL");
        }
    }
    vector<string> Solution()
    {
        vector<string> moveSolution;
        Solve(0, "", moveSolution);
        reverse(moveSolution.begin(), moveSolution.end());
        if (moveSolution.size() < 3)
            return moveSolution;

        vector<string> cleanSolution;
        int aux = 1;
        int indexDelay = 0;
        for (int i = 0; i < moveSolution.size(); i++)
        {
            if ((!cleanSolution.empty()) && (moveSolution[i].compare(cleanSolution[i - 1 - indexDelay]) == 0))
            {
                aux = aux + 1;
                cleanSolution.push_back(moveSolution[i]);
                if (aux == 3)
                {
                    aux = 1;
                    cleanSolution.pop_back();
                    cleanSolution.pop_back();
                    cleanSolution.pop_back();
                    indexDelay = indexDelay + 3;
                }
            }
            else
            {
                cleanSolution.push_back(moveSolution[i]);
                aux = 1;
            }
        }
        return cleanSolution;
    }

    bool Solve(int number, const string move, vector<string> &moveSolution)
    {
        Move(move);
        if (IsSolved())
        {
            Move(move);
            Move(move);
            return true;
        }
        number++;
        if (number >= 20)
        {
            Move(move);
            Move(move);
            return false;
        }
        if (Solve(number, "NL", moveSolution))
        {
            moveSolution.push_back("NL");
            Move(move);
            Move(move);
            return true;
        }
        else if (Solve(number, "NO", moveSolution))
        {
            moveSolution.push_back("NO");
            Move(move);
            Move(move);
            return true;
        }
        else if (Solve(number, "SO", moveSolution))
        {
            moveSolution.push_back("SO");
            Move(move);
            Move(move);
            return true;
        }
        else if (Solve(number, "SL", moveSolution))
        {
            moveSolution.push_back("SL");
            Move(move);
            Move(move);
            return true;
        }
        Move(move);
        Move(move);
        return false;
    }
};