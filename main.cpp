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
    for(int i = 0; i < loop; i++) {
        game->grid->Swap(game->BestMove(game->grid->ValidMoves(), game->grid->Empty()), game->grid->Empty());
        cout << "Loop: " << i << endl;
        game->grid->PrintGridNumber();
        cout << endl;

        if (game->grid->CheckSorted()) {
            cout << "Finished" << endl;
            return;
        }
    }
    cout << "Hit the loop Limit" << endl;
}

/*
void RandomizeGrid(int loop, BoardGame *game){
    for(int i = 0; i < loop; i++){
        game->grid->Randomize();
        //cout << "Loop: " << i << endl;
        if (game->grid->isSolveable()) {
            game->grid->PrintGridNumber();
            break;
        }
    }
}*/

int main() {
    BoardGame game;
    game.grid->PrintGridNumber();
    game.grid->ShuffleTest();
    game.grid->PrintGridNumber();
    RunIDASearch(100, &game);

    //RandomizeGrid(10, &game);
    //RunIDASearch(100, &game);
}