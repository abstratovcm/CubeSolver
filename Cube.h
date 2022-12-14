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
    vector<vector<int>> faces;

public:
    Cube(const string type)
    {
        if (type.compare("skewb") == 0)
            resizeCube(6, 5);
        DefineMoves(type);
    }

    void resizeCube(int rows, int cols)
    {
        if (rows < 1)
            cerr << "ERROR: wrong number of rows to cube representation.";
        if (cols < 1)
            cerr << "ERROR: wrong number of columns to cube representation.";

        faces.resize(rows, vector<int>(cols, 0));
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                faces[i][j] = j + i * cols;
    }

    void Print()
    {
        int rows = faces.size();
        int cols = faces[0].size();
        cout << endl;
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (faces[i][j] < 10)
                    cout << " " << faces[i][j] << " ";
                else
                    cout << faces[i][j] << " ";
            }
            cout << endl;
        }
    }

    bool IsSolved()
    {
        int rows = faces.size();
        int cols = faces[0].size();
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (faces[i][j] != j + i * cols)
                    return false;
            }
        }
        return true;
    }

    void DefineMoves(const string type)
    {
        if (type.compare("skewb") == 0)
        {
            moves.Set("NL", {{1, 2, 5}, {4, 3, 0}}, {{1, 4, 3}, {0}, {2}});
            moves.Set("NO", {{1, 2, 4}, {5, 3, 0}}, {{4, 1, 0}, {2}, {3}});
            moves.Set("SL", {{1, 5, 0}, {2, 3, 4}}, {{3, 1, 0}, {2}, {4}});
            moves.Set("SO", {{1, 4, 0}, {2, 3, 5}}, {{0, 4, 3}, {1}, {2}});
        }
    }

    void Move(const string move)
    {
        if (move.compare("NL") == 0)
            UpdateGears({1, 2, 5}, {4, 3, 0}, {1, 4, 3});
        else if (move.compare("NO") == 0)
            UpdateGears({1, 2, 4}, {5, 3, 0}, {4, 1, 0});
        else if (move.compare("SL") == 0)
            UpdateGears({1, 5, 0}, {2, 3, 4}, {3, 1, 0});
        else if (move.compare("SO") == 0)
            UpdateGears({1, 4, 0}, {2, 3, 5}, {0, 4, 3});
    }

    void MoveSequence(vector<string> moves)
    {
        for (int i = 0; i < moves.size(); i++)
        {
            Move(moves[i]);
        }
    }

    void UpdateGears(vector<int> colors1, vector<int> colors2, vector<int> peaces)
    {
        int aux1;
        aux1 = faces[colors1[0]][peaces[0]];
        faces[colors1[0]][peaces[0]] = faces[colors1[1]][peaces[1]];
        faces[colors1[1]][peaces[1]] = faces[colors1[2]][peaces[2]];
        faces[colors1[2]][peaces[2]] = aux1;

        vector<int> aux2(3);
        for (int i = 0; i < 2; i++)
            aux2[i] = faces[colors2[0]][peaces[i]];

        faces[colors2[0]][peaces[0]] = faces[colors2[1]][peaces[1]];
        faces[colors2[0]][peaces[1]] = faces[colors2[1]][peaces[2]];
        faces[colors2[1]][peaces[1]] = faces[colors2[2]][peaces[2]];
        faces[colors2[1]][peaces[2]] = faces[colors2[2]][peaces[0]];
        faces[colors2[2]][peaces[2]] = aux2[0];
        faces[colors2[2]][peaces[0]] = aux2[1];

        aux2[2] = faces[colors2[0]][2];
        faces[colors2[0]][2] = faces[colors2[1]][2];
        faces[colors2[1]][2] = faces[colors2[2]][2];
        faces[colors2[2]][2] = aux2[2];

        int corner = FindCorner(peaces);
        int cornerAux = faces[colors2[0]][corner];
        faces[colors2[0]][corner] = faces[colors2[1]][corner];
        faces[colors2[1]][corner] = faces[colors2[2]][corner];
        faces[colors2[2]][corner] = cornerAux;
    }

    int FindCorner(vector<int> peaces)
    {
        vector<int> colorAux(4);
        colorAux = {0, 1, 3, 4};
        int countAux = 0;

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 3; j++)
                if (colorAux[i] != peaces[j])
                    countAux++;
            if (countAux == 3)
                return colorAux[i];
            else
                countAux = 0;
        }

        cerr << "ERROR: CORNER NOT FOUND" << endl;
        return 0;
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
    void Compare()
    {
        int rows = faces.size();
        int cols = faces[0].size();
        vector<vector<int>> binaryMatrix(rows, vector<int>(cols, 0));
        cout << endl;
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (faces[i][j] == j + i * cols)
                    cout << " 0 ";
                else
                {
                    cout << " 1 ";
                    binaryMatrix[i][j] = 1;
                }
            }
            cout << "| " << accumulate(binaryMatrix[i].begin(), binaryMatrix[i].end(), 0) << " " << endl;
        }
        cout << " -  -  -  -  - " << endl;
        int sumCol = 0;
        for (int j = 0; j < cols; j++)
        {
            for (int i = 0; i < rows; i++)
            {
                sumCol += binaryMatrix[i][j];
            }
            cout << " " << sumCol << " ";
            sumCol = 0;
        }
        cout << endl;
    }
};