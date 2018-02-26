#include <iostream>
#include <string>
#include "Board.hpp"

class User{
public:
    BitBoard input(Board game){
    go:;
        std::string s;
        std::string c;
		std::cout << "user input >> ";
		std::cin >> s;

		if(s.size() != 2 || inputCheck(s[0], s[1]) == false){
			std::cout << "不正な入力です. もう一度入力してください" << std::endl << std::endl;
			goto go;
		}

        BitBoard x = game.transformBitBoard(s[0], s[1]);

        if((game.retValid() & x) == 0){
			std::cout << "hogeeeeeeeeeee" << std::endl;
			goto go;
		}
        return x;
    }

private:
    bool inputCheck(char al, char num){
		
	    if(( ('A' <= al && al <= 'H') || ('a' <= al && al <= 'h') ) && '1' <= num && num <= '8'){
		    return true;
	    }else{
		    return false;
	    }

    }
};