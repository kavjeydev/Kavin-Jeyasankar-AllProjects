/*
    CSCI 262 Data Structures, Spring 2019, Project 2 - mazes

    maze_solver.cpp

    Code for the maze_solver class.  This class will use stack-based depth
    first search or queue-based breadth first search to find a solution (if
    one exists) to a simple maze.

    C. Painter-Wakefield
*/

#include "maze_solver.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stack>
#include <queue>

using namespace std;


// at maze_solver.h - you will need to modify it as well.  In this file you
// will need to complete several methods, and add any others as needed for your
// solution. 


/*
 _read_maze()

 Read in maze information (rows, columns, maze) from the provided input stream.
*/

vector<point> coordinates;
point startPoint;
point endPoint;

stack<point> stackTrue;
queue<point> queueTrue;

int stepi = startPoint.getY();
int stepj = startPoint.getX();
int numrow = 0;
int numcolumn = 0;



void maze_solver::_read_maze(istream& in) {
    string output = "";
    string column = "";
    string row = "";


    getline(in, output);
    row = output[0];
    column = output[2];
    stringstream introw(row);
    stringstream intcolumn(column);
    introw >> numrow;
    intcolumn >> numcolumn;

    while(getline(in, output)){
        _maze.push_back(output);
    }
}


/*
 _write_maze()

 Output the (partially or totally solved) maze on cout.
*/
void maze_solver::_print_maze() {
    for(int i = 0; i < _maze.size(); i++){
        cout << _maze[i] << endl;
    };
}


/*
 _initialize()

 Find the start point.  Push or enqueue the start point.
*/
void maze_solver::_initialize() {
    int y = 0;
    int xPos = 0;
    int yPos = 0;
    int xPosEnd = 0;
    int yPosEnd = 0;
    for(int i = 0; i < _maze.size(); i++){
        for(int j = 0; j < _maze[i].size(); j++){
            if(_maze[i][j] == 'o'){
                xPos = j;
                yPos = y;
            }
            if(_maze[i][j] == '*'){
                xPosEnd = j;
                yPosEnd = y;
            }
        }
        y++;
    }
    stepi = yPos;
    stepj = xPos;
    startPoint.setX(xPos);
    startPoint.setY(yPos);
    endPoint.setX(xPosEnd);
    endPoint.setY(yPosEnd);
    //stackTrue.push(startPoint);
    /*cout << xPosEnd << endl;
    cout << yPosEnd << endl;*/

}


