#include <vector>
#include <algorithm>
#include <iostream>
#include <array>
using namespace std;

class MoveHelper
{
public:
    static void CombineColorPiece(vector<int> colors, vector<int> pieces,
                                  vector<vector<vector<int>>> &finalMatrix)
    {
        if (colors.size() == 0 || pieces.size() == 0)
            throw("ERROR: (MoveHelper::CombinePieceColor) wrong sizes of vectors");
        vector<vector<int>> auxMatrix;
        vector<int> auxVector(2);
        if (colors.size() % pieces.size() == 0)
        {
            for (int i = 0; i < colors.size(); i++)
            {
                auxVector = {colors[i], pieces[i % pieces.size()]};
                auxMatrix.emplace_back(auxVector.begin(), auxVector.end());
            }
            finalMatrix.emplace_back(auxMatrix.begin(), auxMatrix.end());
        }
        else if (pieces.size() % colors.size() == 0)
        {
            for (int i = 0; i < pieces.size(); i++)
            {
                auxVector = {colors[i % colors.size()], pieces[i]};
                auxMatrix.emplace_back(auxVector.begin(), auxVector.end());
            }
            finalMatrix.emplace_back(auxMatrix.begin(), auxMatrix.end());
        }
        else
            throw("ERROR: (MoveHelper::CombinePieceColor) wrong sizes of vectors");
    }
};