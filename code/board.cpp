#include<iostream>
#include <algorithm>
#include <cstdlib>
#include<string>
#include"board.h"

Board::Board(int N, int M, short int cellStates, UpdateRule &rule) : N(N), M(M), cellStates(cellStates), rule(rule){
    std::vector<short int> initialState;
    presentBoard = std::vector<short int> (N*M);
    pastBoard = std::vector<short int> (N*M);
}

void Board::addGosperGliderGun(){

    presentBoard[5*M + 1] = 1;
    presentBoard[5*M + 2] = 1;
    presentBoard[6*M + 1] = 1;
    presentBoard[6*M + 2] = 1;

    presentBoard[3*M + 13] = 1;
    presentBoard[3*M + 14] = 1;
    presentBoard[4*M + 12] = 1;
    presentBoard[4*M + 16] = 1;
    presentBoard[5*M + 11] = 1;
    presentBoard[5*M + 17] = 1;
    presentBoard[6*M + 11] = 1;
    presentBoard[6*M + 15] = 1;
    presentBoard[6*M + 17] = 1;
    presentBoard[6*M + 18] = 1;
    presentBoard[7*M + 11] = 1;
    presentBoard[7*M + 17] = 1;
    presentBoard[8*M + 12] = 1;
    presentBoard[8*M + 16] = 1;
    presentBoard[9*M + 13] = 1;
    presentBoard[9*M + 14] = 1;

    presentBoard[1*M + 25] = 1;
    presentBoard[2*M + 23] = 1;
    presentBoard[2*M + 25] = 1;
    presentBoard[3*M + 21] = 1;
    presentBoard[3*M + 22] = 1;
    presentBoard[4*M + 21] = 1;
    presentBoard[4*M + 22] = 1;
    presentBoard[5*M + 21] = 1;
    presentBoard[5*M + 22] = 1;
    presentBoard[6*M + 23] = 1;
    presentBoard[6*M + 25] = 1;
    presentBoard[7*M + 25] = 1;
    presentBoard[3*M + 35] = 1;
    presentBoard[3*M + 36] = 1;
    presentBoard[4*M + 35] = 1;
    presentBoard[4*M + 36] = 1;
}

void Board::setUpdateRule(UpdateRule& rule){
    this->rule = rule;
}

void Board::defineInitialState(std::vector<std::vector<short int>> &matrix){
    initialState = std::vector<short int>();
    for(auto && v : matrix){
        initialState.insert(initialState.end(), v.begin(), v.end());
    }
}

void Board::reset(){
    if (initialState.empty()){
        initialState = std::vector<short int>(N*M);
        std::generate(initialState.begin(), initialState.end(), [this](){return (std::rand())%(this->cellStates);});
    }
    else{
        presentBoard = initialState;
    }
}

void Board::swapBoards(){
    presentBoard.swap(pastBoard);
}

void Board::updateCell(int j){

    int row = j/M;
    int col = j%M;
    
    int upIndex = (row == 0) ? (N - 1) * M + col : (row - 1) * M + col;
    int downIndex = (row == N - 1) ? col : (row + 1) * M + col;
    int leftIndex = (col == 0) ? (row + 1) * M - 1 : row * M  + col - 1;
    int rightIndex = (col == M - 1) ? row * M : row * M + col + 1;
    
    presentBoard[j] = rule(
            pastBoard[j], pastBoard[upIndex], pastBoard[downIndex],
            pastBoard[leftIndex], pastBoard[rightIndex],
            pastBoard[upIndex - col + leftIndex % M], pastBoard[upIndex - col + rightIndex % M],
            pastBoard[downIndex - col + leftIndex % M], pastBoard[downIndex - col + rightIndex % M]
        );

}

std::string Board::getEncodedBoard(){
    std::string encoding;
    int currentChar = presentBoard[0];
    encoding.append(std::to_string(currentChar));
    encoding.append(", ");
    encoding.append(", ");
    int leftBound = 0;
    for (int i=0; i<N*M; ++i){
        if (presentBoard[i] != currentChar) {
            encoding.append(std::to_string(i-leftBound));
            encoding.append(", ");
            currentChar = presentBoard[i];
            int leftBound = i;
        }
    }
    encoding.append(std::to_string(N*M-leftBound));
    return encoding;
}