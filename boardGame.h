using namespace std;

class BoardGame
{
public:
    Grid *grid;
    int *previous;

    BoardGame()
    {
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
        for (int i = 0; i < 2; i++)
        {
            previous[i] = -1;
        }
    }

    Node *BestMove(vector<Node *> moves, Node *start, int loop = 1)
    {
        vector<int> heuristic_new = Heuristic(moves, start->y, start->x);
        vector<int> heuristic_original = Heuristic(moves);
        int cost = 0; //IDA* usually has a f(x) = g(x) [cost] + h(x) [heuritic],
                      //however the weight of each path is same so f(x) = h(x)
        if (previous[0] != -1)
        {
            for (int i = 0; i < moves.size(); i++)
            {
                if (moves[i]->y == previous[0] &&
                    moves[i]->x == previous[1])
                {

                    moves[i] = moves[moves.size() - 1];
                    heuristic_new[i] = heuristic_new[heuristic_new.size() - 1];
                    heuristic_original[i] = heuristic_original[heuristic_original.size() - 1];
                    moves.pop_back();
                    heuristic_new.pop_back();
                    heuristic_original.pop_back();
                    break;
                }
            }
        }

        vector<Node *> excluded;
        vector<Node *> included;
        vector<int> includedH;
        for (int i = 0; i < heuristic_new.size(); i++)
        {
            if (heuristic_new[i] > heuristic_original[i])
            {
                excluded.push_back(moves[i]);
            }
            else
            {
                included.push_back(moves[i]);
                includedH.push_back(heuristic_new[i]);
            }
        }

        if (excluded.size() == moves.size())
        {
            int big = 0;
            moves.pop_back();
            for (int i = 1; i < heuristic_new.size(); i++)
            {
                if (heuristic_new[i] < heuristic_new[big])
                {
                    big = i;
                }
                moves.pop_back();
            }
            included.push_back(excluded.at(big));
            includedH.push_back(heuristic_new.at(big));
        }

        for (int i = 0; i < included.size(); i++)
        {
            if (loop > 0)
            {
                includedH.at(i) += BestMove(grid->ValidMoves(included[i]), included[i], loop - 1)->heuristic_value;
            }
        }

        int threshHold = includedH[0];
        for (int i = 1; i < includedH.size(); i++)
        {
            if (includedH[i] < threshHold)
            {
                threshHold = includedH[i];
            }
        }

        vector<Node *> nodes;
        Node *node = nullptr;

        for (int i = 0; i < included.size(); i++)
        {
            if (includedH[i] <= threshHold)
            {
                nodes.push_back(included[i]);
            }
        }
        previous[0] = start->y;
        previous[1] = start->x;

        nodes.at(0)->heuristic_value = heuristic_new[0];
        return (nodes.at(0));
    }

    vector<int> Heuristic(vector<Node *> moves, int emptyY = -1, int emptyX = -1)
    {
        vector<int> values;
        if (emptyY == -1 && emptyX == -1)
        {
            for (int i = 0; i < moves.size(); i++)
            {
                //int num = abs(moves[i]->oY - moves[i]->y) + abs(moves[i]->oX - moves[i]->x);
                //cout << "Original: " << moves[i]->number << ", h(n) = " << num << endl;
                values.push_back(
                    abs(moves[i]->oY - moves[i]->y) +
                    abs(moves[i]->oX - moves[i]->x));
            }
            return values;
        }
        else
        {
            for (int i = 0; i < moves.size(); i++)
            {
                //int num = abs(moves[i]->oY - emptyY) + abs(moves[i]->oX - emptyX);
                //cout << "New: " << moves[i]->number << ", h(n) = " << num << endl;
                values.push_back(
                    abs(moves[i]->oY - emptyY) +
                    abs(moves[i]->oX - emptyX));
            }
            return values;
        }
    }
};