#include <iostream>
#include "Board.hpp"

class AI{
public:
    int NegaMax(Board board, int depth){
        if(depth == 0 || board.isEnd() == true){
             // std::cout << "this value is " << eval(board) << std::endl;
            // board.printBoard();
            return eval(board);
        }

        int best = 0;
        std::vector<BitBoard> vec = board.getPosVec();
        BitBoard b, w;
        
        /*  DEBUG
        std::cout << "depth: " << depth << std::endl;
        for(int i = 0; i < vec.size(); i++)std::cout << i << ": " << vec[i] << " ";
        std::cout << std::endl;
        */

        // 移動前の盤面を保存
        b = board.getBlack();
        w = board.getWhite();

        for(int i = 0; i < vec.size(); i++){

            // error: 参照渡しっぽい ?? 
            board.putPos(vec[i]);
            board.nextTurn();
            //board.printBoard();
            best = max(best, -NegaMax(board, depth - 1 ));
            board.changeColor(b, w);

            board.undoTurn();
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

    int eval(Board board){
        int value = 0;
        BitBoard pos = (BitBoard) 1 << 63;
        BitBoard white = board.getWhite();
        BitBoard black = board.getBlack();
        for(int i = 0; i < 63; i++){
            if((pos & white) != 0 || (pos & black) != 0){
                // std::cout << "add weight ... " << weight[i] << " "<< std::endl;
                value += weight[i];
            }
            pos >>= 1;
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