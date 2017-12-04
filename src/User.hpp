#include <iostream>
#include <string>
#include "Board.hpp"

class User{
public:
    BitBoard input(Board game){
    go:;
        int a;
        std::string c;
		std::cout << "(A ~ H) >> ";
		std::cin >> c;
		std::cout << "(1 ~ 8) >> ";
		std::cin >> a;

		if(inputCheck(c,a) == false){
			std::cout << "不正な入力です. もう一度入力してください" << std::endl << std::endl;
			goto go;
		}

        BitBoard x = game.transformBitBoard(char(c[0]), a);

        if((game.retValid() & x) == 0){
			std::cout << "hogeeeeeeeeeee" << std::endl;
			goto go;
		}
        return x;
    }
private:
    bool inputCheck(std::string c, int x){
	    if("A" <= c && c <= "H" && 1 <= x && x <= 7){
		    return true;
	    }else{
		    return false;
	    }
    }
};