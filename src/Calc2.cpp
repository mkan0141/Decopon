#include <iostream>
#include <vector>
#include <unistd.h>
#include "Board.hpp"
#include "User.hpp"
#include "AI.hpp"
#include "RandomAI.hpp"

#define TRAINING 1
#define AI_t Black //  main AI White -> 後手         Black -> 先手

int main() {
    
	//std::cout << "player (先手 0 後手 1) >> " ;
	//std::cin >> te;
	

    int white_win = 0, black_win = 0, draw = 0;
	
    for(int i = 0; i < TRAINING; i++){
    int a;
	char c;
	bool te;
	BitBoard x;
	Board game;
	User user;
	RandomAI rm;
	AI ai;

    te = AI_t;
	std::cout << "Debug: " << te << " " << game.getColor() << std::endl;
	while (!game.isEnd()) {
/*
		if(30 == game.getStoneNum()){
			ai.changeValueBoard();
		}
*/
		game.printBoard();
		// game.printPos();

		if(te){
			
			std::vector<BitBoard> vec = game.getPosVec();

			if(vec.size() == 0){
				// std::cout << "置ける場所がありません。 このターンをパスします" << std::endl;
				if(game.passCheck() == true){
					// std::cout << "両者とも打つ場所がありません。 ゲームを終了します" << std::endl;
					break;
				}
				te = !te;
				game.nextTurn();
				game.pass();
				continue;
			}
			
			x = rm.RandomPos(vec);
			std::cout << "Random_AI set ";
			game.SetPosPrint(x);
			
			
			// x = user.input(game);
			
			te = !te;
		}else{
            game.printPos();
			// x = user.input(game);
			// te = !te;

			std::vector<BitBoard> vec = game.getPosVec();

			if(vec.size() == 0){
				// std::cout << "置ける場所がありません。 このターンをパスします" << std::endl;
				if(game.passCheck() == true){
					// std::cout << "両者とも打つ場所がありません。 ゲームを終了します" << std::endl;
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
                
				/*if(game.getStoneNum() >= 54) new_value = ai.dfs(game, !AI_t);
                else */new_value = ai.AlphaBeta(game, AI_t, !AI_t, 7, -1000000, 1000000);
				
				if(new_value == 1000000) new_value = -1000000;
                
				game.undoTurn();
                
				std::cout << "評価値: " << new_value << std::endl;
				if(value < new_value){
					value = new_value;
					x = v;
				}
				game.changeColor(b, w);
			}
			std::cout << "NegaMax_AI set ";
			game.SetPosPrint(x);
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

	int black = game.countBlack();
	int white = game.countWhite();

	std::cout << i << "回目: " << "黒: " << black << "    " << "白: " << white << std::endl;
	if(black > white){
		black_win++;
	}else if(black < white){
		white_win++;
	}else{
		draw++;
	}
		//usleep(5000000);
    }
    if(AI_t == Black){
        std::cout << "AI win: " << black_win << std::endl;
        std::cout << "RandomAI win: " << white_win << std::endl;
        std::cout << "draw: " << draw << std::endl;
        std::cout << "rate: " << double(black_win) / TRAINING << std::endl;
    }else{
        std::cout << "AI win: " << white_win << std::endl;
        std::cout << "RandomAI win: " << black_win << std::endl;
        std::cout << "draw: " << draw << std::endl;
        std::cout << "rate: " << double(white_win) / TRAINING << std::endl;
    }
 }
