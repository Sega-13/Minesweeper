#include<iostream>
#include<algorithm>
#include "header.h"
#include<random>
using namespace std;
	GameManager::GameManager() {
		gameStatus = Playing;
		displayWelcome();
		instructions();
		selectDifficultyLevel();
		realBoard.createBoard(difficulty);
		userBoard.createBoard(difficulty);
		flagCount = realBoard.getMines();
		gamePlay();
		
	}
	void GameManager::displayWelcome() {
		cout << "   -------------------------------------------------------------------" << endl;
		cout << "   |""                                                                 ""|" << endl;
		cout << "   |""                WELCOME TO MINESWEEPER                           ""|" << endl;
		cout << "   |""                                                                 ""|" << endl;
		cout << "   -------------------------------------------------------------------" << endl;

	}
	void GameManager :: instructions() {
		cout << "\nThese are the rules: \n";
		cout << "- The board is divided into cells, with mines randomly distributed." << endl;
		cout << "- To win, you need to open all the cells." << endl; 
		cout<<  "- The number on a cell shows the number of mines adjacent to it."<<endl;
		cout << "Using this information, you can determine cells that are safe, and cells that contain mines." << endl;
	}

	void GameManager::selectDifficultyLevel() {
		int difficultyValue=0;
		do {
			if (difficultyValue < 0 || difficultyValue>2) {
				cout << "Please Enter valid input." << endl;
			}
			cout << "Enter difficulty level." << endl;
			cout << "0 - Beginner" << endl;
			cout << "1 - Intermediate" << endl;
			cout << "2 - Expert" << endl;
			cin >> difficultyValue;
		} while (difficultyValue < 0 || difficultyValue>2);
		difficulty = (Difficulty)difficultyValue;
	}
	
	
	void GameManager::gamePlay() {
		do {
			userBoard.displayBoard();
			userChoice();
		} while (gameStatus == Playing);
	}
	void GameManager::userChoice() {
		int row = 1, col = 1;
		int input = 1;
		PlayerMove playerMove;
		do {
			if (gameStatus == Lost || gameStatus == Won)
				return;
			do {
				if (row<1 || row>realBoard.getSize()) {
					cout << "Please enter valid input" << endl;
				}
				cout << "Enter row ( 1 - " << realBoard.getSize() << "): " << endl;
				cin >> row;
			} while (row<1 || row>realBoard.getSize());
			do {
				if (col<1 || col>realBoard.getSize()) {
					cout << "Please enter valid input" << endl;
				}
				cout << "Enter col ( 1 - " << realBoard.getSize() << "): " << endl;
				cin >> col;
			} while (col<1 || col>realBoard.getSize());
			do
			{
				if (input < 1 || input > 2)
				{
					cout << "\nPlease enter valid input!\n";
				}
				cout << "\nSelect operation (1 - Open | 2 - Flag/UnFlag) : ";
				cin >> input;
			} while (input < 1 || input > 2);
			if (input == 1)
				playerMove = Open;
			else
				playerMove = Mark;
		} while (playerSelect(row - 1, col - 1, playerMove));
		
	}
	bool GameManager::playerSelect(int row, int col, PlayerMove playerMove) {
		if (!isPlaced) {
			isPlaced = true;
			placeBomb(row,col);
			for (int i = 0; i < realBoard.getSize(); ++i) {
				for (int j = 0; j < realBoard.getSize(); ++j) {
					if (realBoard.board[i][j] != '*') {
						realBoard.board[i][j] = computeNeighbours(i, j) + '0';
					}
				}
			}
		}
		if (playerMove == Open) {
			if (userBoard.board[row][col] != ' ') {
				cout << "Cell is Already Opend" << endl;
				cout << "Please Re-enter" << endl;
				userChoice();
				return 0;
			}
			userBoard.board[row][col] = realBoard.board[row][col];
			if (userBoard.board[row][col] == '*') {
				gameStatus = Lost;
				for (int i = 0; i < realBoard.getSize(); i++) {
					for (int j = 0; j < realBoard.getSize(); j++) {
						if (realBoard.board[i][j] == '*') {
							userBoard.board[i][j] = realBoard.board[i][j];
						}
					}
				}
				userBoard.displayBoard();
				cout << "OOP'S YOU CLICKED MINE!!!" << endl;
				cout << "Better Luck Next Time" << endl;
			}
			else {
				
				cellOpned++;
				cout << "cellOpned : " << cellOpned << endl;
			}
			checkWin();
		}
		if (playerMove == Mark) {
			if (userBoard.board[row][col] == 'F') {
				userBoard.board[row][col] = ' ';
			}
			else if (userBoard.board[row][col] != ' ') {
				cout << "Wrong Input" << endl;
				userChoice();
			}
			else if (flagCount > 0) {
				userBoard.board[row][col] = 'F';
				flagCount--;
			}
			else {
				cout << "OUT OF FLAG!!"<<endl;
					userChoice();
			}
		}
		return false;
	}
	void GameManager::checkWin() {
		if (cellOpned == (userBoard.getSize() * userBoard.getSize()) - (realBoard.getMines())) {
			gameStatus = Won;
			for (int i = 0; i < realBoard.getSize(); i++) {
				for (int j = 0; j < realBoard.getSize(); j++) {
					if (realBoard.board[i][j] == '*') {
						userBoard.board[i][j] = realBoard.board[i][j];
					}
				}
			}
			userBoard.displayBoard();
			cout << "HURRY YOU WON!!" << endl;
		}
	}
	void GameManager::placeBomb(int row, int col) {
		vector<pair<int, int>> position;
		for (int i = 0; i < realBoard.getSize(); ++i)
			for (int j = 0; j < realBoard.getSize(); ++j)
				position.push_back(make_pair(i, j));
		random_shuffle(position.begin(), position.end());
		for (int i = 0; i < realBoard.getMines(); ++i) {
			if (position[i].first == row && position[i].second == col) {
				random_shuffle(position.begin(), position.end());
				
			}
			realBoard.board[position[i].first][position[i].second] = '*';
		}

	}
	bool GameManager::isInside(int row, int col) {
		return 0 <= row && row < realBoard.getSize() && 0 <= col && col < realBoard.getSize();
	}
	int GameManager::computeNeighbours(int row, int col) {
		int numBomb = 0;
		for (int rowOffset = -1; rowOffset <= 1; ++rowOffset) {
			for (int colOffset = -1; colOffset <= 1; ++colOffset) {
				int nextRow = row + rowOffset;
				int nextCol = col + colOffset;
				if (isInside(nextRow,nextCol) && realBoard.board[nextRow][nextCol] == '*') {
					++numBomb;
				}
			}
		}
		return numBomb;
	}
