using namespace std;

class BoardGame
{
public:
    Grid *grid; //stores Grid here
    int *previous; //Previous Move on Grid

    BoardGame() {
        grid = new Grid;
        previous = new int[2];
        for (int i = 0; i < 2; i++) {
            previous[i] = -1;
        }

        /* Original code for Scalable Approach
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
        
    }

    Node *BestMove(vector<Node *> moves, Node *start, int loop = 1) { //IDA* Search
        //H_new finds heurisitc value of Node, if it were to be swapped.
        //H_original finds heuristic value of Node, from it's current Position.
        vector<int> heuristic_new = Heuristic(moves, start->y, start->x); 
        vector<int> heuristic_original = Heuristic(moves);
        /*
        IDA* usually has a f(x) = g(x) [cost] + h(x) [heuritic],
        however the weight of each path is same so f(x) = h(x).
        Thus we just used Heuritic values.
        */
        if (previous[0] != -1) { //Removes the previous action from the Valid Moves List.
            for (int i = 0; i < moves.size(); i++) {
                if (moves[i]->y == previous[0] &&
                    moves[i]->x == previous[1]) {

                    //overwrite current element with last
                    moves[i] = moves[moves.size() - 1]; 
                    heuristic_new[i] = heuristic_new[heuristic_new.size() - 1];
                    heuristic_original[i] = heuristic_original[heuristic_original.size() - 1];

                    //delete the last element to remove Redudantcy.
                    moves.pop_back();
                    heuristic_new.pop_back();
                    heuristic_original.pop_back();
                    break;
                }
            }
        }

        vector<Node *> excluded;
        vector<Node *> included;
        vector<int> includedH; //included Node's Heurostics.
        for (int i = 0; i < heuristic_new.size(); i++) {
            if (heuristic_new[i] > heuristic_original[i]) {
                //if the new Heuristic_new value is higher than Old
                //Exclude it.
                excluded.push_back(moves[i]);
            }
            else {
                included.push_back(moves[i]);
                includedH.push_back(heuristic_new[i]);
            }
        }

        if (excluded.size() == moves.size()) { 
            //Checks if all Valid moves were excluded
            int small = 0;
            //gets the smallest new Heuristic value.
            for (int i = 1; i < heuristic_new.size(); i++) {
                if (heuristic_new[i] < heuristic_new[small]) {
                    small = i;
                }
            }
            included.push_back(excluded.at(small));
            includedH.push_back(heuristic_new.at(small));
        }

        //Goes down 1 Depth of Grid Search by recursively calling once.
        //We experiemented with greater numbers, but no benefits occured.
        for (int i = 0; i < included.size(); i++) {
            if (loop > 0) {
                includedH.at(i) += BestMove(grid->ValidMoves(included[i]), included[i], loop - 1)->heuristic_value;
            }
        }

        int threshHold = includedH[0]; //sets new threshold.
        for (int i = 1; i < includedH.size(); i++) {
            //Try to find smallest possible Threshold
            if (includedH[i] < threshHold) {
                threshHold = includedH[i];
            }
        }

        vector<Node *> nodes;
        Node *node = nullptr;
        //Use the threshold to get best Node to move to.
        for (int i = 0; i < included.size(); i++) {
            if (includedH[i] <= threshHold) {
                nodes.push_back(included[i]);
            }
        }
        //Update the Previous move with newly selected Node.
        previous[0] = start->y;
        previous[1] = start->x;

        //sets heuristic_value of Node, for the recursive call.
        nodes.at(0)->heuristic_value = heuristic_new[0];
        return (nodes.at(0));
    }

    vector<int> Heuristic(vector<Node *> moves, int emptyY = -1, int emptyX = -1) {
        //Finds the Heurisitc Vaules
        vector<int> values;
        if (emptyY == -1 && emptyX == -1) { //Checks Heuristic Value with it's current location
            for (int i = 0; i < moves.size(); i++) {
                //int num = abs(moves[i]->oY - moves[i]->y) + abs(moves[i]->oX - moves[i]->x);
                //cout << "Original: " << moves[i]->number << ", h(n) = " << num << endl;
                values.push_back(
                    abs(moves[i]->oY - moves[i]->y) +
                    abs(moves[i]->oX - moves[i]->x));
                //get distance by getting the absolute value of the difference between
                //the Current Locations's x and y cordinates and original x and y cordinates
            }
            return values;
        }
        else { //Checks Heuristic Value based off empty location.
            for (int i = 0; i < moves.size(); i++) {
                //int num = abs(moves[i]->oY - emptyY) + abs(moves[i]->oX - emptyX);
                //cout << "New: " << moves[i]->number << ", h(n) = " << num << endl;
                values.push_back(
                    abs(moves[i]->oY - emptyY) + 
                    abs(moves[i]->oX - emptyX)); 
                //get distance by getting the absolute value of the difference between
                //the empty's x and y cordinates and original x and y cordinates
            }
            return values;
        }
    }
};