#include <unistd.h>
#include <ctime>
#include <iostream>
#include <vector>

#include "./hpp/AI.hpp"
#include "./hpp/Board.hpp"
#include "./hpp/RandomAI.hpp"
#include "./hpp/User.hpp"

int main() {
    bool te;

    std::cout << "playerの色を入力してください(白: 0  黒: 1)  >> ";
    std::cin >> te;

    BitBoard x = 0;
    Board game;
    User user;
    AI ai;
    bool AI_t;

    AI_t = te;
    while (!game.isEnd()) {
        game.printBoard();

        if (te) {
            game.printPos();
            std::vector<BitBoard> vec = game.getPosVec();

            if (vec.size() == 0) {
                std::cout << "置ける場所がありません。 このターンをパスします"
                          << std::endl;
                if (game.passCheck() == true) {
                    std::cout
                        << "両者とも打つ場所がありません。 ゲームを終了します"
                        << std::endl;
                    break;
                }
                te = !te;
                game.nextTurn();
                game.pass();
                continue;
            }

            game.notpass();
            x = user.input(game);

            te = !te;
        } else {
            clock_t start = clock();

            game.printPos();
            // x = user.input(game);
            // te = !te;

            std::vector<BitBoard> vec = game.getPosVec();

            if (vec.size() == 0) {
                // std::cout << "置ける場所がありません。
                // このターンをパスします" << std::endl;
                if (game.passCheck() == true) {
                    // std::cout << "両者とも打つ場所がありません。
                    // ゲームを終了します" << std::endl;
                    break;
                }
                te = !te;
                game.nextTurn();
                game.pass();
                continue;
            }

            std::vector<BitBoard> tmp;
            for (auto v : vec) {
                if (v == 9223372036854775808uL || v == (BitBoard)72057594037927936uL ||
                    v == 128 || v == 1) {
                    tmp.push_back(v);
                }
            }

            if (tmp.size() != 0) {
                vec = tmp;
            }

            x = ai.search(game, vec, AI_t, 7);

            clock_t end = clock();

            std::cout << "waiting time: " << (end - start) / CLOCKS_PER_SEC << "sec"
                      << std::endl;
            std::cout << "AI ---> ";
            game.SetPosPrint(x);
            te = !te;
        }

        // std::cout << "set: " <<  x << std::endl;
        game.addStone();
        game.putPos(x);
        game.nextTurn();
    }
    // std:: cout<< std::endl << std:: endl;
    std::cout << "----------------- Game Set !! -----------------" << std::endl;
    game.printBoard();

    int black = game.countBlack();
    int white = game.countWhite();

    std::cout << "black: " << black << "    "
              << "white: " << white << std::endl;
    if (black > white) {
        std::cout << "black win !" << std::endl;
    } else if (black < white) {
        std::cout << "white win !" << std::endl;
    } else {
        std::cout << "draw ..." << std::endl;
    }
    return 0;
};
