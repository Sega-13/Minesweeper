#include "header.h"
#include <random>
#include<vector>
#include<algorithm>
Board::Board() {
	cellStatus = Empty;
	data = '0';
}
void Board::setData(char data) {
	this->data = data;
}
char Board::getData() {
	return data;
}

void Board::setCellStatus(Cell cellStatus) {
	this->cellStatus = cellStatus;
}
 Cell Board::getCellStatus(char ch) {
	 if (ch == ' ') {
		 return Empty;
	 }
	 else if (ch == '*') {
		 return Bomb;
	 }
	 else if (ch == 'F') {
		 return Flag;
	 }
	 else {
		 return Data;
	 }
}
 void Board::setSize(int size) {
	 this->size = size;
 }
 int Board::getSize() {
	 return size;
 }
 void Board::setMines(int mines) {
	 this->mines;
 }
 int Board::getMines() {
	 return mines;
 }

void Board::displayBoard() {
	cout << "   ";
	for (int i = 0; i < size; i++) {
		cout << "   ";
		cout << i + 1;
	}
	cout << endl;
	
	for (int i = 0; i < size; i++) {
		if (i >= 9)
			cout << " ";
		else
			cout << "  ";
		cout << i + 1;
		for (int j = 0; j < size; j++) {
			switch (getCellStatus(board[i][j])) {
			case Empty:
				cout << "  | ";
				break;
			case Data:
				cout << "  |"<<board[i][j];
				break;
			case Flag:
				cout << "  |F";
				break;
			case Bomb:
				cout << "  |*";
				break;
			}

		}
		cout << "  |" << endl;
	}
	cout << endl;

}
void Board::initBoard() {
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			board[i][j] = ' ';
		}
	}
	
}
void Board::createBoard(Difficulty difficulty) {
	switch (difficulty) {
	case Beginner:
		size = EASY_SIZE;
		mines = EASY_MINE;
		break;
	case Intermediate:
		size = MEDIUM_SIZE;
		mines = MEDIUM_MINE;
		break;
	case Expert:
		size = HARD_SIZE;
		mines = HARD_MINE;
		break;
	}
	setMines(mines);
	setSize(size);
	board = new char * [size];
	for (int i = 0; i < size; i++) {
		board[i] = new char[size];
	}
	initBoard();
}
int Board:: getRandomNumber(int min, int max) {
	random_device rand;
	mt19937 gen(rand());
	uniform_int_distribution<>dis(1, 10);
	int random_number = dis(gen);
	return random_number;
}


