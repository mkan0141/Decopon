#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <cstdint>

#define Black 0
#define White 1
#define None -1
typedef std::uint64_t BitBoard;

class Board {
public:
	Board() {
		this->black = 0x1008000000;
		this->white = 0x810000000;
	}

	std::vector<BitBoard> getPosVec(){
		std::vector<BitBoard> vec;
		BitBoard pos = GenValidPos();

		BitBoard tmp = 1;
		for(int i = 0; i < 64; i++){
			if((tmp & pos) != 0){
				vec.push_back(tmp);
			}
			tmp = (tmp << 1);
		}
		return vec;
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

	

	// 自分の石を置いた時の処理
	void putPos(BitBoard pos) {
		
		BitBoard rev = getReverse(pos);

		if (this->color == Black) {
			this->black ^= pos | rev;
			this->white ^= rev;
		}
		else if (this->color == White) {
			this->black ^= rev;
			this->white ^= pos | rev;
		}
	}
	
	void nextTurn() {
		turn_num++;
		
		if (this->color == Black) {
			this->color = White;
		} else {
			this->color = Black;
		}
	}

	void undoTurn() {
		turn_num--;
		
		if (this->color == Black) {
			this->color = White;
		} else {
			this->color = Black;
		}
	}

	void changeColor(BitBoard black, BitBoard white){
		this->white = white;
		this->black = black;
	}

	// 盤面を出力
	void printBoard() {
		BitBoard pos = (BitBoard)1 << 63;

		std::cout << "  A B C D E F G H" << std::endl;

		for (int i = 0; i < 64; i++) {
			if (i % 8 == 0)std::cout << i / 8 + 1 << " ";


			if ((this->black & pos) != 0) {
				std::cout << "x" << " ";
			}
			else if ((this->white & pos) != 0) {
				std::cout << "o" << " ";
			} else {
				std::cout << "." << " ";
			}

			if (i % 8 == 7)std::cout << std::endl;

			pos >>= 1;
		}
	}

	void printPos(){
		if(getColor() == White)std::cout<<"it's white!!"<<std::endl;
		this->valid = GenValidPos();

		BitBoard pos = (BitBoard)1 << 63;

		std::cout << "置ける場所[ ";

		for (int i = 0; i < 64; i++) {

			if ((this->valid & pos) != 0) {
				std::cout << "(" << chchar[i % 8 + 1] << "," << i / 8 + 1 <<"), ";
			}
			pos >>= 1;
		}
		std::cout << " ]" << std::endl;
	}

	void AISetPosPrint(BitBoard pos){
		std::cout << "AI set ";

		BitBoard cnt = (BitBoard)1 << 63;
		for (int i = 0; i < 64; i++) {

			if ((pos & cnt) != 0) {
				std::cout << "(" << chchar[i % 8 + 1] << "," << i / 8 + 1 <<"), " << std::endl;
				return ;
			}
			cnt >>= 1;
		}
	}

	bool isEnd(){
		
		if(this->turn_num == 60){
			return true;
		}else{
			return false;
		}
	}

	bool getColor(){
		return this->color;
	}

	// 黒色のbitboardを返す
	BitBoard getBlack(){
		return this->black;
	}

	// 白色のbitboardを返す
	BitBoard getWhite(){
		return this->white;
	}

private:
	BitBoard black, white;
	bool color = Black;
	bool is_end = false;
	BitBoard valid;
	int turn_num = 1;
	std::map<int ,char> chchar = { {1, 'A'}, {2, 'B'}, {3, 'C'}, {4, 'D'}, {5, 'E'}, {6, 'F'}, {7, 'G'}, {8, 'H'} };
	
	// 合法手をbitで返す
	BitBoard GenValidPos() {
		BitBoard blank, me, enemy, mask, t, retValid = 0;

		if (this->color == Black) {
			me = this->black;
			enemy = this->white;
		} else {
			me = this->white;
			enemy = this->black;
		}

		blank = ~(this->white | this->black);

		// 右
		mask = enemy & 0x7e7e7e7e7e7e7e7e;
		t = mask & (me << 1);
		for (int i = 0; i < 5; i++) {
			t |= mask & (t << 1);
		}
		retValid = blank & (t << 1);

		// 左
		mask = enemy & 0x7e7e7e7e7e7e7e7e;
		t = mask & (me >> 1);
		for (int i = 0; i < 5; i++) {
			t |= mask & (t >> 1);
		}
		retValid |= blank & (t >> 1);

		// 上
		mask = enemy & 0x00ffffffffffff00;
		t = mask & (me << 8);
		for (int i = 0; i < 5; i++) {
			t |= mask & (t << 8);
		}
		retValid |= blank & (t << 8);

		// 下
		mask = enemy & 0x00ffffffffffff00;
		t = mask & (me >> 8);
		for (int i = 0; i < 5; i++) {
			t |= mask & (t >> 8);
		}
		retValid |= blank & (t >> 8);

		// 右上
		mask = enemy & 0x007e7e7e7e7e7e00;
		t = mask & (me << 7);
		for (int i = 0; i < 5; i++) {
			t |= mask & (t << 7);
		}
		retValid |= blank & (t << 7);

		// 左上
		mask = enemy & 0x007e7e7e7e7e7e00;
		t = mask & (me << 9);
		for (int i = 0; i < 5; i++) {
			t |= mask & (t << 9);
		}
		retValid |= blank & (t << 9);

		// 右下
		mask = enemy & 0x007e7e7e7e7e7e00;
		t = mask & (me >> 9);
		for (int i = 0; i < 5; i++) {
			t |= mask & (t >> 9);
		}
		retValid |= blank & (t >> 9);

		// 左下
		mask = enemy & 0x007e7e7e7e7e7e00;
		t = mask & (me >> 7);
		for (int i = 0; i < 5; i++) {
			t |= mask & (t >> 7);
		}
		retValid |= blank & (t >> 7);

		return retValid;
	}

	// 裏返る敵石をbitで返す
	BitBoard getReverse(BitBoard pos) {
		int i = 0;
		BitBoard me, enemy, mask, rev = 0, rev_tmp;

		if (this->color == Black) {
			me = this->black;
			enemy = this->white;
		} else {
			me = this->white;
			enemy = this->black;
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
