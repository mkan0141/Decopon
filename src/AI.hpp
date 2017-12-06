#include <iostream>
#include "Board.hpp"

class AI{
public:
    // 序盤の戦略

    // 中盤読み
    int NegaMax(Board board, int depth, bool color){
        if(depth == 0 || board.isEnd() == true){
             // std::cout << "this value is " << eval(board) << std::endl;
            // board.printBoard();
            if(board.getColor() == color)return eval(board, color);
            else return -eval(board, color);
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

            board.putPos(vec[i]);
            board.nextTurn();
            //board.printBoard();
            best = max(best, NegaMax(board, depth - 1, color));
            board.changeColor(b, w);

            board.undoTurn();
        }
        return best;
    }

    int MinMax(Board board, int depth, bool color){
        if(depth == 0 || board.isEnd() == true){
            return eval(board, color);
        }

        int best = 0;

        if(color == board.getColor()){
            best = -10000;
        }else{
            best = 10000;
        }

        std::vector<BitBoard> vec = board.getPosVec();
        BitBoard b, w;

        // 移動前の盤面を保存
        b = board.getBlack();
        w = board.getWhite();

        for(int i = 0; i < vec.size(); i++){

            board.putPos(vec[i]);
            board.nextTurn();
            int now = NegaMax(board, depth - 1, !color);

            if(color == true){
                best = max(best, now);
            }else{
                best = min(best, now);
            }

            board.changeColor(b, w);
            board.undoTurn();
        }
        return best;
    }

    // 完全読み
    int dfs(Board board, bool color){
        if(board.isEnd() == true){
            if(color == Black){
                return board.countBlack() >= board.countWhite();
            }else{
                return board.countBlack() < board.countWhite();
            }
        }

        std::vector<BitBoard> vec = board.getPosVec();
        BitBoard b, w;
        int best = 0;

        // 移動前の盤面を保存
        b = board.getBlack();
        w = board.getWhite();

        for(int i = 0; i < vec.size(); i++){

            board.putPos(vec[i]);
            board.nextTurn();
            //board.printBoard();
            best += dfs(board, color);
            board.changeColor(b, w);

            board.undoTurn();
        }

        return best;
    }

private:
    int t_weight[64] = {
        30, -12,  0, -1, -1,  0, -12, 30,
         0,  -3,  0, -1, -1,  0,  -3,  0,
         0,  -3,  0, -1, -1,  0,  -3,  0,
        -1,  -3, -1, -1, -1, -1,  -3, -1,
        -1,  -3, -1, -1, -1, -1,  -3, -1,
         0,  -3,  0, -1, -1,  0,  -3,  0,
         0,  -3,  0, -1, -1,  0,  -3,  0,
        30, -12,  0, -1, -1,  0, -12, 30
    };

    int weight[64] = {
         50,  -20,   0,  -1,  -1,   0, -20,  50,
        -20,  -30,  -3,  -3,  -3,  -3, -30, -20,
          0,   -3,   0,  -1,  -1,   0,  -3,  20,
         -1,   -3,  -1,  -1,  -1,  -1,  -3,  -1,
         -1,   -3,  -1,  -1,  -1,  -1,  -3,  -1,
          0,   -3,   0,  -1,  -1,   0,  -3,  20,
        -20,  -30,  -3,  -3,  -3,  -3, -30, -20,
         50,  -20,   0,  -1,  -1,   0, -20,  50
    };

    int eval(Board board, bool color){
        int black_num = 0, white_num = 0;
        BitBoard pos = (BitBoard) 1 << 63;
        BitBoard white = board.getWhite();
        BitBoard black = board.getBlack();

        for(int i = 0; i < 63; i++){
            if((pos & white) != 0){
                // std::cout << "add weight ... " << weight[i] << " "<< std::endl;
                white_num += weight[i];
            }else if((pos & black) != 0){
                black_num += weight[i];
            }
            pos >>= 1;
        }

        // std::cout << black_num << "  " << white_num << std::endl;
        if(color == Black){
            // std::cout << "hyo-kati: " << black_num - white_num << std::endl;
            return black_num - white_num;
        }else{
            // std::cout << "hyo-kati: " << white_num - black_num << std::endl;
            return white_num - black_num;
        }
    }

    int max(int x, int y){
        if(x > y){
            return x;
        }else{
            return y;
        }
    }

    int min(int x, int y){
        if(x < y){
            return x;
        }else{
            return y;
        }
    }
};