/*
 _step()

 Take *one* step towards solving the maze, setting _no_more_steps and
 _goal_reached as appropriate.  This implements the essential maze search
 algorithm; take the next location from your stack or queue, mark the
 location with '@', add all reachable next points to your stack or queue,
 etc.

 Notes:

 - Your initial point should have been pushed/enqueued in the _initialize()
   method.

 - Set the _no_more_steps variable to true when there are no more reachable
   points, or when the maze was successfully solved.

 - Set the _goal_reached variable to true if/when the maze was successfully
   solved.

 - You should write an '@' over every location you have previously visited,
   *except* for the start and goal positions - they should remain 'o' and '*',
   respectively.

 - Since the run() method will call _print_maze() in between calls to _step(),
   you probably want to try to make progress on each call to step.  On some
   mazes, depending on your approach, it may be possible to add the same
   point multiple times to your stack or queue - i.e., if a point is reachable
   from multiple other points.  When this happens, your code will work, but
   it may make very slow progress.  To fix the problem, simply run a loop to
   remove any already visited points from your stack or queue at the beginning
   or end of _step().

 - There are many approaches to dealing with invalid/unreachable points; you
   can choose to add them and then remove them next time you get into _step(),
   you can choose to not add them in the first place, etc.

 - It is strongly recommended that you make helper methods to avoid code
   duplication; e.g., a function to detect that a point is out of bounds is
   a real help on the mazes with no walls.  You can also think about pulling
   out methods that do the actual acting on stacks/queues - this will reduce
   code duplication, since everything is identical between the two except
   for whether you use your stack or queue.  E.g., you could have methods
   named "_push", "_pop", "_next" which use the appropriate data structure.
*/
//point current = startPoint;
point current;
int once = 0;
bool endStack = false;
bool throughLoop = false;
void maze_solver::_step() {




    bool inLoop = true;
    point teleport = startPoint;

    int count = 0;
    if(_use_stack){
       /* cout << "SIZE" << endl;
        cout << stackTrue.size() << endl;*/

        while(_maze[stepi][stepj] != '*' && inLoop && !_goal_reached){
            //BOUNDS CHECK
            current.setX(stepj);
            current.setY(stepi);
            if(once == 0){
                stackTrue.push(current);
                once++;
            }
            int pop = 0;

            /*cout << "y: " << endl;
            cout << stepi << endl;
            cout << "x: " << endl;
            cout << stepj << endl;



            cout << "Start" << endl;
            cout << current.getX() << endl;
            cout << current.getY() << endl;*/

            if(stepi < numrow - 1) {
                if ((!throughLoop && _maze[stepi + 1][stepj] == '.' && _maze[stepi + 1][stepj] != '@' && _maze[stepi+1][stepj] != '#')||
                    _maze[stepi + 1][stepj] == '*') {
                    if (_maze[stepi + 1][stepj] == '*') {
                        _goal_reached = true;
                        _no_more_steps = true;
                        inLoop = false;
                        //cout << _goal_reached << endl;
                    }
                    if (_maze[stepi + 1][stepj] != '*') {
                        stepi++;
                        current.setY(stepi);
                        stackTrue.push(current);
                        throughLoop = true;
                        /*cout << "PUSH" << endl;
                        cout << current.getX() << endl;
                        cout << current.getY() << endl;*/
                        _maze[stepi][stepj] = '@';

                    }
                }
                else{
                    pop++;
                }
            }
            else{
                pop++;
            }
            if(stepj > 0) {
                if ((!throughLoop && _maze[stepi][stepj - 1] == '.' && _maze[stepi][stepj - 1] != '@' && _maze[stepi][stepj - 1] != '#')||
                    _maze[stepi][stepj - 1] == '*') {
                    if (_maze[stepi][stepj - 1] == '*') {
                        _goal_reached = true;
                        _no_more_steps = true;
                        inLoop = false;
                        //cout << _goal_reached << endl;
                    }
                    if (_maze[stepi][stepj - 1] != '*') {
                        stepj--;
                        current.setX(stepj);
                        stackTrue.push(current);
                        throughLoop = true;
                        /*cout << "PUSH" << endl;
                        cout << current.getX() << endl;
                        cout << current.getY() << endl;*/
                        _maze[stepi][stepj] = '@';

                    }
                }
                else{
                    pop++;
                }
            }
            else{
                pop++;
            }
            if(stepj < numcolumn - 1) {
                if ((!throughLoop && _maze[stepi][stepj + 1] == '.' && _maze[stepi][stepj + 1] != '@' && _maze[stepi][stepj + 1] != '#')||
                    _maze[stepi][stepj + 1] == '*') {
                    if (_maze[stepi][stepj + 1] == '*') {
                        _goal_reached = true;
                        _no_more_steps = true;
                        inLoop = false;
                       //cout << _goal_reached << endl;
                    }
                    if (_maze[stepi][stepj + 1] != '*') {
                        stepj++;
                        current.setX(stepj);
                        stackTrue.push(current);
                        throughLoop = true;
                        /*cout << "PUSH" << endl;
                        cout << current.getX() << endl;
                        cout << current.getY() << endl;*/
                        _maze[stepi][stepj] = '@';

                    }
                }
                else{
                    pop++;
                }
            }
            else{
                pop++;
            }
            if(stepi > 0 ) {
                if ((!throughLoop && _maze[stepi - 1][stepj] == '.' && _maze[stepi - 1][stepj] != '@' && _maze[stepi-1][stepj] != '#')||
                    _maze[stepi - 1][stepj] == '*') {
                    if (_maze[stepi - 1][stepj] == '*') {
                        _goal_reached = true;
                        _no_more_steps = true;
                        inLoop = false;
                        //cout << _goal_reached << endl;
                    }
                    if (_maze[stepi - 1][stepj] != '*') {
                        stepi--;
                        current.setY(stepi);
                        stackTrue.push(current);
                        throughLoop = true;
                        /*cout << "PUSH" << endl;
                        cout << current.getX() << endl;
                        cout << current.getY() << endl;*/
                        _maze[stepi][stepj] = '@';

                    }
                }
                else{
                    pop++;
                }
            }
            else{
                pop++;
            }
            if(pop == 4){
                if(stackTrue.size() > 0) {
                    stackTrue.pop();
                    if(stackTrue.size() == 0){
                        _no_more_steps = true;
                        _goal_reached = false;
                        inLoop = false;
                        endStack = true;
                    }
                    if(!endStack) {
                        /*cout << "this" << endl;
                        cout << stackTrue.top().getX() << endl;
                        cout << stackTrue.top().getY() << endl;*/
                        stepj = stackTrue.top().getX();
                        stepi = stackTrue.top().getY();
                        pop = 0;
                    }

                }



            }

            throughLoop = false;

        }


    }


    if(!_use_stack){


        while(_maze[stepi][stepj] != '*' && inLoop && !_goal_reached){
            //BOUNDS CHECK
            current.setX(stepj);
            current.setY(stepi);
            if(once == 0){
                queueTrue.push(current);
                once++;
            }
            int pop = 0;
            /*cout << "SIZE" << endl;
            cout << queueTrue.size() << endl;*/

            /*cout << "y: " << endl;
            cout << stepi << endl;
            cout << "x: " << endl;
            cout << stepj << endl;



            cout << "Start" << endl;
            cout << current.getX() << endl;
            cout << current.getY() << endl;*/

            if(stepi < numrow - 1) {
                if ((!throughLoop && _maze[stepi + 1][stepj] == '.' && _maze[stepi + 1][stepj] != '@' && _maze[stepi+1][stepj] != '#')||
                    _maze[stepi + 1][stepj] == '*') {
                    if (_maze[stepi + 1][stepj] == '*') {
                        _goal_reached = true;
                        _no_more_steps = true;
                        inLoop = false;
                        //cout << _goal_reached << endl;
                    }
                    if (_maze[stepi + 1][stepj] != '*') {
                        stepi++;
                        current.setY(stepi);
                        queueTrue.push(current);
                        throughLoop = true;
                        /*cout << "PUSH" << endl;
                        cout << current.getX() << endl;
                        cout << current.getY() << endl;*/
                        _maze[stepi][stepj] = '@';

                    }
                }
                else{
                    pop++;
                }
            }
            else{
                pop++;
            }
            if(stepj > 0) {
                if ((!throughLoop && _maze[stepi][stepj - 1] == '.' && _maze[stepi][stepj - 1] != '@' && _maze[stepi][stepj - 1] != '#')||
                    _maze[stepi][stepj - 1] == '*') {
                    if (_maze[stepi][stepj - 1] == '*') {
                        _goal_reached = true;
                        _no_more_steps = true;
                        inLoop = false;
                        //cout << _goal_reached << endl;
                    }
                    if (_maze[stepi][stepj - 1] != '*') {
                        stepj--;
                        current.setX(stepj);
                        queueTrue.push(current);
                        throughLoop = true;
                        /*cout << "PUSH" << endl;
                        cout << current.getX() << endl;
                        cout << current.getY() << endl;*/
                        _maze[stepi][stepj] = '@';

                    }
                }
                else{
                    pop++;
                }
            }
            else{
                pop++;
            }
            if(stepj < numcolumn - 1) {
                if ((!throughLoop && _maze[stepi][stepj + 1] == '.' && _maze[stepi][stepj + 1] != '@' && _maze[stepi][stepj + 1] != '#')||
                    _maze[stepi][stepj + 1] == '*') {
                    if (_maze[stepi][stepj + 1] == '*') {
                        _goal_reached = true;
                        _no_more_steps = true;
                        inLoop = false;
                        //cout << _goal_reached << endl;
                    }
                    if (_maze[stepi][stepj + 1] != '*') {
                        stepj++;
                        current.setX(stepj);
                        queueTrue.push(current);
                        throughLoop = true;
                        /*cout << "PUSH" << endl;
                        cout << current.getX() << endl;
                        cout << current.getY() << endl;*/
                        _maze[stepi][stepj] = '@';

                    }
                }
                else{
                    pop++;
                }
            }
            else{
                pop++;
            }
            if(stepi > 0 ) {
                if ((!throughLoop && _maze[stepi - 1][stepj] == '.' && _maze[stepi - 1][stepj] != '@' && _maze[stepi-1][stepj] != '#')||
                    _maze[stepi - 1][stepj] == '*') {
                    if (_maze[stepi - 1][stepj] == '*') {
                        _goal_reached = true;
                        _no_more_steps = true;
                        inLoop = false;
                        //cout << _goal_reached << endl;
                    }
                    if (_maze[stepi - 1][stepj] != '*') {
                        stepi--;
                        current.setY(stepi);
                        queueTrue.push(current);
                        throughLoop = true;
                        /*cout << "PUSH" << endl;
                        cout << current.getX() << endl;
                        cout << current.getY() << endl;*/
                        _maze[stepi][stepj] = '@';

                    }
                }
                else{
                    pop++;
                }
            }
            else{
                pop++;
            }
            if(pop == 4){
                if(queueTrue.size() > 0) {
                    queueTrue.pop();
                    if(queueTrue.size() == 0){
                        _no_more_steps = true;
                        _goal_reached = false;
                        inLoop = false;
                        endStack = true;
                    }
                    if(!endStack) {
                        /*cout << "this" << endl;
                        cout << queueTrue.front().getX() << endl;
                        cout << queueTrue.front().getY() << endl;*/
                        stepj = queueTrue.front().getX();
                        stepi = queueTrue.front().getY();
                        pop = 0;
                    }

                }



            }

            throughLoop = false;

        }


    }



}



