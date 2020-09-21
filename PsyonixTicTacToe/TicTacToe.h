#ifndef TICTACTOE_H
#define TICTACTOE_H
#include <vector>
#include <iostream>
#include <stack>
//Board class stores info about tic tac toe board and methods to pull/place data
class Board {
public:
	Board(int N, int M);
	int getN();
	int getM();
	char get(int n, int m);
	void place(int n, int m, char player);
private:
	std::vector<std::vector<char>> board;
};
//TicTacToe class stores board and other game data
class TicTacToe {
	public:
		TicTacToe(int N, int M, int K);
		void print();
		bool move(int n, int m);
		char checkWin(int n, int m);
		bool undo();
		char getPlayer();
	private:
		Board board;
		int K;
		char player;
		std::stack<std::pair<int, int>> moves;
};
#endif