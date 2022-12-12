#include <vector>
#include <iostream>
#include <stdlib.h>

using namespace std;

class Skewb
{
public:
    vector<vector<int>> faces;
    // vector<vector<int>> faces(6, vector<int>(5, 0));

    void Init()
    {
        faces.resize(6, vector<int>(5, 0));
        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                faces[i][j] = j + i * 5;
            }
        }
    }

    void Print()
    {
        cout << endl
             << "Skweb:" << endl;
        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                cout << faces[i][j] << " ";
            }
            cout << endl;
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

    bool IsSolved()
    {
        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                if (faces[i][j] != j + i * 5)
                    return false;
            }
        }
        return true;
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
    bool Solve(int number, const string move)
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
        if (Solve(number, "NL"))
        {
            cout << "NL" << endl;
            Move(move);
            Move(move);
            return true;
        }
        else if (Solve(number, "NO"))
        {
            cout << "NO" << endl;
            Move(move);
            Move(move);
            return true;
        }
        else if (Solve(number, "SO"))
        {
            cout << "NO" << endl;
            Move(move);
            Move(move);
            return true;
        }
        else if (Solve(number, "SL"))
        {
            cout << "NO" << endl;
            Move(move);
            Move(move);
            return true;
        }
        Move(move);
        Move(move);
        return false;
    }
};