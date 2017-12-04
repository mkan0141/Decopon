#include <iostream>
#include "Board.hpp"

class AI{
public:
    BitBoard NegaMax(Board board, int depth){
        if(depth == 0 || board.isEnd() == true){
            return eval(board);
        }

        BitBoard best = 0;
        std::vector<BitBoard> vec = board.getPosVec();
        
        for(int i = 0; i < vec.size(); i++){
            Board nextBoard = board;
            nextBoard.putPos(vec[i]);
            BitBoard value = max(value, -NegaMax(board, depth - 1 ));
        }

        return best;
    }

private:
    int weight[64] = {
        30, -12,  0, -1, -1,  0, -12, 30,
         0,  -3,  0, -1, -1,  0,  -3,  0,
         0,  -3,  0, -1, -1,  0,  -3,  0,
        -1,  -3, -1, -1, -1, -1,  -3, -1,
        -1,  -3, -1, -1, -1, -1,  -3, -1,
         0,  -3,  0, -1, -1,  0,  -3,  0,
         0,  -3,  0, -1, -1,  0,  -3,  0,
        30, -12,  0, -1, -1,  0, -12, 30
    };

    BitBoard eval(Board board){
        int value = 0;
        BitBoard pos = 1;
        BitBoard white = board.getWhite();
        BitBoard black = board.getBlack();
        for(int i = 63; i >= 0; i--){
            if((pos & white) != 0 || (pos & black) != 0){
                value += weight[i];
            }
            pos = (pos << 1);
        }
    }

    BitBoard max(BitBoard x, BitBoard y){
        if(x > y){
            return x;
        }else{
            return y;
        }
    }
};