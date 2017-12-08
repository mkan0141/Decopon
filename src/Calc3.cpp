#include <iostream>
#include <vector>
#include "Board.hpp"
#include "User.hpp"
#include "AI.hpp"
#include "RandomAI.hpp"

#define TRAINING 1
#define AI_t Black //  main AI White -> 後手         Black -> 先手

int main() {
    bool te;
	std::cout << "player (先手 0 後手 1) >> " ;
	std::cin >> te;

    int a;
	char c;
	te = !te;
	BitBoard x;
	Board game;
	User user;
	RandomAI rm;
	AI ai;

    te = AI_t;
	std::cout << "Debug: " << te << " " << game.getColor() << std::endl;
	while (!game.isEnd()) {

		game.printBoard();
		// game.printPos();

		if(te){
			game.printPos();
			std::vector<BitBoard> vec = game.getPosVec();

			if(vec.size() == 0){
				std::cout << "置ける場所がありません。 このターンをパスします" << std::endl;
				if(game.passCheck() == true){
					std::cout << "両者とも打つ場所がありません。 ゲームを終了します" << std::endl;
					break;
				}
				te = !te;
				game.nextTurn();
				game.pass();
				continue;
			}
			
			x = user.input(game);
			
			te = !te;
		}else{
            game.printPos();

			std::vector<BitBoard> vec = game.getPosVec();

			if(vec.size() == 0){
				std::cout << "置ける場所がありません。 このターンをパスします" << std::endl;
				if(game.passCheck() == true){
					std::cout << "両者とも打つ場所がありません。 ゲームを終了します" << std::endl;
					break;
				}
				te = !te;
				game.nextTurn();
				game.pass();
				continue;
			}
			
			int value = -1000000;
			BitBoard b, w;
			
			b = game.getBlack();
			w = game.getWhite();

			
			std::vector<BitBoard> tmp;
			for(auto v : vec){
				if(v == 9223372036854775808 || v == 72057594037927936 || v == 128 || v == 1){
					tmp.push_back(v);
				}
			}

			if(tmp.size() != 0 ){
				vec = tmp;
			}

			for(auto v : vec){
				game.changeColor(b, w);
				int new_value;
                // std::cout << "te == game.getColor  ---> " << (game.getColor() == te) << std::endl;

                // 54手目以降はBFSで全探索させる それより前はMinMax
                game.putPos(v);
                game.nextTurn();
				// std::cout << "Debug: " << te << " " << game.getColor() << std::endl;
                if(game.getStoneNum() >= 52) new_value = ai.dfs(game, !AI_t);
                else new_value = ai.AlphaBeta(game, AI_t, false, 6, -1000000, 1000000);
				
                game.undoTurn();
                std::cout << "評価値: " << new_value << std::endl;
				if(value < new_value){
					value = new_value;
					x = v;
				}
				game.changeColor(b, w);
			}
            // std::cout << "評価値: " << x << std::endl;
			std::cout << "AI set ";
			game.SetPosPrint(x);
			te = !te;
		}

		// std::cout << "set: " <<  x << std::endl;
		game.addStone();
		game.putPos(x);
		game.nextTurn();
	}
	std:: cout<< std::endl << std:: endl;
	std::cout << "----------------- Game Set !! -----------------" << std::endl;
	game.printBoard();

	int black = game.countBlack();
	int white = game.countWhite();

	std::cout << "黒: " << black << "    " << "白: " << white << std::endl;
	if(black > white){
		std::cout << "黒の勝利" << std::endl;
	}else if(black < white){
		std::cout << "白の勝利" << std::endl;
	}else{
		std::cout << "引き分け" << std::endl;
	}
 }
