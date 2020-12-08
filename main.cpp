#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <algorithm>
#include <cmath>
#include <random>
//#include <bits/stdc++.h> 

using namespace std;

class Node {
public:
    int x, y;
    string number;
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
                gridNodes[i][j].number = to_string(i * gridSize + j + 1);
            }
        }

        gridNodes[gridSize - 1][gridSize - 1].number = " ";
    }

    void Print() {
        for (int i = 0; i < gridSize; i++) {
            for (int j = 0; j < gridSize; j++) {
                cout << " Node: " << gridNodes[i][j].number << endl;
            }
        }
    }

    void PrintGrid() {
        for (int i = 0; i < gridSize; i++) {
            cout << "|";
            for (int j = 0; j < gridSize; j++) {
                cout << " " << gridNodes[i][j].number << " |";
            }

            if (i != gridSize - 1) {
                cout << endl << "|---";
                for (int j = 0; j < gridSize - 1; j++)
                {
                    cout << "|---";
                }
                cout << "|";
            }
            cout << endl;
        }
    }

    void randomize() {
        array<int, 9> shuffleArray;

        //Iterate through 1..8 to populate shuffleArray with 1,2,3..8
        for (int i = 0; i < 9; i++) {
            shuffleArray[i] = i + 1;
        }

        unsigned seed = 0;

        // cout << "Seed: ," << seed;
        /*
        for (int i = 0; i < 9; i++) {
            cout << shuffleArray.at(i) << "";
        }
        

        cout << endl;
        */
        int original[9] = { 1,2,3,4,5,6,7,8,9 };
        shuffle(shuffleArray.begin(), shuffleArray.end(), default_random_engine(seed));
        for (int i = 0; i < 9; i++) {
            Swap(shuffleArray[i], original[i]);
        }
        /*
        for (int i = 0; i < 9; i++) {
            cout << shuffleArray.at(i) << " ";
        }
        */
    }

    /*
        void randomize(){
            //vector<int> randomArray(gridSize*gridSize);

            //Init array called shuffleArray with nodeNum which is 9 (gridsize of 9).
            cout << "Reached Randomize function" << endl;
            array<int, 9> shuffleArray;

            //Iterate through 1..9 to populate shuffleArray with 1,2,3..9
            for(int i = 0; i < nodeNum; i++){
                shuffleArray[i] = i+1;
            }
            unsigned seed = 0;
            cout << "Seed: " << seed << endl;
            shuffle(shuffleArray.begin(), shuffleArray.end(), default_random_engine(seed));
            //shuffleArray.size();
            for(int i = 0; i < 9; i++){
            cout << shuffleArray.at(i) << "";
            }
            //[1..nodeNum-1] <- shuffle that. Then swap the index of matrix with that shuffle
            //example: shuffled: [5,2,7,4,8,6,3,9,1]
            //ex:          grid: [1,2,3,4,5,6,7,8,9]


        }
        */
        void Shuffle(){
            int newShuffle[9] = {1,2,3,4,5,6,7,8,9};
            //int newShuffle[9] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
            //int newShuffle[9] {8,9,7,1,2,4,6,5,3};
            int original[9] =   {1,2,3,4,5,6,7,8,9};

            for(int i = 0; i < 9; i++){
                Swap(newShuffle[i], original[i]);
            }
        }

    void Swap(int newLoc, int oldLoc) {
        //locations being 1-9 as the spots on grid of 3x3
        int newLocX = floor(newLoc / (gridSize + 0.1));
        int newLocY = (newLoc - 1) % gridSize;
        int oldLocX = floor(oldLoc / (gridSize + 0.1));
        int oldLocY = (oldLoc - 1) % gridSize;

        string temp = gridNodes[oldLocX][oldLocY].number;
        gridNodes[oldLocX][oldLocY].number = gridNodes[newLocX][newLocY].number;
        gridNodes[newLocX][newLocY].number = temp;
    }



};



int main()
{
    Grid a;
    a.PrintGrid();
    cout << endl;
    //a.Shuffle();
    a.randomize();
    a.PrintGrid();
}