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
			std::vector<BitBoard> vec = game.getPosVec();
			
			for(auto v : vec){
				

			}
			te = !te;
		}

		game.putPos(x);
	}
	
}
