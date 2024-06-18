#pragma once
#include<iostream>
#include<vector>
using namespace std;

#define EASY_SIZE 9
#define MEDIUM_SIZE 12
#define HARD_SIZE 15

#define EASY_MINE 9
#define MEDIUM_MINE 12
#define HARD_MINE 15

enum GameStatus {
	Playing,
	Won,
	Lost
};

enum Difficulty {
	Beginner,
	Intermediate,
	Expert
};
enum Cell {
	Empty,
	Data,
	Flag,
	Bomb
};
enum PlayerMove {
	Open,
	Mark
};



class Board {
private:
	Cell cellStatus;
	bool boardGenerated;
	int size;
	int mines;
	char data;
	vector<int> xCord;
	vector<int> yCord;
public:
	char** board;
	Board();
	void setData(char);
	char getData();
	void setCellStatus(Cell);
	Cell getCellStatus(char);
	void setMines(int);
	int getMines();
	void setSize(int);
	int getSize();
	void createBoard(Difficulty);
	void displayBoard();
	void initBoard();
	int getRandomNumber(int, int);
};
class GameManager {
private:
	Board userBoard,realBoard;
	Board* boardObj;
	Difficulty difficulty;
	GameStatus gameStatus;
	bool isPlaced;
	int cellOpned;
	int flagCount;
	
public:
	GameManager();
	void displayWelcome();
	void instructions();
	void selectDifficultyLevel();
	void userChoice();
	void gamePlay();
	void placeBomb(int,int);
	bool playerSelect(int, int, PlayerMove);
	int computeNeighbours(int,int);
	bool isInside(int, int);
	void checkWin();
};
