#include <iostream>
#include <cassert>
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

        int best = -10000000;

        std::vector<BitBoard> vec = board.getPosVec();
        BitBoard b, w;

        // 移動前の盤面を保存
        b = board.getBlack();
        w = board.getWhite();

        if(vec.size() == 0){
            best = 0;
        }

        for(int i = 0; i < vec.size(); i++){

            board.putPos(vec[i]);
            board.nextTurn();
            int now = MinMax(board, depth - 1, color);

            if(color == board.getColor()){
                best = max(best, now);
            }else{
                best = max(best, -now);
            }

            board.changeColor(b, w);
            board.undoTurn();
        }
        return best;
    }

    // 完全読み
    int dfs(Board board, bool color){
        std::vector<BitBoard> vec = board.getPosVec();
        if(vec.size() == 0){
            if(color == Black){
                // std::cout << "dfs___   black  = " << board.countBlack() << "  white = " <<  board.countWhite() << std::endl;
                return board.countBlack() >= board.countWhite();
            }else{
                // std::cout << "dfs___   black  = " << board.countBlack() << "  white = " <<  board.countWhite() << std::endl;
                return board.countBlack() < board.countWhite();
            }
        }

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

            // 盤面を元に戻す
            board.changeColor(b, w);

            // ターンを1つ戻す
            board.undoTurn();
        }

        return best;
    } 

    // Debug Alpha Beat
    int AlphaBeta(Board board, bool color, bool turn, int depth, int alpha, int beta){
        assert(alpha <= beta);
        // 終了処理
        if(depth == 0 || board.isEnd()){
            return eval(board, turn);
        }else if(board.passCheck() == true){
            turn *= -1;
        }

        std::vector<BitBoard> vec = board.getPosVec();

        // 
        BitBoard b = board.getBlack();
        BitBoard w = board.getWhite();

        for(int i = 0; i < vec.size(); i++){
            
            board.putPos(vec[i]);

            board.nextTurn();
            int value = AlphaBeta(board, color, !turn, depth - 1, alpha, beta);

            if(turn == color && value >= beta){
                return value;
            }else if(turn != color && value <= alpha){
                return value;
            }

            if(turn == color && value >= alpha){
                alpha = value;
            }else if(turn != color && value < beta){
                beta = value;
            }

            board.changeColor(b,w);
            board.undoTurn();
        }

        if(turn == color){
            return alpha;
        }else{
            return beta;
        }
    }

private:
    int weight[65] = {
        30,  -12,   0, -1, -1,   0,  -12,  30,
       -12,  -15,  -3, -3, -3,  -3,  -15,  -12,
         0,   -3,   0, -1, -1,   0,   -3,    0,
        -1,   -3,  -1, -1, -1,  -1,   -3,   -1,
        -1,   -3,  -1, -1, -1,  -1,   -3,   -1,
         0,   -3,   0, -1, -1,   0,   -3,    0,
         0,   -3,   0, -1, -1,   0,  -15,  -12,
        30,  -12,   0, -1, -1,   0,  -12,   30
    };

    int g_weight[64] = {
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

    int eval2(Board board){
        // 確定席の数
        
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