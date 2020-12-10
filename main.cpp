#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <algorithm>
#include <cmath>
#include <random>

using namespace std;

class Node {
    public:
    int x, y;
    string currentLocation;
    string number;
};

class Grid {
    public:
    int gridSize;
    int nodeNum;
    Node** gridNodes;

    Grid(){
       gridSize = 3;
       nodeNum = (gridSize*gridSize);
       gridNodes= new Node*[gridSize];

       for(int i = 0; i < gridSize; i++){
           gridNodes[i] = new Node[3];
       }

       for (int i = 0; i < gridSize; i++) {
           for (int j = 0; j < gridSize; j++) {
               gridNodes[i][j].number = to_string(i * gridSize + j + 1);
               gridNodes[i][j].currentLocation = gridNodes[i][j].number;
           }
       }

       gridNodes[gridSize-1][gridSize-1].number = " ";
    }

    void Print(){
        for(int i = 0; i < gridSize; i++) {
            for (int j = 0; j < gridSize; j++) {
                cout << " Node: " << gridNodes[i][j].number << ", Current Loc: " << gridNodes[i][j].currentLocation << endl;
            }
        }
    }

    void PrintGridNumbers()
    {
        for (int i = 0; i < gridSize; i++)
        {
            cout << "|";
            for (int j = 0; j < gridSize; j++)
            {
                cout << " " << gridNodes[i][j].number << " |";
            }

            if (i != gridSize - 1)
            {
                cout << endl
                     << "|---";
                for (int j = 0; j < gridSize - 1; j++)
                {
                    cout << "|---";
                }
                cout << "|";
            }
            cout << endl;
        }
    }

    void PrintGrid(){
        for (int i = 0; i < gridSize; i++) {
            cout << "|";
            for (int j = 0; j < gridSize; j++) {
                cout << " " << gridNodes[i][j].currentLocation << " |";
            }
                
            if(i != gridSize-1){
                cout << endl << "|---" ;
                for (int j = 0; j < gridSize-1; j++)
                {
                    cout << "|---";
                }
                cout << "|";
            }
                cout << endl;
        }
    }

    void Shuffle(){
        //int newShuffle[9] = {1,2,3,4,5,6,7,8,9}; 
        //int newShuffle[9] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
        int newShuffle[9] = {8,9,7,1,2,4,6,5,3};
        int original[9] =   {1,2,3,4,5,6,7,8,9};

        string** tempArray = new string *[gridSize];
        for (int i = 0; i < gridSize; i++){
            tempArray[i] = new string[3];
        }

        for(int i = 0; i < 9; i++){
            Swap(newShuffle[i], original[i], tempArray);
        }

        for (int i = 0; i < gridSize; i++) {
            for (int j = 0; j < gridSize; j++) {
                gridNodes[i][j].currentLocation = tempArray[i][j];
            }
        }
    }

    void Swap(int newLoc, int oldLoc, string** newArray){
        //locations being 1-9 as the spots on grid of 3x3
        int newLocX = floor(newLoc / (gridSize + 0.1));
        int newLocY = (newLoc - 1) % gridSize;
        int oldLocX = floor(oldLoc / (gridSize + 0.1));
        int oldLocY = (oldLoc - 1) % gridSize;

        cout << "New Location: " << newLoc << ", Old Location: " << oldLoc << endl;
        cout << "New X: " << newLocX << ", New Y: " << newLocY << endl;
        cout << "Old X: " << oldLocX << ", Old Y: " << oldLocY << endl;

        newArray[newLocX][newLocY] = gridNodes[oldLocX][oldLocY].currentLocation;
    }
};



int main()
{
    Grid a;
    a.PrintGrid();
    cout << endl;
    a.PrintGridNumbers();
    cout << endl;
    a.Shuffle();
    a.PrintGrid();
    cout << endl;
    //a.PrintGridNumbers();
}