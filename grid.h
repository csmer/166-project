using namespace std;

class Grid
{
public:
    int gridSize;
    int nodeNum;
    Node **gridNodes;

    Grid(int size = 3)
    {
        gridSize = size;
        nodeNum = (gridSize * gridSize);
        gridNodes = new Node *[gridSize];

        for (int i = 0; i < gridSize; i++)
        {
            gridNodes[i] = new Node[size];
        }

        for (int i = 0; i < gridSize; i++)
        {
            for (int j = 0; j < gridSize; j++)
            {
                gridNodes[i][j].number = i * gridSize + j + 1;
                gridNodes[i][j].currentLocation = gridNodes[i][j].number;
                gridNodes[i][j].x = j;
                gridNodes[i][j].y = i;
                gridNodes[i][j].oX = j;
                gridNodes[i][j].oY = i;
            }
        }
    }

    void Print()
    {
        for (int i = 0; i < gridSize; i++)
        {
            for (int j = 0; j < gridSize; j++)
            {
                cout << "Node: " << gridNodes[i][j].number << ", Ox: " << gridNodes[i][j].oX << ", Oy: " << gridNodes[i][j].oY << endl;

                cout << "Current Loc: " << gridNodes[i][j].currentLocation << ", x: " << gridNodes[i][j].x << ", y: " << gridNodes[i][j].y << endl
                     << endl;
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
                     << line;
                for (int j = 0; j < gridSize - 1; j++)
                {
                    cout << line;
                }
                cout << "|";
            }
            cout << endl;
        }
        cout << endl;
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
        for(int i = 0; i < nodeNum; i++) {
            original[i] = i+1;
        }

        Node **newNodes = new Node *[gridSize];
        for (int i = 0; i < gridSize; i++) {
            newNodes[i] = new Node[gridSize];
        }

        for (int i = 0; i < nodeNum; i++) {
            int newLocY = floor(shuffleArray[i] / (gridSize + 0.1));
            int newLocX = (shuffleArray[i] - 1) % gridSize;
            int oldLocY = floor(original[i] / (gridSize + 0.1));
            int oldLocX = (original[i] - 1) % gridSize;

            newNodes[newLocY][newLocX] = gridNodes[oldLocY][oldLocX];
            newNodes[newLocY][newLocX].currentLocation = shuffleArray[i];
            newNodes[newLocY][newLocX].x = newLocX;
            newNodes[newLocY][newLocX].y = newLocY;
        }

        for (int i = 0; i < gridSize; i++) {
            for (int j = 0; j < gridSize; j++) {
                gridNodes[i][j] = newNodes[i][j];
            }
        }
    }
    */

    // Helper function for isSolveable function
    int getInvCount()
    {
        int count = 0;
        for (int i = 0; i < nodeNum - 1; i++)
        {
            for (int j = i + 1; j < nodeNum; j++)
            {
                if (gridNodes[j] && gridNodes[i] && gridNodes[i] > gridNodes[j])
                    count++;
            }
        }
        return count;
    }

    bool isSolveable()
    { // Checks to see if sliding puzzle is solvable
        int invCount = getInvCount();
        return (invCount % 2 == 0); // True if number of inversions are even
    }

    void ShuffleTest()
    {
        int newShuffle[9] = {1, 9, 5, 8, 3, 2, 4, 6, 7};
        int original[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

        Node **newNodes = new Node *[gridSize];
        for (int i = 0; i < gridSize; i++)
        {
            newNodes[i] = new Node[gridSize];
        }

        for (int i = 0; i < nodeNum; i++)
        {
            int newLocY = floor(newShuffle[i] / (gridSize + 0.1));
            int newLocX = (newShuffle[i] - 1) % gridSize;
            int oldLocY = floor(original[i] / (gridSize + 0.1));
            int oldLocX = (original[i] - 1) % gridSize;

            newNodes[newLocY][newLocX] = gridNodes[oldLocY][oldLocX];
            newNodes[newLocY][newLocX].currentLocation = newShuffle[i];
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
    }

    void Swap(Node *node1, Node *node2)
    {
        Node temp = *node1;
        node1->number = node2->number;
        node1->oX = node2->oX;
        node1->oY = node2->oY;

        node2->number = temp.number;
        node2->oX = temp.oX;
        node2->oY = temp.oY;
    }

    Node *Empty()
    {
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

    vector<Node *> ValidMoves(Node *nodeIn = nullptr)
    {
        Node *node = nullptr;
        if (nodeIn == nullptr)
        {
            node = Empty();
        }
        else
        {
            node = nodeIn;
        }

        int *moves = new int[8];
        moves[0] = node->y + 1;
        moves[1] = node->x; //up side
        moves[2] = node->y - 1;
        moves[3] = node->x; //down side
        moves[4] = node->y;
        moves[5] = node->x + 1; //right side
        moves[6] = node->y;
        moves[7] = node->x - 1; //left side

        vector<int> validMoves;
        for (int i = 0; i < 8; i++)
        {
            if ((-1 < moves[i]) && (moves[i] < gridSize))
            {
                validMoves.push_back(moves[i]);
            }
            else if (i % 2 == 1)
            {
                validMoves.pop_back();
            }
            else
            {
                i++;
            }
        }
        /*
        cout << "Valid Moves: ";
        for (int i = 0; i < validMoves.size(); i += 2) {
            cout << "y " << validMoves[i] << " x " << validMoves[i + 1] << ", ";
        }
        cout << endl << endl;
        */
        vector<Node *> validNodes;
        for (int i = 0; i < validMoves.size(); i += 2)
        {
            validNodes.push_back(&gridNodes[validMoves[i]][validMoves[i + 1]]);
        }
        return validNodes;
    }

    bool CheckSorted()
    {
        for (int i = 0; i < gridSize; i++)
        {
            for (int j = 0; j < gridSize; j++)
            {
                if (gridNodes[i][j].currentLocation != gridNodes[i][j].number)
                {
                    return false;
                }
            }
        }
        return true;
    }
};