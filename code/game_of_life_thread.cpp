#include "solvers.h"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>

template<typename ... Args>
std::string string_format( const std::string& format, Args ... args )
{
    int size_s = std::snprintf( nullptr, 0, format.c_str(), args ... ) + 1; // Extra space for '\0'
    if( size_s <= 0 ){ throw std::runtime_error( "Error during formatting." ); }
    auto size = static_cast<size_t>( size_s );
    std::unique_ptr<char[]> buf( new char[ size ] );
    std::snprintf( buf.get(), size, format.c_str(), args ... );
    return std::string( buf.get(), buf.get() + size - 1 ); // We don't want the '\0' inside
}

bool verbose = false;

int binaryInit(){
    return (std::rand())%2;
}

int zeroInit(){return 0;}

int main(int argc, char * argv[]) {


    if(argc != 9) {
        std::cout << "Usage is: " << argv[0] << " N M number_step seed nw ruleClass p_death p_birth" << std::endl;
        return(-1);
    }

    int N = atoi(argv[1]);
    int M = atoi(argv[2]);
    int numSteps = atoi(argv[3]);
    std::srand(atoi(argv[4]));
    int numWorkers = atoi(argv[5]);
    char *ruleClass = argv[6];
    float p_death = atof(argv[7]);
    float p_birth = atof(argv[8]);
    short int cellStates = 2;

    UpdateRule *rule;

    if (strcmp(ruleClass, "Stochastic") == 0){
        rule = new GameOfLifeStochasticRule(p_death, p_birth);
    }
    else if (strcmp(ruleClass, "VonNeumann") == 0){
        rule = new VonNeumannStochasticRule(p_death, p_birth);
    }
    else{
        rule = new GameOfLifeRule();
    }
    Board board = Board(N, M, cellStates, *rule);
    ThreadSolver solver = ThreadSolver(&board);

    std::vector<std::vector<short int>> firstState (N, std::vector<short int> (M));
    for (auto &row: firstState){
        std::generate(row.begin(), row.end(), zeroInit);
    }

    board.defineInitialState(firstState);
    board.addGosperGliderGunToInitialState();
    board.reset();
    std::stringstream ss;
    ss << "./results/" << ruleClass << "_";
    ss << std::fixed << std::setprecision(1) << p_death << "_" << std::fixed << std::setprecision(1) << p_birth << ".txt";
    std::string savePath = ss.str();

    solver.solve(numSteps, numWorkers, savePath);

    return(0);
}