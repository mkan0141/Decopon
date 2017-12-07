#include <iostream>
#include <vector>
#include "Board.hpp"
#include "User.hpp"
#include "AI.hpp"
#include "RandomAI.hpp"

int a;
char c;
bool te;
BitBoard x;
Board game;
User user;
RandomAI rm;
AI ai;

void gameWhite(){
	te = !te;
	game.printBoard();
	std::cout << "Debug: " << te << " " << game.getColor() << std::endl;
	while (!game.isEnd()) {

		game.printBoard();
		game.printPos();

		if(te){

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

			game.SetPosPrint(x);
			
			x = user.input(game);
			
			te = !te;
		}else{

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
			
			int value = -10000000;
			BitBoard b, w;
			
			b = game.getBlack();
			w = game.getWhite();

			for(auto v : vec){
				game.changeColor(b, w);
				int new_value;

				game.putPos(v);
                game.nextTurn();
				if(game.getStoneNum() >= 54) new_value = ai.dfs(game, Black);
				else new_value = ai.MinMax(game, 5, Black);
				game.undoTurn();
				std::cout << "評価値: " << new_value << std::endl;
				if(value < new_value){
					value = new_value;
					x = v;
				} 
				game.changeColor(b, w);
			}
			std::cout << "MinMax_AI set ";
			game.SetPosPrint(x);
			te = !te;
		}

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

void gameBlack(){
	game.printBoard();
	std::cout << "Debug: " << te << " " << game.getColor() << std::endl;
	while (!game.isEnd()) {

		game.printBoard();
		game.printPos();

		if(!te){

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

			game.SetPosPrint(x);
			
			x = user.input(game);
			
			te = !te;
		}else{

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
			
			int value = -10000000;
			BitBoard b, w;
			
			b = game.getBlack();
			w = game.getWhite();

			for(auto v : vec){
				game.changeColor(b, w);
				int new_value;

				game.putPos(v);
                game.nextTurn();
				if(game.getStoneNum() >= 54) new_value = ai.dfs(game, White);
				else new_value = ai.MinMax(game, 5, White);
				game.undoTurn();
				std::cout << "評価値: " << new_value << std::endl;
				if(value < new_value){
					value = new_value;
					x = v;
				} 
				game.changeColor(b, w);
			}
			std::cout << "MinMax_AI set ";
			game.SetPosPrint(x);
			te = !te;
		}

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

int main() {

	std::cout << "player (先手 0 後手 1) >> " ;
	std::cin >> te;

	if(te == Black){
		gameBlack();
	}else if(te == White){
		gameWhite();
	}
	
 }
