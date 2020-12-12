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
        int newShuffle[9] = {1,9,5,8,3,2,4,6,7};
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

    void Swap2(Node* node1, Node* node2){
        Node temp = *node1;
        node1->number = node2->number;
        node1->oX = node2->oX;
        node1->oY = node2->oY;

        node2->number = temp.number;
        node2->oX = temp.oX;
        node2->oY = temp.oY;
    }

    Node* Empty(){
        Node *empty = nullptr;
        for (int i = 0; i < gridSize; i++)
        {
            for (int j = 0; j < gridSize; j++)
            {
                if (gridNodes[i][j].number == nodeNum)
                {
                    return empty = &gridNodes[i][j];
                }
            }
        }
    }

    vector<Node*> ValidMoves(int y = -1, int x = -1){
        Node* node = nullptr;
        if(x == -1 && y ==-1){
            node = Empty();
        }
        else{
            node = &gridNodes[y][x];
        }

        int* moves = new int[8];
        moves[0] = node->y + 1; moves[1] = node->x; //up side
        moves[2] = node->y - 1; moves[3] = node->x; //down side
        moves[4] = node->y; moves[5] = node->x + 1; //right side
        moves[6] = node->y; moves[7] = node->x - 1; //left side

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

        vector<Node*> validNodes;
        for(int i = 0; i < validMoves.size(); i+=2){
            validNodes.push_back(&gridNodes[validMoves[i]][validMoves[i+1]]);
        }
        return validNodes;
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
    /*
    int threshHold;
    Node** gridNodes;

    IDA(Node** nodes = nullptr){
        gridNodes = nodes;
    };

    void Sort(vector<int>* arr){
        int step = 0;
        for(int i = 0; i < arr->size(); ++i) {
            int min = i;
            for(int j = i + 1; j < arr->size(); ++j) {
                if(arr[j] < arr[min]) {
                    min = j;
                }
                step++;
            }
            int temp = arr->at(i);
            arr[i] = arr[min];
            arr->at(min) = temp;
        }
    }

    int BestMove(vector<int> moves){
        int threshHold = 0;
        vector<int> heuristic_values = Heuristic(moves);
        for(int i = 0; i < nodeNum)

        //IDA* usually has a f(x) = g(x) [cost] + h(x) [heuritic], 
        //however the weight of each path is same so f(x) = h(x)

        int small = heuristic_values[0];
        /*
        for (int i = 1; i < heuristic_values.size(); i++) {
            if(heuristic_values[i] < small){

            }
        }
        *//*
    }

    vector<int> Heuristic(vector<int> moves) {
        int y, x;
        vector<int> values;
        for(int i = 0; i < moves.size(); i+=2){
            y = moves.at(i);
            x = moves.at(i+1);

            values.push_back((gridNodes[y][x].oY - y) + abs(gridNodes[y][x].oX - x));
        }
        return values;
    }
    */
};

class BFS{

};
// TODO: BFS uses valid moves for starting node then swap in BFS order

class BoardGame {
    public:
    Grid* grid;
    IDA* search;
    int* previous;

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
       previous = new int[2];
       for(int i = 0; i < 2; i++){
           previous[i] = -1;
       }
       //search = new IDA(grid->gridNodes);
    }

    void Sort(vector<int> *arr)
    {
        int step = 0;
        for (int i = 0; i < arr->size(); ++i)
        {
            int min = i;
            for (int j = i + 1; j < arr->size(); ++j)
            {
                if (arr[j] < arr[min])
                {
                    min = j;
                }
                step++;
            }
            int temp = arr->at(i);
            arr[i] = arr[min];
            arr->at(min) = temp;
        }
    }

    Node* BestMove(vector<Node*> moves, Node* start) {
        vector<int> heuristic_values = Heuristic(moves, start->y, start->x);
        int cost = 0; //IDA* usually has a f(x) = g(x) [cost] + h(x) [heuritic],
        //however the weight of each path is same so f(x) = h(x)
        if (previous[0] != -1) {
            for(int i = 0; i < moves.size(); i++){
                if (moves[i]->y == previous[0] &&
                    moves[i]->x == previous[1] ) {

                    moves[i] = moves[moves.size()-1];
                    heuristic_values[i] = heuristic_values[heuristic_values.size()-1];
                    moves.pop_back();
                    heuristic_values.pop_back();
                    break;
                }
            }
        }

        int threshHold = heuristic_values[0];
        for (int i = 1; i < heuristic_values.size(); i++) {
            if (heuristic_values[i] < threshHold){
                threshHold = heuristic_values[i];
            }
        }

        int bestMove[2];
        vector<Node*> nodes;
        Node* node = nullptr;

        for (int i = 0; i < moves.size(); i++){
            if (heuristic_values[i] <= threshHold) {
                nodes.push_back(moves[i]);
            }
        }
        previous[0] = start->y;
        previous[1] = start->x;
        return(nodes.at(0));
        /*
        if(nodes.size() > 1){
            for (int i = 0; i < nodes.size(); i++){
                //BestMove(grid->ValidMoves(nodes[i]->x, nodes[i]->y), );
            }
        }
        */
        
    }

    vector<int> Heuristic(vector<Node*> moves, int emptyY, int emptyX){
        vector<int> values;
        for (int i = 0; i < moves.size(); i ++){
            values.push_back(
                abs(moves[i]->oY - emptyY) + 
                abs(moves[i]->oX - emptyX));
        }
        return values;
    }
    /*
    void IDA1(){
        /*
        path              //current search path (acts like a stack)
        node              //current node (last node in current path)
        //g                 //the cost to reach current node
        int f                 //estimated cost of the cheapest path (root..node..goal)
        int h(node)           //estimated cost of the cheapest path (node..goal)
        cost(node, succ)  //step cost function
        is_goal(node)     //goal test
        successors(node)  //node expanding function, expand nodes ordered by g + h(node)
        ida_star(root)    //return either NOT_FOUND or a pair with the best path and its cost
        *//*
    }

    int H(Node* node) {
        return (abs(node->oY - node->y) +
            abs(node->oX - node->x));
    }

    void ida_star(Node* root, vector<Node*> moves) {
        int bound = 0;
        int t = 0;
        for(int i = 0; i < moves.size(); i++){
            t = Search(moves[i], bound);
            if t = FOUND then return (path, bound)
            if t = ∞ then return NOT_FOUND
            bound = t;
        }
    }

    int Search(Node* node, int bound){
        int f = H(node);
        if (f > bound){ return f; }
        if (is_goal(node)){ return 1; } //true
        int min = grid->nodeNum+1;
        for(succ in successors(node){
            if(succ not in path) {}
                path.push(succ)
                t := search(path, g + cost(node, succ), bound)
                if t = FOUND then return FOUND
                if t < min then min := t
                path.pop()
            }
        }
        return min
    } 

    bool is_goal(Node* node){
        return (node->oX == emtpy);
    }
    
    }*/
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
    game.grid->Shuffle();
    //game.grid->PrintGrid();
    //game.grid->PrintGridNumbers();
    //game.grid->Swap(0, 2, 1, 1);
    //cout << endl << "SWAP" << endl;
    game.grid->PrintGridNumber();
    //game.grid->ValidMoves();
    cout << endl;
    int i = 0;
    while(i < 25){
        game.grid->Swap2(game.BestMove(game.grid->ValidMoves(), game.grid->Empty()), game.grid->Empty());
        game.grid->PrintGridNumber();
        cout << endl;
        i++;
    }
}  
