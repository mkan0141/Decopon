#include <unistd.h>
#include <ctime>
#include <iostream>
#include <map>
#include <vector>
#include "./../hpp/AI.hpp"
#include "./../hpp/Board.hpp"
#include "./../hpp/RandomAI.hpp"
#include "./../hpp/User.hpp"

int main() {
    long double think_time = 0, total_time = 0;
    bool te_t;
    int n;
    std::cout << "AIの色を入力してください(白: 0  黒: 1)  >> ";
    std::cin >> te_t, te_t = !te_t;
    std::cout << "実験回数を入力してください >> ";
    std::cin >> n;

    std::vector<long double> time_vec;
    std::vector<std::pair<int,int> > score;
    int black = 0, white = 0, draw = 0;

    for(int i=0;i<n;i++){
        think_time = 0;
        bool te = te_t;
        BitBoard x;
        Board game;
        RandomAI rndAI;
        AI ai;
        bool AI_t;

        AI_t = te;
        while (!game.isEnd()) {
            game.printBoard();

            if (te) {
                // game.printPos();
                std::vector<BitBoard> vec = game.getPosVec();

                if (vec.size() == 0) {
                    //std::cout << "置ける場所がありません。 このターンをパスします"
                    //<< std::endl;
                    if (game.passCheck() == true) {
                        //std::cout
                        //<< "両者とも打つ場所がありません。 ゲームを終了します"
                        //<< std::endl;
                        break;
                    }
                    te = !te;
                    game.nextTurn();
                    game.pass();
                    continue;
                }


                game.notpass();
                x = rndAI.RandomPos(vec);

                te = !te;
            } else {
                clock_t start = clock();

                //game.printPos();
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

                // 四隅が取れそうなら取る

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

                x = ai.search(game, vec, AI_t, 11);

                clock_t end = clock();
                think_time += (end-start) / CLOCKS_PER_SEC;
                //std::cout << "waiting time: " << (end - start) / CLOCKS_PER_SEC << "sec"<< std::endl;
                // std::cout << "AI ---> ";
                //game.SetPosPrint(x);
                te = !te;
            }

            // std::cout << "set: " <<  x << std::endl;
            game.addStone();
            game.putPos(x);
            game.nextTurn();
        }
        // std:: cout<< std::endl << std:: endl;
        // std::cout << "----------------- Game Set !! -----------------" << std::endl;
        // game.printBoard();

        int _black = game.countBlack();
        int _white = game.countWhite();
        if(_black > _white){std::cout<<"black win"<<std::endl;black++;}
        else if(_black < _white){std::cout<<"white win"<<std::endl;white++;}
        else draw++;
        score.push_back(std::make_pair(_white, _black));
        time_vec.push_back(think_time / (game.turnNum()/2));
        total_time = think_time;
    }

    std::cout << "finished ... " << std::endl;
    std::cout << "black: " << black << "    "
        << "white: " << white << "    "
        << "draw: "<< draw << std::endl;
    if (black > white) {
        std::cout << "black win !" << std::endl;
    } else if (black < white) {
        std::cout << "white win !" << std::endl;
    } else {
        std::cout << "draw ..." << std::endl;
    }

    std::cout << "white" <<" "<<"black"<<" "<<"time"<< std::endl;

    for(int i = 0; i < (int)score.size(); i++){
         std::cout << score[i].first <<" "<<score[i].second<<" "<<time_vec[i]<< std::endl;
    }
    std::cout << "time average: " << total_time / n <<std::endl;
    return 0;
}
