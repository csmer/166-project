# 166-project
 Team Project with Micah Mercado and Harpreet Ghag
Fresno State Fall 2020
CSCI 166
Sliding Puzzle Project
Harpreet Ghag & Micah Mercado

https://github.com/HarpreetGh/166-project


A sliding puzzle puzzle is played by sliding a tile along cardinal directions in a N^2 grid. A tile or node can only move into the empty slot (our project uses the number 9 as the empty slot). There is only ever 1 empty slot. The tiles can be numbers or images - in our case they are numbers printed in a grid in the terminal. The grid can scale up such as 4x4, 5x5, or whatever number is given for the grid size. The grid space can be considered a graph and we try to implement and study solving it as a search problem (BFS, DFS, A*, IDA* with heuristics, etc.). The graph is weighted with weights of 1 (because a connection between 1 node and the empty space is 1), cyclic (the nodes can go in circles - forever looping), and is undirected (or bidirectional). Each piece of the grid is a Node aka tile. The node acts as a data structure to contain the goal state, as well as its current state, via x and y coordinates; as well as the numbers displayed on tile. The grid has many functions that manipulate the nodes, and allows us to access them easily. The grid dwells in the BoardGame Class which contains all the IDA* functions. For specific information on all functions please refer to the source code, as there is additional information there.

States: There will be a N^2 grid, that contains N^2 - 1 numbered squares, and 1 empty state. There is a final or goal state which is the solution/correct configuration of the grid containing the squares in the correct position. 
Actions: Moving a single tile in cardinal directions: up, down, left, right into the empty state, and the empty state moves to where the tile came from. 
Rewards: There is only a reward for the entire Grid to be sorted.
Transition Model: The Empty State or space on the grid is swapped with an adjacent tile leaving a new empty state from where the adjacent tile went from, only if it doesn’t undo the previous transition. The Tile closest to its goal plus  the tile after it determines which tile is moved into empty state.

All code is written in C++ using Visual Studio Code and Visual Studio 2019 utilizing Github Desktop for version control. We implemented Iterative Deepening A* or IDA* (for the most part) and researched how depth-first search and breadth-first search would work on our problem representation of search on a graph. We also have several functions regarding the grid and nodes (or tiles): print, print the grid, print the grid’s numbers, randomize the contents of the grid, checking if the grid is solvable (along with a helper function to see - count the number of inversions on the graph, even number of inversions solvable, odd number of inversions not solvable), a shuffle test (a working example or use case of the grid), and swapping nodes (to move them in a sense). DFS would not work with our graph because it is cyclic, going into a loop forever sometimes. BFS would work but not as fast as IDA* due to not having knowledge like a heuristic (BFS being uninformed). 

For IDA* to work, we have a heuristic function which calculates the distance from current location to goal state, as well as the distance from empty state to goal state. Normally in IDA*, the cost is f(x) = g(x) + h(x), however in our case the costs are universally the same to move one tile compared to another, we simply ignore the cost, and use our heuristic measures for f(x). We get the heuristic values of the possible moves that can occur from the empty state, using validMoves() in the Grid Class. We further filter the Valid Moves by eliminating the previous move, and removing moves that result in increasing the heuristic value; just in case all values are removed we use the least negative heuristic value. From there we check the heuristic value of the depth 1 to see deeper, and update the heuristic value of current search iteration. We recursively call the IDA* search once. We experience no gains, by increasing the depth greater than 1. Next we get the lowest heuristic value to be our threshold, and use that to find our best possible move, and return the Node to be moved into the Empty spot, via Swap in Grid class.  

Our results or output is shown in RESULT_IDA_RANDOMIZE.txt and RESULT_IDA_SHUFFLE.txt
In result_ida_shuffle, the shuffle test function is called and completes it within 39 steps. The result_ida_randomize file uses the randomize function and does not complete it within 100 steps (it is possible that it is beyond 100 steps for IDA to complete). 
Pictures of the two outputs at the end of the file is shown on the next two pages.


RESULT_IDA_SHUFFLE:                                                           RESULT_IDA_RANDOMIZE:






