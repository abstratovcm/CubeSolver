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
            moves.SetSkewbMove("NL", {1, 2, 5}, {4, 3, 0}, {1, 4, 3});
            moves.SetSkewbMove("NO", {1, 2, 4}, {5, 3, 0}, {4, 1, 0});
            moves.SetSkewbMove("SL", {1, 5, 0}, {2, 3, 4}, {3, 1, 0});
            moves.SetSkewbMove("SO", {1, 4, 0}, {2, 3, 5}, {0, 4, 3});
        }
    }

    void Move(const string name)
    {
        if (moves.Find(name))
        {
            int aux, MAX;
            vector<vector<vector<int>>> *m = &moves.Get(name);
            for (int i = 0; i < (*m).size(); i++)
            {
                MAX = (*m)[i].size() - 1;
                aux = faces[(*m)[i][0][0]][(*m)[i][0][1]];
                for (int j = 0; j < (*m)[i].size() - 1; j++)
                {
                    faces[(*m)[i][j][0]][(*m)[i][j][1]] = faces[(*m)[i][j + 1][0]][(*m)[i][j + 1][1]];
                }
                faces[(*m)[i][MAX][0]][(*m)[i][MAX][1]] = aux;
            }
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