/***************************************************************************
    You should not need to modify code below this point.  Touch at your own
    risk!
****************************************************************************/

/*
 maze_solver constructor

 You should not need to modify this.  It opens the maze file and passes
 the input stream to read_maze(), along with setting up some internal state
 (most importantly, the variable telling you whether to use a stack or
 a queue).
*/
maze_solver::maze_solver(string infile, bool use_stak, bool pause) {
    _use_stack = use_stak;
    _do_pause = pause;

    _no_more_steps = false;
    _goal_reached = false;

    // parse out maze name for later use in creating output file name
    int pos = infile.find(".");
    if (pos == string::npos) {
        _maze_name = infile;
    } else {
        _maze_name = infile.substr(0, pos);
    }

    // open input file and read in maze
    ifstream fin(infile);

    _read_maze(fin);

    fin.close();
}

/*
 run()

 Initializes the maze_solver, then runs a loop to keep moving forward towards
 a solution.

 While more steps are possible (while no_more_steps == false), run() calls
 step(), then calls print_maze(), then pause().  Once there are no more steps,
 it prints a success/failure message to the user (based on the goal_reached
 flag) and writes the final maze to a solution file.
*/

void maze_solver::run() {
    _initialize();

    cout << "Solving maze '" << _maze_name << "'." << endl;
    cout << "Initial maze: " << endl << endl;
    _print_maze();
    cout << endl;
    _pause();

    // main loop
    while (!_no_more_steps) {
        _step();
        cout << endl;
        _print_maze();
        cout << endl;
        _pause();
    }

    // final output to user
    cout << "Finished: ";
    if (_goal_reached) {
        cout << "goal reached!" << endl;
    } else {
        cout << "no solution possible!" << endl;
    }
}


/*
 pause()

 Pauses execution until user hits enter (unless do_pause == false).
*/
void maze_solver::_pause() {
    if (!_do_pause) return;
    string foo;
    cout << "Hit Enter to continue...";
    getline(cin, foo);
}

