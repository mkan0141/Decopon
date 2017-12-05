#include <iostream>
#include <vector>
#include "Board.hpp"
#include "User.hpp"
#include "AI.hpp"


int main() {
	int a;
	char c;
	bool te;
	BitBoard x;
	Board game;
	User user;
	AI ai;


	std::cout << "player (先手 0 後手 1) >> " ;
	std::cin >> te;

	game.printBoard();
	while (!game.isEnd()) {

		game.printBoard();
		game.printPos();

		if(!te){
			x = user.input(game);
			te = !te;
		}else{
			// x = user.input(game);
			// te = !te;

			
			std::vector<BitBoard> vec = game.getPosVec();
			int value = -10000000;
			BitBoard b, w;
			
			b = game.getBlack();
			w = game.getWhite();

			for(auto v : vec){
				std::cout << v << std::endl;
				game.changeColor(b, w);
				int new_value = ai.NegaMax(game, 2);

				// std::cout << "new value: " << new_value << " " << value << std::endl;
				if(value < new_value){
					// std::cout << "new!!: " << v << std::endl; 
					value = new_value;
					x = v;
				} 
				game.changeColor(b, w);
			}
			game.AISetPosPrint(x);
			te = !te;
		}

		// std::cout << "set: " <<  x << std::endl;
		game.putPos(x);
		game.nextTurn();
	}
	
}
