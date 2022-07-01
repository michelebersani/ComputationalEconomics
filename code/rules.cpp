#include "rules.h"
#include <stdlib.h>

short int GameOfLifeRule::operator() (short int centre, short int up, short int down, short int left, short int right, short int upLeft, short int upRight, short int downLeft, short int downRight){

    short int sum = up + right + left + down + downLeft + downRight + upLeft + upRight; 
    return (sum == 3 || (centre == 1 && sum == 2));
}

GameOfLifeStochasticRule::GameOfLifeStochasticRule(float p_death, float p_birth): p_death(p_death), p_birth(p_birth) {}

short int GameOfLifeStochasticRule::operator() (short int centre, short int up, short int down, short int left, short int right, short int upLeft, short int upRight, short int downLeft, short int downRight){

    short int sum = up + right + left + down + downLeft + downRight + upLeft + upRight;
    return (centre && ((2<=sum && sum<=3) || ((double)rand()/RAND_MAX) > p_death)) || (!centre && (sum==3 || (sum==2 && ((double)rand()/RAND_MAX) < p_birth)));
}

VonNeumannStochasticRule::VonNeumannStochasticRule(float p_death, float p_birth): p_death(p_death), p_birth(p_birth) {}

short int VonNeumannStochasticRule::operator() (short int centre, short int up, short int down, short int left, short int right, short int upLeft, short int upRight, short int downLeft, short int downRight){

    short int sum = up + right + left + down;
    return (centre && ((sum<=1) || ((double)rand()/RAND_MAX) > p_death)) || (!centre && (sum==2 || (sum==1 && ((double)rand()/RAND_MAX) < p_birth)));
//    original version is not compatible with 2D grid
//    return (centre && (sum == 4 || (sum == 2 && (double)rand()/RAND_MAX < p_death) || ((sum == 1 || sum == 3)  && (double)rand()/RAND_MAX < p_birth) )) ||
//           (!centre && (sum==3 || (sum==2 && ((double)rand()/RAND_MAX) < p_birth)));
}