#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <algorithm>
#include <cmath>
#include <queue>
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
               gridNodes[i][j].x = j;
               gridNodes[i][j].y = i;
           }
       }
    }

    void Print() {
        for (int i = 0; i < gridSize; i++) {
            for (int j = 0; j < gridSize; j++) {
                cout << " Node: " << gridNodes[i][j].number << 
                ", Current Loc: " << gridNodes[i][j].currentLocation <<
                 ", x: " << gridNodes[i][j].x << ", y: " << gridNodes[i][j].y << endl;
            }
        }
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

        int* original = new int [nodeNum];
        for(int i = 0; i < nodeNum; i++){
            original[i] = i+1;
        }

        Node **newNodes = new Node *[gridSize];
        for (int i = 0; i < gridSize; i++){
            newNodes[i] = new Node[gridSize];
        }

        for (int i = 0; i < nodeNum; i++)
        {
            int newLocY = floor(shuffleArray[i] / (gridSize + 0.1));
            int newLocX = (shuffleArray[i] - 1) % gridSize;
            int oldLocY = floor(original[i] / (gridSize + 0.1));
            int oldLocX = (original[i] - 1) % gridSize;

            newNodes[newLocY][newLocX] = gridNodes[oldLocY][oldLocX];
            newNodes[newLocY][newLocX].currentLocation = shuffleArray[i];
            newNodes[newLocY][newLocX].x = newLocX;
            newNodes[newLocY][newLocX].y = newLocY;
        }

        for (int i = 0; i < gridSize; i++)
        {
            for (int j = 0; j < gridSize; j++)
            {
                gridNodes[i][j] = newNodes[i][j];
            }
        }
    } */


    void Shuffle(){
        //int newShuffle[9] = {1,2,3,4,5,6,7,8,9}; 
        //int newShuffle[9] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
        int newShuffle[9] = {8,9,7,1,2,4,6,5,3};
        int original[9] =   {1,2,3,4,5,6,7,8,9};

        Node** newNodes = new Node *[gridSize];
        for (int i = 0; i < gridSize; i++) {
            newNodes[i] = new Node[gridSize];
        }

        for (int i = 0; i < nodeNum; i++){
            int newLocY = floor(newShuffle[i] / (gridSize + 0.1));
            int newLocX = (newShuffle[i] - 1) % gridSize;
            int oldLocY = floor(original[i] / (gridSize + 0.1));
            int oldLocX = (original[i] - 1) % gridSize;

            newNodes[newLocY][newLocX] = gridNodes[oldLocY][oldLocX];
            newNodes[newLocY][newLocX].currentLocation = newShuffle[i];
            newNodes[newLocY][newLocX].x = newLocX;
            newNodes[newLocY][newLocX].y = newLocY;
        }

        for (int i = 0; i < gridSize; i++) {
            for (int j = 0; j < gridSize; j++) {
                gridNodes[i][j] = newNodes[i][j];
            }
        }
    }

    void Swap(int Loc1y, int Loc1x, int Loc2y, int Loc2x) { //fixme
        Node temp = gridNodes[Loc1x][Loc1y];
        temp.x = Loc2x;
        temp.y = Loc2y;
        gridNodes[Loc1y][Loc1x] = gridNodes[Loc2y][Loc2x];
        gridNodes[Loc2x][Loc2x] = temp;
    }

    int ValidMoves(){
        Print();
        Node* empty = nullptr;
        for (int i = 0; i < gridSize; i++) {
            for (int j = 0; j < gridSize; j++) {
                if(gridNodes[i][j].number == 9){
                    empty = &gridNodes[i][j];
                }
            }
        }

        int* moves = new int[8];
        moves[0] = empty->y + 1; moves[1] = empty->x; //up side
        moves[2] = empty->y - 1; moves[3] = empty->x; //down side
        moves[4] = empty->y; moves[5] = empty->x + 1; //right side
        moves[6] = empty->y; moves[7] = empty->x - 1; //left side

        vector<int> validMoves;
        for(int i = 0; i < 8; i++){
            if( (-1 < moves[i]) && (moves[i] < gridSize) ){
                validMoves.push_back(moves[i]);
            }
            else if(i % 2 == 1){
                validMoves.pop_back();
            }
            else{
                i++;
            }
        }

        int* moves2 = new int[validMoves.size()];
        for(int i = 0; i < validMoves.size(); i++) { 
            moves2[i] = validMoves.at(i); 
        }
        

        cout << "Valid Moves: ";
        for(int i = 0; i < validMoves.size(); i+=2) { 
            cout << "y " << moves2[i] << " x " << moves2[i+1] << ", ";
        }
        cout << endl << endl;
        return *moves2;
    }

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

    a.ValidMoves();
    //a.PrintGridNumbers();
    //cout << endl;
    //a.randomize();
    a.Shuffle();
    //a.PrintGrid();
    a.PrintGridNumbers();

    a.ValidMoves();
    cout << endl;
}  