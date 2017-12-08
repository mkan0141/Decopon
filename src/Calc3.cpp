#include <iostream>
#include <vector>
#include <time.h>
#include "Board.hpp"
#include "User.hpp"
#include "AI.hpp"
#include "RandomAI.hpp"

bool AI_t; 

int main() {
    bool te;
	std::cout << "playerの色を入力してください(黒: 0  白: 1)  >> " ;
	std::cin >> te;

    int a;
	char c;
	te = !te;
	BitBoard x;
	Board game;
	User user;
	RandomAI rm;
	AI ai;

    AI_t = !te;

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

			game.notpass();
			x = user.input(game);

			te = !te;
		}else{
			clock_t start = clock();

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

			int value = -1000000000;
			BitBoard b, w;

			b = game.getBlack();
			w = game.getWhite();

			// 四隅が取れそうなら取る
			
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

                game.putPos(v);
                game.nextTurn();
                
				if(game.getStoneNum() >= 54) new_value = ai.dfs(game, !AI_t);
                else new_value = ai.AlphaBeta(game, AI_t, !AI_t, 7, -1000000, 1000000, start);
				
				if(new_value == 1000000) new_value = -1000000;
                
				game.undoTurn();
                
				std::cout << "評価値: " << new_value << std::endl;
				if(value < new_value){
					value = new_value;
					x = v;
				}
				game.changeColor(b, w);
			}

			clock_t end = clock();

			std::cout << "思考時間: " << (end - start) / CLOCKS_PER_SEC << std::endl;

			std::cout << "NegaMax_AI set ";
			game.notpass();
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
