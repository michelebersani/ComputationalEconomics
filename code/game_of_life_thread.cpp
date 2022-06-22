#include "solvers.h"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

bool verbose = false;

int binaryInit(){
    return (std::rand())%2;
}

int zeroInit(){return 0;}

int main(int argc, char * argv[]) {

    if(argc != 6 and argc != 7) {
        std::cout << "Usage is: " << argv[0] << " N M number_step seed nw savePath" << std::endl;
        return(-1);
    }

    int N = atoi(argv[1]);
    int M = atoi(argv[2]);
    int numSteps = atoi(argv[3]);
    std::srand(atoi(argv[4]));
    int numWorkers = atoi(argv[5]);
    short int cellStates = 2;

    GameOfLifeRule rule = GameOfLifeRule();
    Board board = Board(N, M, cellStates, rule);
    ThreadSolver solver = ThreadSolver(&board);
    
    std::vector<std::vector<short int>> firstState (N, std::vector<short int> (M));
    for (auto &row: firstState){
        std::generate(row.begin(), row.end(), zeroInit);
    }

    board.addGosperGliderGun();

    board.defineInitialState(firstState);
    board.reset();
    if (argc == 6)
        solver.solve(numSteps, numWorkers);
    else{
        std::string savePath(argv[7]);
        solver.solve(numSteps, numWorkers, savePath);
    }
    return(0);
}