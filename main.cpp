#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <algorithm>
#include <cmath>
#include <queue>
#include <random>

//Classes for Program
#include "node.h" //Nodes represent the tiles of Sliding Game
#include "grid.h" //Grid is all the Nodes(tiles) on grid and their functions
#include "boardGame.h" //BoardGame that has IDA* and Grid 

using namespace std;

void RunIDASearch(int loop, BoardGame* game) {
    for(int i = 0; i < loop; i++) { //Runs the IDA Search for a limited amount of iteration to avoid long loops.
        game->grid->Swap(game->BestMove(game->grid->ValidMoves(), game->grid->Empty()), game->grid->Empty());
        cout << "Loop: " << i << endl;
        game->grid->PrintGridNumber();
        cout << endl;

        if (game->grid->CheckSorted()) { //if the Grid becomes sorted break
            cout << "Finished" << endl;
            return;
        }
    }
    //if unable to sort grid within number of loops
    cout << "Hit the loop Limit" << endl;
}


void RandomizeGrid(int loop, BoardGame *game){ //Function to be called in main
    for(int i = 0; i < loop; i++){ //Iterate through for a number of times
        game->grid->Randomize(); //Randomize/shuffle the grid
        //cout << "Loop: " << i << endl;
        if (game->grid->isSolveable()) { //If it is solveable, print the grid numbers then break
            game->grid->PrintGridNumber();
            break;
        }
    }
}

int main() {
    BoardGame game;
    //Initial State
    game.grid->PrintGridNumber();

    //Confirmed working Test Case
    game.grid->ShuffleTest();
    game.grid->PrintGridNumber();
    RunIDASearch(100, &game);

    //Randomized Case.
    //Uncomment to Run.
    /*
    RandomizeGrid(10, &game);
    RunIDASearch(100, &game);
    */
}