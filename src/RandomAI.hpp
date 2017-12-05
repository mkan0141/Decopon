#include <iostream>
#include <random>
#include <vector>
#include "Board.hpp"

class RandomAI{
public:
    BitBoard RandomPos(std::vector<BitBoard> v){
        int index = 0;
        
        std::random_device rnd;
        std::mt19937 mt(rnd());
        std::uniform_int_distribution<> rand(0, v.size() - 1);
        
        index = rand(mt);

        return v[index];
    }
};