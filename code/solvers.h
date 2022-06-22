#ifndef SOLVERS_H
#define SOLVERS_H

#include <string>
#include "board.h"

class Solver {
    public:
        virtual void solve(int numSteps, int numWorkers, std::string savePath) = 0;
    protected:
        Board * parentPtr;
};

class ThreadSolver : public Solver{
    public:
        ThreadSolver(Board * parent);
        void solve(int numSteps, int numWorkers, std::string savePath=std::string());
};

#endif