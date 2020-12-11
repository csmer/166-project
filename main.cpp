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
    int currentLocation;
    int number;
};

class Grid {
public:
    int gridSize;
    int nodeNum;
    Node** gridNodes;

    Grid() {
        gridSize = 3;
        nodeNum = (gridSize * gridSize);
        gridNodes = new Node * [gridSize];

        for (int i = 0; i < gridSize; i++) {
            gridNodes[i] = new Node[3];
        }

       for (int i = 0; i < gridSize; i++) {
           for (int j = 0; j < gridSize; j++) {
               gridNodes[i][j].number = i * gridSize + j + 1;
               gridNodes[i][j].currentLocation = gridNodes[i][j].number;
               gridNodes[i][j].x = i;
               gridNodes[i][j].y = j;
           }
       }
    }

    void Print() {
        for (int i = 0; i < gridSize-1; i++) {
            for (int j = 0; j < gridSize; j++) {
                cout << " Node: " << gridNodes[i][j].number << 
                ", Current Loc: " << gridNodes[i][j].currentLocation << endl;
            }
        }
        for (int j = 0; j < gridSize-1; j++){
            cout << " Node: " << gridNodes[gridSize-1][j].number << 
            ", Current Loc: " << gridNodes[gridSize-1][j].currentLocation << endl;
        }
        cout << " Node: " << "_" << 
        ", Current Loc: " << gridNodes[gridSize - 1][gridSize - 1].currentLocation << endl;
    }

    void PrintGridNumbers() {
        int maxLength = to_string(gridSize * gridSize).length();
        for (int i = 0; i < gridSize; i++) {
            cout << "|";
            for (int j = 0; j < gridSize; j++){
                if (gridNodes[i][j].number == (gridSize * gridSize)) {
                    cout << " ";
                    for (int k = 0; k < maxLength; k++) {
                        cout << " ";
                    }
                    cout << " |";
                }
                else if (to_string(gridNodes[i][j].number).length() < maxLength) {
                    cout << " ";
                    for (int k = 0; k < maxLength - to_string(gridNodes[i][j].number).length(); k++) {
                        cout << " ";
                    }
                    cout << " |";
                }
                else {
                    cout << " " << gridNodes[i][j].number << " |";
                }
            }

            if (i != gridSize - 1) {
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

    void PrintGrid()
    {
        int maxLength = to_string(gridSize * gridSize).length();
        for (int i = 0; i < gridSize; i++)
        {
            cout << "|";
            for (int j = 0; j < gridSize; j++)
            {
                if (gridNodes[i][j].currentLocation == (gridSize * gridSize))
                {
                    cout << " ";
                    for (int k = 0; k < maxLength; k++)
                    {
                        cout << " ";
                    }
                    cout << " |";
                }
                else if (to_string(gridNodes[i][j].currentLocation).length() < maxLength)
                {
                    cout << " ";
                    for (int k = 0; k < maxLength - to_string(gridNodes[i][j].currentLocation).length(); k++)
                    {
                        cout << " ";
                    }
                    cout << " |";
                }
                else
                {
                    cout << " " << gridNodes[i][j].currentLocation << " |";
                }
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
/*
    void randomize() {
        int* shuffleArray = new int[nodeNum];

        //Iterate through 1..8 to populate shuffleArray with 1,2,3..8
        for (int i = 0; i < nodeNum; i++) {
            shuffleArray[i] = i + 1;
        }
        unsigned seed = 0;
        shuffle(&shuffleArray[0], &shuffleArray[nodeNum-1], default_random_engine(seed));

        int **tempArray = new int *[gridSize];
        for (int i = 0; i < gridSize; i++) {
            tempArray[i] = new int[3];
        }

        int original[nodeNum];
        for(int i = 0; i < nodeNum; i++){
            original[i] = i+1;
        }

        for (int i = 0; i < 9; i++) {
            RandSwap(shuffleArray[i], original[i], tempArray);
        }

        for (int i = 0; i < gridSize; i++) {
            for (int j = 0; j < gridSize; j++) {
                gridNodes[i][j].currentLocation = tempArray[i][j];
            }
        }
    }
    */

    void Shuffle(){
        //int newShuffle[9] = {1,2,3,4,5,6,7,8,9}; 
        //int newShuffle[9] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
        int newShuffle[9] = {8,9,7,1,2,4,6,5,3};
        int original[9] =   {1,2,3,4,5,6,7,8,9};

        int** tempArray = new int *[gridSize];
        for (int i = 0; i < gridSize; i++){
            tempArray[i] = new int[3];
        }
        //int tempArray[gridSize][gridSize];

        for(int i = 0; i < 9; i++){
            RandSwap(newShuffle[i], original[i], tempArray);
        }

        for (int i = 0; i < gridSize; i++) {
            for (int j = 0; j < gridSize; j++) {
                gridNodes[i][j].currentLocation = tempArray[i][j];
            }
        }
    }

    void RandSwap(int newLoc, int oldLoc, int** newArray){
        //locations being 1-9 as the spots on grid of 3x3
        int newLocX = floor(newLoc / (gridSize + 0.1));
        int newLocY = (newLoc - 1) % gridSize;
        int oldLocX = floor(oldLoc / (gridSize + 0.1));
        int oldLocY = (oldLoc - 1) % gridSize;

        //cout << "New Location: " << newLoc << ", Old Location: " << oldLoc << endl;
        //cout << "New X: " << newLocX << ", New Y: " << newLocY << endl;
        //cout << "Old X: " << oldLocX << ", Old Y: " << oldLocY << endl;

        newArray[newLocX][newLocY] = gridNodes[oldLocX][oldLocY].currentLocation;
    }

    void Swap(int Loc1x, int Loc1y, int Loc2x, int Loc2y){
        int temp = gridNodes[Loc1x][Loc1y].currentLocation;
        gridNodes[Loc1x][Loc1y].currentLocation = gridNodes[Loc2x][Loc2y].currentLocation;;
        gridNodes[Loc2x][Loc2y].currentLocation = temp;
    }

    /*
    void ValidMoves(){
        Node* empty = &gridNodes[gridSize-1][gridSize-1];
    }
    */

    bool CheckSorted(){
        for (int i = 0; i < gridSize; i++) {
            for (int j = 0; j < gridSize; j++) {
                if(gridNodes[i][j].currentLocation != gridNodes[i][j].number){
                    return false;
                }
            }
        }
        return true;
    }
};


int main()
{
    Grid a;
    //a.Print();
    //cout << endl;
    a.PrintGrid();
    cout << endl;
    //a.PrintGridNumbers();
    //cout << endl;
    //a.randomize();
    a.Shuffle();
    a.PrintGrid();
    cout << endl;
}  