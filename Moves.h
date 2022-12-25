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
        vector<int> instructions;
        void PrintCycles()
        {
            int size = instructions.size(), value;
            vector<int> seen(size, -1);
            cout << endl;
            for (int i = 0; i < size; i++)
            {
                if (instructions[i] == i)
                {
                    seen[i] = i;
                    continue;
                }
                if (seen[i] != i)
                {
                    value = instructions[i];
                    seen[i] = i;
                    cout << "(" << value;
                    while (true)
                    {
                        value = instructions[value];
                        seen[value] = value;
                        if (value == instructions[i])
                        {
                            cout << ")";
                            break;
                        }
                        cout << " " << value;
                    }
                }
            }
            cout << endl;
        }

        void Print()
        {
            cout << endl;
            string line1 = "";
            string line2 = "";
            int aux = 1, count = 1, MAX = 2;
            while (true)
            {
                if (instructions.size() < 10 * aux)
                {
                    aux = 1;
                    break;
                }
                aux *= 10;
                MAX += 1;
            }

            for (int i = 0; i < instructions.size(); i++)
            {
                while (true)
                {
                    if (i < 10 * aux)
                    {
                        line1.append(string(MAX - count, ' ') + to_string(i));
                        count = 1;
                        aux = 1;
                        break;
                    }
                    count++;
                    aux *= 10;
                }
                while (true)
                {
                    if (instructions[i] < 10 * aux)
                    {
                        line2.append(string(MAX - count, ' ') + to_string(instructions[i]));
                        count = 1;
                        aux = 1;
                        break;
                    }
                    count++;
                    aux *= 10;
                }
            }
            cout << line1 << endl;
            cout << line2 << endl;
        }

        void Set(vector<int> moves)
        {
            instructions.resize(moves.size());
            for (int i = 0; i < moves.size(); i++)
            {
                if (moves[i] >= moves.size())
                    throw("ERROR: (Moves::move.Set) it isn't a permutation");
                instructions[i] = moves[i];
            }
        }
    };

    unordered_map<string, move> movesTable;

public:
    void Set(const string name, vector<int> permutation)
    {
        if (Find(name))
            throw("ERROR: (Moves::Set) name found");
        move m;
        m.Set(permutation);
        movesTable.insert({name, m});
    }

    void Set(const string name, vector<vector<int>> cycles, int size = -1)
    {
        if (Find(name))
            throw("ERROR: (Moves::Set) name found");

        move m;

        int MAX = 0, previousMAX = 0;
        vector<int> permutation;
        if (size > -1)
        {
            MAX = size;
            permutation.resize(MAX);
            for (int k = previousMAX; k < MAX; k++)
                permutation[k] = k;
        }

        for (int i = 0; i < cycles.size(); i++)
        {
            for (int j = 0; j < cycles[i].size(); j++)
            {
                if (cycles[i][j] >= MAX)
                {
                    previousMAX = MAX;
                    MAX = cycles[i][j] + 1;
                    permutation.resize(MAX);
                    for (int k = previousMAX; k < MAX; k++)
                        permutation[k] = k;
                }
                if (j == cycles[i].size() - 1)
                {
                    permutation[cycles[i][j]] = cycles[i][0];
                }
                else
                {
                    permutation[cycles[i][j]] = cycles[i][j + 1];
                }
            }
        }

        m.Set(permutation);
        movesTable.insert({name, m});
    }

    vector<int> &Get(const string name)
    {
        if (Find(name))
            return movesTable[name].instructions;
        throw "ERROR: (Moves::Get) name not found";
    }

    bool Find(const string name)
    {
        if (movesTable.find(name) != movesTable.end())
            return true;
        return false;
    }

    void Print(const string name, bool showCycles = false)
    {
        if (Find(name))
        {
            if (showCycles == false)
                movesTable[name].Print();
            else
                movesTable[name].PrintCycles();
        }

        else
            throw "ERROR: (Moves::Print) name not found";
    }

    void Compose(const string name1, const string name2)
    {
        if (Find(name1) && Find(name2))
        {
            if (movesTable[name1].instructions.size() != movesTable[name2].instructions.size())
                throw("ERROR: (Moves::Compose) different size for permutations");
            move m;
            m.instructions.resize(movesTable[name1].instructions.size());
            for (int i = 0; i < m.instructions.size(); i++)
                m.instructions[i] = movesTable[name2].instructions[movesTable[name1].instructions[i]];

            movesTable.insert({name1 + " " + name2, m});
        }
    }
};