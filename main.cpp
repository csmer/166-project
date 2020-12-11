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
    int heuristic_value;
    int x, y;
    int number;
    int oX, oY;
    int currentLocation;
};

class Grid {
public:
    int gridSize;
    int nodeNum;
    Node** gridNodes;

    Grid(int size = 3) {
        gridSize = size;
        nodeNum = (gridSize * gridSize);
        gridNodes = new Node * [gridSize];

        for (int i = 0; i < gridSize; i++) {
            gridNodes[i] = new Node[size];
        }

       for (int i = 0; i < gridSize; i++) {
           for (int j = 0; j < gridSize; j++) {
               gridNodes[i][j].number = i * gridSize + j + 1;
               gridNodes[i][j].currentLocation = gridNodes[i][j].number;
               gridNodes[i][j].x = j;
               gridNodes[i][j].y = i;
               gridNodes[i][j].oX = j;
               gridNodes[i][j].oY = i;
           }
       }
    }

    void Print() {
        for (int i = 0; i < gridSize; i++) {
            for (int j = 0; j < gridSize; j++) {
                cout << "Node: " << gridNodes[i][j].number << 
                ", Ox: " << gridNodes[i][j].oX << ", Oy: " << gridNodes[i][j].oY << endl;

                cout << "Current Loc: " << gridNodes[i][j].currentLocation <<
                 ", x: " << gridNodes[i][j].x << ", y: " << gridNodes[i][j].y << endl << endl;
            }
        }
    }

    void PrintGridNumber()
    {
        int maxLength = to_string(gridSize * gridSize).length();
        string line = "|--";
        for (int i = 0; i < maxLength; i++)
        {
            line += "-";
        }

        for (int i = 0; i < gridSize; i++)
        {
            cout << "|";
            for (int j = 0; j < gridSize; j++)
            {
                if (gridNodes[i][j].number == (gridSize * gridSize))
                {
                    cout << " ";
                    for (int k = 0; k < maxLength; k++)
                    {
                        cout << " ";
                    }
                    cout << " |";
                }
                else if (to_string(gridNodes[i][j].number).length() < maxLength)
                {
                    cout << " ";
                    for (int k = 0; k < maxLength - to_string(gridNodes[i][j].number).length(); k++)
                    {
                        cout << " ";
                    }
                    cout << gridNodes[i][j].number << " |";
                }
                else
                {
                    cout << " " << gridNodes[i][j].number << " |";
                }
            }

            if (i != gridSize - 1)
            {
                cout << endl
                     << line; //<< "|---";
                //s

                for (int j = 0; j < gridSize - 1; j++)
                {
                    cout << line;
                }
                cout << "|";
            }
            cout << endl;
        }
    }

    void PrintGrid() {
        int maxLength = to_string(gridSize * gridSize).length();
        string line = "|--";
        for(int i = 0; i < maxLength; i++) {
            line += "-";
        }

        for (int i = 0; i < gridSize; i++) {
            cout << "|";
            for (int j = 0; j < gridSize; j++) {
                if (gridNodes[i][j].currentLocation == (gridSize * gridSize)) {
                    cout << " ";
                    for (int k = 0; k < maxLength; k++) {
                        cout << " ";
                    }
                    cout << " |";
                }
                else if (to_string(gridNodes[i][j].currentLocation).length() < maxLength)
                {
                    cout << " ";
                    for (int k = 0; k < maxLength - to_string(gridNodes[i][j].currentLocation).length(); k++){
                        cout << " ";
                    }
                    cout << gridNodes[i][j].currentLocation << " |";
                }
                else
                {
                    cout << " " << gridNodes[i][j].currentLocation << " |";
                }
            }

            if (i != gridSize - 1)
            {
                cout << endl << line; //<< "|---";
                //s

                for (int j = 0; j < gridSize - 1; j++){
                    cout << line;
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
        shuffle(&shuffleArray[0], &shuffleArray[nodeNum], default_random_engine(seed));

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

    void Swap(int Loc1y, int Loc1x, int Loc2y, int Loc2x) {
        Node temp = gridNodes[Loc1y][Loc1x];

        gridNodes[Loc1y][Loc1x].number = gridNodes[Loc2y][Loc2x].number;
        gridNodes[Loc1y][Loc1x].oX = gridNodes[Loc2y][Loc2x].oX;
        gridNodes[Loc1y][Loc1x].oY = gridNodes[Loc2y][Loc2x].oY;

        gridNodes[Loc2y][Loc2x].number = temp.number;
        gridNodes[Loc2y][Loc2x].oX = temp.oX;
        gridNodes[Loc2y][Loc2x].oY = temp.oY;
    }

    vector<int> ValidMoves(){
        //Print();
        Node* empty = nullptr;
        for (int i = 0; i < gridSize; i++) {
            for (int j = 0; j < gridSize; j++) {
                if(gridNodes[i][j].number == nodeNum){
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

        cout << "Valid Moves: ";
        for(int i = 0; i < validMoves.size(); i+=2) { 
            cout << "y " << validMoves[i] << " x " << validMoves[i+1] << ", ";
        }
        cout << endl << endl;
        return validMoves;
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

class IDA {
    public:
    int threshHold;


    IDA(){
        int lol = 0;
    };

    int BestMove(vector<int> moves){

    }

};

class BFS{

};
// TODO: BFS uses valid moves for starting node then swap in BFS order

class BoardGame {
    public:
    Grid* grid;
    IDA search;

    BoardGame(){
        /*
        int size;
        cout << "Enter Board Size 3 or Above: ";
        cin >> size;
        cout << endl;
        if(size < 3){
            cout << "Invalid Size! Defaulted to Size: 3" << endl;
            grid = new Grid;
        }
        else{
            grid = new Grid(size);
        }
        */
       grid = new Grid;
    }

};

int main()
{
    BoardGame game;
    //game.grid->Print();
    //Grid a;
    //a.Print();
    //cout << endl;
    game.grid->PrintGrid();
    cout << endl;

    //game.grid->ValidMoves();
    //game.grid->PrintGridNumbers();
    //cout << endl;
    //game.grid->randomize();
    //game.grid->Shuffle();
    //game.grid->PrintGrid();
    //game.grid->PrintGridNumbers();
    game.grid->Swap(0, 2, 1, 1);
    //cout << endl << "SWAP" << endl;
    game.grid->PrintGridNumber();
    game.grid->ValidMoves();
    //cout << endl;
}  
