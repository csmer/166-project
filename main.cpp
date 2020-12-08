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
    Node* gridNodes;

    Grid(){
       gridSize = 3;
       nodeNum = (gridSize*gridSize);
       gridNodes = new Node[nodeNum];
       
       for(int i = 0; i < nodeNum-1; i++){
           gridNodes[i].number = to_string(i+1);
       }
       gridNodes[nodeNum-1].number = " ";
    }

    void Print(){
        for (int i = 0; i < nodeNum; i++)
        {
           cout << "Node: " << gridNodes[i].number << endl;
        }
    }
    
    void PrintGrid(){
        int i = 0;

        while(i < nodeNum){
            cout << "|";
            for(int j = 0; j < gridSize; j++){
                cout << " " << gridNodes[i].number << " |";
                i+=1;
            }

            if(i < nodeNum){
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