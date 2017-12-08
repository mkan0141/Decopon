#include <iostream>
#include <vector>
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
			
			int value = -10000000;
			BitBoard b, w;
			
			b = game.getBlack();
			w = game.getWhite();

			for(auto v : vec){
				game.changeColor(b, w);
				int new_value;
                // std::cout << "te == game.getColor  ---> " << (game.getColor() == te) << std::endl;

                // 54手目以降はBFSで全探索させる それより前はMinMax
                game.putPos(v);
                game.nextTurn();
				// std::cout << "Debug: " << te << " " << game.getColor() << std::endl;
                if(game.getStoneNum() >= 52) new_value = ai.dfs(game, !AI_t);
                else new_value = ai.MinMax(game, 1, AI_t);
                game.undoTurn();
                std::cout << "評価値: " << new_value << std::endl;
				if(value < new_value){
					value = new_value;
					x = v;
				}
				game.changeColor(b, w);
			}
            // std::cout << "評価値: " << x << std::endl;
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
