#include <iostream>
#include "Board.hpp"

class AI{
public:
    BitBoard NegaAlpha(Board board, BitBoard Alpha, BitBoard  Beta, int turn, int depth){
        if(depth == 0){
            return board.eval();
        }


    }
private:
};