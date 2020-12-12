class Node
{ //Represents a Segment of grid, aka Tile
public:
    int heuristic_value;

    int oX, oY; //Original  X, Y
    int number; //Original Number of Node

    int x, y; //Current X, Y cords
    int currentLocation;
};