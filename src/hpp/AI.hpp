#include <ctime>
#include <cassert>
#include <iostream>
#include <algorithm>

#include "Board.hpp"

typedef std::pair<int, BitBoard> MOScore;

class AI {
public:
    // NegaMax
    int NegaMax(Board board, int depth, bool color) {
        if (depth == 0 || board.isEnd() == true) {
            // std::cout << "this value is " << eval(board) << std::endl;
            // board.printBoard();
            if (board.getColor() == color)
                return eval(board, color);
            else
                return -eval(board, color);
        }

        int best = 0;
        std::vector<BitBoard> vec = board.getPosVec();
        BitBoard b, w;

        // 移動前の盤面を保存
        b = board.getBlack();
        w = board.getWhite();

        for (int i = 0; i < (int)vec.size(); i++) {
            board.putPos(vec[i]);
            board.nextTurn();
            // board.printBoard();
            best = max(best, NegaMax(board, depth - 1, color));
            board.changeColor(b, w);

            board.undoTurn();
        }
        return best;
    }

    // MinMax
    int MinMax(Board board, int depth, bool color) {
        if (depth == 0 || board.isEnd() == true) {
            return eval(board, color);
        }

        int best = -10000000;

        std::vector<BitBoard> vec = board.getPosVec();
        BitBoard b, w;

        // 移動前の盤面を保存
        b = board.getBlack();
        w = board.getWhite();

        if (vec.size() == 0) {
            best = 0;
        }

        for (int i = 0; i < (int)vec.size(); i++) {
            board.putPos(vec[i]);
            board.nextTurn();
            int now = MinMax(board, depth - 1, color);

            if (color == board.getColor()) {
                best = max(best, now);
            } else {
                best = max(best, -now);
            }

            board.changeColor(b, w);
            board.undoTurn();
        }
        return best;
    }

    // 完全読み
    int dfs(Board board, bool color) {
        std::vector<BitBoard> vec = board.getPosVec();
        if (vec.size() == 0) {
            if (color == Black) {
                // std::cout << "dfs___   black  = " << board.countBlack() << "
                // white = " <<  board.countWhite() << std::endl;
                return board.countBlack() >= board.countWhite();
            } else {
                // std::cout << "dfs___   black  = " << board.countBlack() << "
                // white = " <<  board.countWhite() << std::endl;
                return board.countBlack() < board.countWhite();
            }
        }

        BitBoard b, w;
        int best = 0;

        // 移動前の盤面を保存
        b = board.getBlack();
        w = board.getWhite();

        for (int i = 0; i < (int)vec.size(); i++) {
            board.putPos(vec[i]);
            board.nextTurn();

            best += dfs(board, color);

            // 盤面を元に戻す
            board.changeColor(b, w);

            // ターンを1つ戻す
            board.undoTurn();
        }

        return best;
    }

    void moveOrdering(std::vector<BitBoard> &vec, AI &ai, Board &game, bool ai_color) {
        const int mo_depth = 3;
        std::vector<MOScore> score;
        BitBoard b, w;

        w = game.getWhite();
        b = game.getBlack();

        for(auto x : vec){std::cout << x << " ";}
        std::cout << std::endl;

        for(int i = 0; i < (int)vec.size(); i++){
            game.changeColor(b, w);

            game.putPos(vec[i]);
            game.nextTurn();

            score.push_back(std::make_pair(ai.AlphaBeta(game, ai_color, !ai_color, mo_depth, -1000000,1000000, 0), vec[i]));
            std::cout <<score[i].first << " ";
            game.undoTurn();

            game.changeColor(b, w);
        }std::cout << std::endl;

        std::sort(score.begin(), score.end(), std::greater<MOScore>());

        for(int i = 0; i < (int)score.size(); i++){
            std::cout << "score: " << score[i].first << " ";
            vec[i] = score[i].second;
        }

        std::cout << std::endl;

        for(auto x : vec){std::cout << x << " ";}
        std::cout << std::endl;
    }

    BitBoard search(Board &game, AI &ai, std::vector<BitBoard> vec, bool ai_color, int depth){
        int value = -100000000;
        BitBoard ret = 0, b, w;
        clock_t start;
        w = game.getWhite();
        b = game.getBlack();

        moveOrdering(vec, ai, game, ai_color);

        for (auto v : vec) {

            start = clock();

             game.changeColor(b, w);
             int new_value;

             game.putPos(v);
             game.nextTurn();

             if (game.getStoneNum() >= 50)
                 new_value = ai.AlphaBeta(game, ai_color, !ai_color, depth, -1000000,1000000, start);
             else
                 new_value = ai.AlphaBeta(game, ai_color, !ai_color, depth, -1000000, 1000000, start);

              if (new_value == 1000000) new_value = -1000000;

              game.undoTurn();

              std::cout << "evaluators value: " << new_value << std::endl;
              if (value < new_value) {
                  value = new_value;
                  ret = v;
              }

              game.changeColor(b, w);
        }

        return ret;
    }

    // Alpha Beta
    int AlphaBeta(Board board, bool color, bool turn, int depth, int alpha,
                  int beta, clock_t start) {
        assert(alpha <= beta);
        clock_t now = clock();
        if (((now - start) / CLOCKS_PER_SEC) >= 260) {
            return eval(board, turn);
        }
        // 終了処理
        if (depth == 0 || board.isEnd()) {
            return eval(board, turn);
        } else if (board.passCheck() == true) {
            turn *= -1;
        }

        std::vector<BitBoard> vec = board.getPosVec();

        if (vec.size() == 0) {
            return eval(board, turn);
        }

        BitBoard b = board.getBlack();
        BitBoard w = board.getWhite();

        for (int i = 0; i < (int)vec.size(); i++) {
            board.putPos(vec[i]);

            board.nextTurn();
            int value =
                AlphaBeta(board, color, !turn, depth - 1, alpha, beta, start);

            if (turn == color && value >= beta) {
                return value;
            } else if (turn != color && value <= alpha) {
                return value;
            }

            if (turn == color && value >= alpha) {
                alpha = value;
            } else if (turn != color && value < beta) {
                beta = value;
            }

            board.changeColor(b, w);
            board.undoTurn();
        }

        if (turn == color) {
            return alpha;
        } else {
            return beta;
        }
    }

private:
    int weight[65] = {
        30, -12, 0,  -1, -1, 0,  -12, 30,  -12, -15, -3, -3, -3, -3, -15, -12,
        0,  -3,  0,  -1, -1, 0,  -3,  0,   -1,  -3,  -1, -1, -1, -1, -3,  -1,
        -1, -3,  -1, -1, -1, -1, -3,  -1,  0,   -3,  0,  -1, -1, 0,  -3,  0,
        0,  -3,  0,  -1, -1, 0,  -15, -12, 30,  -12, 0,  -1, -1, 0,  -12, 30};

    /*
       int good_weight[65] = {
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
       */

    int eval(Board board, bool color) {
        int evaluation = 0;

        BitBoard pos = (BitBoard)1 << 63;
        BitBoard white = board.getWhite();
        BitBoard black = board.getBlack();

        for (int i = 0; i < 63; i++) {
            if ((pos & white) != 0) {
                if (color == White) evaluation += weight[i];
                if (color == Black) evaluation -= weight[i];
            } else if ((pos & black) != 0) {
                if (color == Black) evaluation += weight[i];
                if (color == White) evaluation -= weight[i];
            }
            pos >>= 1;
        }

        return evaluation;
    }



    int max(int x, int y) {
        return (y < x) ? x : y;
    }

    int Min(int x, int y) {
        return (x < y) ? x : y;
    }
};
