#include <iostream>
#include "Board.cpp"
bool inputCheck(char c, int x);

int main() {
	int a;
	char c;
	Board game;
	game.printBoard();
	while (!game.isEnd()) {
		game.printBoard();
		game.printPos();
	go:;
		std::cout << "(A ~ H) >> ";
		std::cin >> c;
		std::cout << "(1 ~ 8) >> ";
		std::cin >> a;
		
		if(inputCheck(c,a) == false){
			std::cout << "不正な入力です. もう一度入力してください" << std::endl << std::endl;
			goto go;
		}

		BitBoard x = game.transformBitBoard(c, a);
		
		// std::cout << x <<std::endl;
		// std::cout << game.retValid() << std::endl << std::endl;

		game.printBoard();

		if((game.retValid() & x) == 0){
			std::cout << "hogeeeeeeeeeee" << std::endl;
			goto go;
		}
		game.putPos(x);
	}
	
}

bool inputCheck(char c, int x){
	if('A' <= c && c <= 'H' && 1 <= x && x <= 7){
		return true;
	}else{
		return false;
	}
}