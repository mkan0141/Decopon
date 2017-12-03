#include <iostream>
#include <cstdint>

#define Black 0
#define White 1
#define None -1
typedef std::uint64_t BitBoard;

class Board {
public:
	Board() {
		black = 0x1008000000;
		white = 0x810000000;
	}

	BitBoard retValid(){
		return this->valid;
	}

	// 入力座標をbitに変換する
	BitBoard transformBitBoard(char x, int y) {
		BitBoard pos;
		int xNum = int(7 - x + 'A');
		int yNum = y;

		pos = ((BitBoard)1 << (xNum + 8 * (8 - yNum)));

		return pos;
	}

	void printPos(){
		BitBoard pos = (BitBoard)1 << 63;

		std::cout << "置ける場所[ ";

		for (int i = 0; i < 64; i++) {

			if ((valid & pos) != 0) {
				std::cout << "(" << i / 8 + 1 << "," << i % 8 + 1 <<"), ";
			}
			pos >>= 1;
		}
		std::cout << " ]" << std::endl;
	}

	// 自分の石を置いた時の処理
	void putPos(BitBoard pos) {
		
		BitBoard rev = getReverse(pos);

		if (color == Black) {
			black ^= pos | rev;
			white ^= rev;
		}
		else if (color == White) {
			black ^= rev;
			white ^= pos | rev;
		}

		nextTurn();
	}
	
	void nextTurn() {
		turn_num++;
		
		if (color == Black) {
			color = White;
		} else {
			color = Black;
		}
	}

	// 盤面を出力
	void printBoard() {
		BitBoard pos = (BitBoard)1 << 63;

		std::cout << "  A B C D E F G H" << std::endl;

		for (int i = 0; i < 64; i++) {
			if (i % 8 == 0)std::cout << i / 8 + 1 << " ";


			if ((black & pos) != 0) {
				std::cout << "x" << " ";
			}
			else if ((white & pos) != 0) {
				std::cout << "o" << " ";
			} else {
				std::cout << "." << " ";
			}

			if (i % 8 == 7)std::cout << std::endl;

			pos >>= 1;
		}
	}

	bool isEnd(){
		valid = GenValidPos();
		
		if(this->turn_num == 60){
			return true;
		}else{
			return false;
		}
	}

private:
	BitBoard black, white;
	bool color = Black;
	bool is_end = false;
	BitBoard valid;
	int turn_num = 1;

	// 合法手をbitで返す
	BitBoard GenValidPos() {
		BitBoard blank, me, enemy, mask, t, valid = 0;

		if (color == Black) {
			me = black;
			enemy = white;
		} else {
			me = white;
			enemy = black;
		}

		blank = ~(white | black);

		// 右
		mask = enemy & 0x7e7e7e7e7e7e7e7e;
		t = mask & (me << 1);
		for (int i = 0; i < 5; i++) {
			t |= mask & (t << 1);
		}
		valid = blank & (t << 1);

		// 左
		mask = enemy & 0x7e7e7e7e7e7e7e7e;
		t = mask & (me >> 1);
		for (int i = 0; i < 5; i++) {
			t |= mask & (t >> 1);
		}
		valid |= blank & (t >> 1);

		// 上
		mask = enemy & 0x00ffffffffffff00;
		t = mask & (me << 8);
		for (int i = 0; i < 5; i++) {
			t |= mask & (t << 8);
		}
		valid |= blank & (t << 8);

		// 下
		mask = enemy & 0x00ffffffffffff00;
		t = mask & (me >> 8);
		for (int i = 0; i < 5; i++) {
			t |= mask & (t >> 8);
		}
		valid |= blank & (t >> 8);

		// 右上
		mask = enemy & 0x007e7e7e7e7e7e00;
		t = mask & (me << 7);
		for (int i = 0; i < 5; i++) {
			t |= mask & (t << 7);
		}
		valid |= blank & (t << 7);

		// 左上
		mask = enemy & 0x007e7e7e7e7e7e00;
		t = mask & (me << 9);
		for (int i = 0; i < 5; i++) {
			t |= mask & (t << 9);
		}
		valid |= blank & (t << 9);

		// 右下
		mask = enemy & 0x007e7e7e7e7e7e00;
		t = mask & (me >> 9);
		for (int i = 0; i < 5; i++) {
			t |= mask & (t >> 9);
		}
		valid |= blank & (t >> 9);

		// 左下
		mask = enemy & 0x007e7e7e7e7e7e00;
		t = mask & (me >> 7);
		for (int i = 0; i < 5; i++) {
			t |= mask & (t >> 7);
		}
		valid |= blank & (t >> 7);

		return valid;
	}

