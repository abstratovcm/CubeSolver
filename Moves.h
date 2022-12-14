#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
using namespace std;

class Moves
{
public:
    struct move
    {
        vector<vector<int>> colorCycle;
        vector<vector<int>> pieceCycle;
    };
    unordered_map<string, move> movesTable;

    void Set(const string name, vector<vector<int>> colorCycle,
             vector<vector<int>> pieceCycle)
    {
        move m;
        m.colorCycle.resize(colorCycle.size());
        for (int i = 0; i < colorCycle.size(); i++)
        {
            m.colorCycle[i].resize(colorCycle[i].size());
            for (int j = 0; j < colorCycle[i].size(); j++)
            {
                m.colorCycle[i][j] = colorCycle[i][j];
            }
        }
        m.pieceCycle.resize(pieceCycle.size());
        for (int i = 0; i < pieceCycle.size(); i++)
        {
            m.pieceCycle[i].resize(pieceCycle[i].size());
            for (int j = 0; j < pieceCycle[i].size(); j++)
            {
                m.pieceCycle[i][j] = pieceCycle[i][j];
            }
        }
        movesTable.insert({name, m});
    }

    void GetColorCycle(vector<vector<int>>& cycle, const string name)
{
    if (Find(name))
    {
        cycle.resize(movesTable[name].colorCycle.size());

        for (int i=0; i<cycle.size(); i++) {
            cycle[i].resize(movesTable[name].colorCycle[i].size());
            for (int j=0; j<cycle[i].size(); j++) {
                cycle[i][j] = movesTable[name].colorCycle[i][j];
            }
        }
    }
    
}
void GetPieceCycle(vector<vector<int>>& cycle, const string name)
{
    if (Find(name))
    {
        cycle.resize(movesTable[name].pieceCycle.size());

        for (int i=0; i<cycle.size(); i++) {
            cycle[i].resize(movesTable[name].pieceCycle[i].size());
            for (int j=0; j<cycle[i].size(); j++) {
                cycle[i][j] = movesTable[name].pieceCycle[i][j];
            }
        }
    }
    
}

   //Init(&p, num);
   //if(p == NULL) {
   //   /*Memory allocation failed */
   //}

    bool Find(const string name) {
        if (movesTable.find(name) != movesTable.end())
            return true;
        else
        {
            cerr << "Move " << name << " not found" << endl;
            return false;
        }
    }


};