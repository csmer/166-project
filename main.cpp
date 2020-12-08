#include <iostream>
#include <vector>
#include <string>
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
           }
       }

       gridNodes[gridSize-1][gridSize-1].number = " ";
    }

    void Print(){
        for(int i = 0; i < gridSize; i++) {
            for (int j = 0; j < gridSize; j++) {
                cout << " Node: " << gridNodes[i][j].number << endl; 
            }
        }
    }
    
    void PrintGrid(){
        for (int i = 0; i < gridSize; i++) {
            cout << "|";
            for (int j = 0; j < gridSize; j++) {
                cout << " " << gridNodes[i][j].number << " |";
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

    void randomizeArray(){
        
        //random_shuffle(arr.begin(), arr.end());
    }

    
};



int main()
{
    Grid a;
    a.PrintGrid();
}