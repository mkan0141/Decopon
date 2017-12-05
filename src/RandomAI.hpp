#include <iostream>
#include <cstdlib>
#include <vector>
#include "Board.hpp"

class RandomAI{
public:
    BitBoard RandomPos(std::vector<BitBoard> v){
        int index = 0;

        index = int(rand() * (v.size()  / (1.0 + RAND_MAX)));

        return v[index];
    }
};