	// 裏返る敵石をbitで返す
	BitBoard getReverse(BitBoard pos) {
		int i = 0;
		BitBoard me, enemy, mask, rev = 0, rev_tmp;

		if (color == Black) {
			me = black;
			enemy = white;
		}
		else {
			me = white;
			enemy = black;
		}

		rev_tmp = 0;

		// 右
		rev_tmp = 0;
		mask = 0x7e7e7e7e7e7e7e7e;
		for (i = 1; ((pos >> i) & mask & enemy) != 0; i++) {
			rev_tmp |= (pos >> i);
		}
		if (((pos >> i) & me) != 0) {
			rev |= rev_tmp;
		}

		// 左
		rev_tmp = 0;
		mask = 0x7e7e7e7e7e7e7e7e;
		for (i = 1; ((pos << i) & mask & enemy) != 0; i++) {
			rev_tmp |= (pos << i);
		}
		if (((pos << i) & me) != 0) {
			rev |= rev_tmp;
		}

		// 上
		rev_tmp = 0;
		mask = 0x00ffffffffffff00;
		for (i = 1; ((pos << 8 * i) & mask & enemy) != 0; i++) {
			rev_tmp |= (pos << 8 * i);
		}
		if (((pos << 8 * i) & me) != 0) {
			rev |= rev_tmp;
		}

		// 下
		rev_tmp = 0;
		mask = 0x00ffffffffffff00;
		for (i = 1; ((pos >> 8 * i) & mask & enemy) != 0; i++) {
			rev_tmp |= (pos >> 8 * i);
		}
		if (((pos >> 8 * i) & me) != 0) {
			rev |= rev_tmp;
		}

		// 右上
		rev_tmp = 0;
		mask = 0x007e7e7e7e7e7e00;
		for (i = 1; ((pos << 7 * i) & mask & enemy) != 0; i++) {
			rev_tmp |= (pos << 7 * i);
		}
		if (((pos << 7 * i) & me) != 0) {
			rev |= rev_tmp;
		}

		// 左上
		rev_tmp = 0;
		mask = 0x007e7e7e7e7e7e00;
		for (i = 1; ((pos << 9 * i) & mask & enemy) != 0; i++) {
			rev_tmp |= (pos << 9 * i);
		}
		if (((pos << 9 * i) & me) != 0) {
			rev |= rev_tmp;
		}

		// 右下
		rev_tmp = 0;
		mask = 0x007e7e7e7e7e7e00;
		for (i = 1; ((pos >> 9 * i) & mask & enemy) != 0; i++) {
			rev_tmp |= (pos >> 9 * i);
		}
		if (((pos >> 9 * i) & me) != 0) {
			rev |= rev_tmp;
		}

		// 左下
		rev_tmp = 0;
		mask = 0x007e7e7e7e7e7e00;
		for (i = 1; ((pos >> 7 * i) & mask & enemy) != 0; i++) {
			rev_tmp |= (pos >> 7 * i);
		}
		if (((pos >> 7 * i) & me) != 0) {
			rev |= rev_tmp;
		}

		return rev;
	}
};

/*--------------------------- main ---------------------------*/

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