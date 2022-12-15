#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include "MoveHelper.h"
using namespace std;

class Moves
{
private:
    struct move
    {
        vector<vector<vector<int>>> perm;
        void Print()
        {
            string firstLine = "";
            string secondLine = "";
            for (int i = 0; i < perm.size(); i++)
            {
                for (int j = 0; j < perm[i].size(); j++)
                {
                    for (int k = 0; k < perm[i][j].size(); k++)
                    {
                        if (k == 0)
                            firstLine = firstLine + to_string(perm[i][j][k]);
                        else if (k == 1)
                            secondLine = secondLine + to_string(perm[i][j][k]);
                    }
                }
                firstLine += " ";
                secondLine += " ";
            }
            cout << endl;
            cout << firstLine << endl;
            cout << secondLine << endl;
        }

        void Set(vector<vector<vector<int>>> moves)
        {
            perm.resize(moves.size());
            for (int i = 0; i < perm.size(); i++)
            {
                perm[i].resize(moves[i].size());
                for (int j = 0; j < perm[i].size(); j++)

                    for (int k = 0; k < moves[i][j].size(); k++)
                        perm[i][j].push_back(moves[i][j][k]);
            }
        }
    };

    unordered_map<string, move> movesTable;

public:
    void Set(const string name, vector<vector<vector<int>>> permutations)
    {
        if (Find(name))
            throw("ERROR: (Moves::Set) name found");
        move m;
        m.Set(permutations);
        movesTable.insert({name, m});
    }

    void SetSkewbMove(const string name, vector<int> colors,
                      vector<int> otherColors, vector<int> pieces)
    {
        if (Find(name))
            throw("ERROR: (Moves::SetSkewbMove) name found");
        vector<vector<vector<int>>> finalMatrix;
        vector<int> allColors = {0, 1, 2, 3, 4, 5};
        vector<int> allPieces = {0, 1, 2, 3, 4};
        vector<int> otherPieces;

        MoveHelper::CombineColorPiece(colors, pieces, finalMatrix);
        MoveHelper::CombineColorPiece(otherColors, pieces, finalMatrix);

        rotate(pieces.rbegin(), pieces.rbegin() + 2, pieces.rend());
        MoveHelper::CombineColorPiece(otherColors, pieces, finalMatrix);

        sort(pieces.begin(), pieces.end());
        set_difference(allPieces.begin(), allPieces.end(), pieces.begin(), pieces.end(),
                       inserter(otherPieces, otherPieces.begin()));
        for (int i = 0; i < otherPieces.size(); i++)
            MoveHelper::CombineColorPiece(otherColors, {otherPieces[i]}, finalMatrix);

        move m;
        m.Set(finalMatrix);
        movesTable.insert({name, m});
    }

    vector<vector<vector<int>>> &Get(const string name)
    {
        if (Find(name))
            return movesTable[name].perm;
        throw "ERROR: (Moves::Get) name not found";
    }

    bool Find(const string name)
    {
        if (movesTable.find(name) != movesTable.end())
            return true;
        return false;
    }

    void Print(const string name)
    {
        if (Find(name))
            movesTable[name].Print();
        else
            throw "ERROR: (Moves::Print) name not found";
    }
};